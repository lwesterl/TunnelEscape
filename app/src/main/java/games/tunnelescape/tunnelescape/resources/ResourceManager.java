/**
 * @file ResourceManager.java
 * @author Lauri Westerholm
 * @details Contains ResourceManager which handles loading resources etc.
 */

package games.tunnelescape.tunnelescape.resources;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;

final public class ResourceManager {

    private static HashMap<ImageType, Bitmap> bitmapResources = new HashMap<>();

    /**
     * @brief Load all resources, call this when app starts
     * @details This is quite heavy method but it should be called only once
     */
    public static void loadResources(Context context) {
        try {
            for (ImageType imageType : ImageType.values()) {
                // add all image assets
                InputStream is = context.getAssets().open(ImageType.getImagePath(imageType));
                bitmapResources.put(imageType, BitmapFactory.decodeStream(is));
            }

        } catch (IOException e) {
            System.out.println(e.getStackTrace());
        }
    }

    /**
     * @brief Get bitmap matching imageType
     * @param imageType specifies which bitmap should be returned
     * @return return bitmap matching imageType from bitmapResources. return null when imageType
     * not found
     */
    public static Bitmap getBitmap(ImageType imageType) {
        return bitmapResources.get(imageType);
    }

    /**
     * @brief This is a static class so no constructor
     */
    private ResourceManager() {}

    /**
     * @brief Get image height
     * @return return matching bitmap height or 0 if there is no matching bitmap
     */
    public static float getImageWidth(ImageType imageType) {
        Bitmap bitmap = ResourceManager.getBitmap(imageType);
        if(bitmap != null) return bitmap.getWidth();
        return 0;
    }

    /**
     * @brief Get image height
     * @return return matching bitmap height or 0 if there is no matching bitmap
     */
    public static float getImageHeight(ImageType imageType) {
        Bitmap bitmap = ResourceManager.getBitmap(imageType);
        if(bitmap != null) return bitmap.getHeight();
        return 0;
    }


}
