package games.tunnelescape.tunnelescape.resources;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.graphics.Bitmap;

import org.tensorflow.lite.Interpreter;

import java.io.FileInputStream;
import java.io.IOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * @class MLManager
 * Handle ML related operations
 */
public class MLManager {

    private static String ModelPath = "model.lite";
    private static final int OutputSize = 4;
    private static final int ImageWidth = 40;
    private static final int ImageHeight = 40;
    private static final int ImageChannels = 4;
    private static final Map<Integer, String> IntToAction = Collections.unmodifiableMap(InitMap());
    private static Interpreter tflite;

    /**
     * Create map from ints to actions Strings
     * @return Map which maps int to AIPlayer actions
     */
    private static Map<Integer, String> InitMap() {
        HashMap<Integer, String> map = new HashMap<>();
        map.put(0, "hold");
        map.put(1, "up");
        map.put(2, "left");
        map.put(3, "right");
        return map;
    }

    /**
     * Load model, this needs to be done when app is launched
     * @param activity current activity, i.e. MenuScreen instance
     */
    public static void loadModel(Activity activity) {
        // TODO: add proper error handling
        tflite = new Interpreter(GetModelByteBuffer(activity));
    }

    /**
     * Use model to get next action for AIPlayer
     * @param bitmap current screen state as bitmap
     * @return String indicating correct action
     */
    public static String getAction(Bitmap bitmap) {
        float[][] output = new float[1][OutputSize];
        float[][][][] input = ConvertBitmapToModelInput(bitmap);
        tflite.run(input, output);
        System.out.println(output[0][0]);
        int max_index = 0;
        for (int i = 1; i < OutputSize; i++) {
            max_index = output[0][i] > output[0][max_index] ? i : max_index;
        }
        return IntToAction.get(max_index);

    }

    /**
     * Get model as bytebuffer
     * @param activity current activity i.e. MenuScreen instance
     * @return model as bytebuffer
     */
    private static MappedByteBuffer GetModelByteBuffer(Activity activity) {
        try {
            AssetFileDescriptor fd = activity.getAssets().openFd(ModelPath);
            FileInputStream is = new FileInputStream(fd.getFileDescriptor());
            FileChannel fileChannel = is.getChannel();
            long startOffset = fd.getStartOffset();
            long fileLen = fd.getDeclaredLength();
            return fileChannel.map(FileChannel.MapMode.READ_ONLY, startOffset, fileLen);
        } catch (IOException e) {
            System.out.println(e.getStackTrace());
            return null;
        }
    }

    /**
     * Convert bitmap to model input
     * @param bitmap scaled screen capture as bitmap
     * @return float array which is used as model input
     */
    private static float[][][][] ConvertBitmapToModelInput(Bitmap bitmap) {
        float [][][][] conversion = new float[1][ImageHeight][ImageWidth][ImageChannels];
        int comparison = 0xFF000000;
        for (int i = 1; i < ImageChannels; i++) {
            for (int y = 0; y < bitmap.getHeight(); y++) {
                for (int x = 0; x < bitmap.getWidth(); x++) {
                    int result = (bitmap.getPixel(x, y) & (comparison >>> (i * 8)));
                    conversion[0][y][x][i] = result / (float)(comparison >>> (i * 8));
                }
            }
        }
        return conversion;
    }
}
