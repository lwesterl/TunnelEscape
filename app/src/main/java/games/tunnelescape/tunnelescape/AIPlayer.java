package games.tunnelescape.tunnelescape;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.os.AsyncTask;
import android.util.Base64;

import games.tunnelescape.UI.MenuScreen;
import games.tunnelescape.tunnelescape.objects.GameObject;
import games.tunnelescape.tunnelescape.objects.PlayerObject;
import games.tunnelescape.tunnelescape.resources.FileType;
import games.tunnelescape.tunnelescape.resources.ImageType;
import games.tunnelescape.tunnelescape.resources.MLManager;
import games.tunnelescape.tunnelescape.resources.ResourceManager;

import java.io.ByteArrayOutputStream;
import java.util.HashMap;

public class AIPlayer extends SinglePlayer {

    static public int reward = 0;
    static public boolean EdgeHit = false;
    static public boolean HazardHit = false;
    static public final int LevelCompletedReward = 50;
    static public final int LevelFailedReward = -10;
    static public final int TimeReward = 0;
    static public final int EdgeHitReward = -20;//-5;
    static public final int HazardHitReward = -10;
    static public final int ProgressReward = 10; // 5
    static private String RewardURL = "http://192.168.0.14:10000/reward";// these all only for the ML training
    static private String StateURL = "http://192.168.0.14:10000/update";
    private int renderCycles = 0;
    private static int games = 0;
    private static final @FileType.FileTypeRef int AIPlayerLevel = FileType.Intro; // only this level is allowed for AIPlayer

    public AIPlayer(Context context) {
        super(context, AIPlayer.AIPlayerLevel);
        AIPlayer.reward = 0;
    }

    /**
     * Loops all levels, this must be called prior starting new AIPlayer game
     * This is used only for ML training
     */
    public static void loopLevels() {
        AIPlayer.games ++;
        if (AIPlayer.games > 5) {
            // loop around levels (not bonus level because it isn't a proper one)
            if (CurrentLevel == FileType.Level4) CurrentLevel = FileType.Intro;
            else CurrentLevel++;
            AIPlayer.games = 0;
        }
    }

    /**
     * Customize render so that current screen content is saved as a bitmap to be fed to the ML model
     * @param canvas drawing surface
     */
    @Override
    public void render(Canvas canvas) {
        Canvas surfaceCanvas = null;
        Bitmap surfaceBitmap = null;
        renderCycles ++;
        if (renderCycles == 10) {
            PlayerObject.boostPressed = false;
            PlayerObject.rightPressed = false;
            PlayerObject.lefPressed = false;
        } else if (renderCycles %  20 == 0) {
            surfaceBitmap = Bitmap.createBitmap(MenuScreen.ScreenWidth, MenuScreen.ScreenHeight, Bitmap.Config.ARGB_8888);
            surfaceCanvas = new Canvas(surfaceBitmap);
            transferCanvas(surfaceCanvas);
            if (AIPlayer.EdgeHit) AIPlayer.reward = AIPlayer.EdgeHitReward;
            if (AIPlayer.HazardHit) AIPlayer.reward = AIPlayer.HazardHitReward;
            AIPlayer.EdgeHit = false;
            AIPlayer.HazardHit = false;
            renderCycles = 0;
        }
        transferCanvas(canvas);
        canvas.drawColor(backgroundColor);
        for (GameObject imageObject : imageObjects) {
            imageObject.draw(canvas);
            if (surfaceCanvas != null) imageObject.draw(surfaceCanvas);
        }
        for (HashMap.Entry<Long, GameObject> item : gameObjects.entrySet()) {
            item.getValue().draw(canvas);
            if (surfaceCanvas != null) item.getValue().draw(surfaceCanvas);
        }
        if (surfaceBitmap != null) {
            float xCounterTransform = canvasMultiplierX * (MenuScreen.ScreenWidth - maxDiffX);
            float yCounterTransform = canvasMultiplierY * (MenuScreen.ScreenHeight - maxDiffY);
            float playerWidth = ResourceManager.getImageWidth(ImageType.Player);
            float playerHeight = ResourceManager.getImageHeight(ImageType.Player);
            int x = (int) (playerPosition.getX() - xCounterTransform - 4.5f * playerWidth);
            int y = (int) (playerPosition.getY() - yCounterTransform - 4.5f * playerHeight);
            int width = (int) (10.f * playerWidth);
            int height = (int) (10.f * playerHeight);
            x = x < 0 ? 0 : x;
            y = y < 0 ? 0 : y;
            if (width > MenuScreen.ScreenWidth - x) width = MenuScreen.ScreenWidth - x;
            if (height > MenuScreen.ScreenHeight - y) height = MenuScreen.ScreenHeight -y;
            Bitmap cropped = Bitmap.createBitmap(surfaceBitmap, x, y, width, height);
            Bitmap scaled = Bitmap.createScaledBitmap(cropped, 40, 40, false);
            ProcessCanvasBitmap(scaled);
        }

    }

    /**
     * Customize stopSinglePlayer to suite AIPlayer. Update AIPlayer reward, which is basically redundant
     * when the pre-trained model is used in production
     */
    @Override
    protected void stopSinglePlayer() {
        gameRunning = false;
        // the lines below are used only for training the ML
        if (!PlayerWon) {
            Score = 0;
            // update AIPlayer reward
            AIPlayer.reward = AIPlayer.LevelFailedReward;
            ProcessCanvasBitmap(null);
        }
        else {
            CalculateScore();
            // update AIPlayer reward
            AIPlayer.reward = AIPlayer.LevelCompletedReward + AIPlayer.TimeReward * Score;
            ProcessCanvasBitmap(null);
        }
        //SinglePlayer.PlayerWon = true;
        // Get a handler that can be used to post to the main thread
        android.os.Handler mainHandler = new android.os.Handler(context.getMainLooper());

        Runnable myRunnable = () -> {
            MenuScreen menuScreen = (MenuScreen) context;
            menuScreen.singlePlayerOver(true);
        };
        mainHandler.post(myRunnable);
    }


    /**
     * Convert bitmap to base64 string, used when image is send to server
     * @param bitmap to be converted to base64
     * @return base64 encoded bitmap
     */
    private String BitmapToBase64(Bitmap bitmap) {
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 100, byteArrayOutputStream);
        byte[] byteArray = byteArrayOutputStream .toByteArray();
        return Base64.encodeToString(byteArray, Base64.DEFAULT);
    }

    /**
     * Send reward and game state as bitmap to server
     * @param bitmap if null -> send only reward for previous action (used when game ends)
     */

    private void ProcessCanvasBitmap(Bitmap bitmap) {
        if (CheckWhetherProgressed() && AIPlayer.reward > -1) AIPlayer.reward += ProgressReward;
        else AIPlayer.reward -= 2;
        // When training ML, uncomment the line below
        //new UpdateAITask().execute(AIPlayer.RewardURL, String.valueOf(AIPlayer.reward));
        if (bitmap != null) new UpdateAITask().execute(AIPlayer.StateURL, BitmapToBase64(bitmap));
    }

    /**
     * Check whether Player has progressed towards at least one end
     * @return true if closer to one end than before, otherwise false
     */
    private boolean CheckWhetherProgressed() {
        boolean closingEnd = false;
        float x_center = playerPosition.getX() + ResourceManager.getImageWidth(ImageType.Player) * 0.5f;
        float y_center = playerPosition.getY() + ResourceManager.getImageHeight(ImageType.Player) * 0.5f;
        for (Vector2fDoublePair pair : endDistance) {
            Vector2f endPosition = pair.first;
            Double cmpDistance = pair.second;
            // check if distance between player and end is smaller (endPosition is end center coordinates)
            double distance = Math.sqrt(Math.pow(endPosition.getX() - x_center, 2.f) + Math.pow(endPosition.getY() - y_center, 2.f));
            if (distance < cmpDistance) {
                closingEnd = true;
                pair.second = distance; // update, do not update otherwise so that agent isn't rewarded from going back and forth
            }

        }
        return closingEnd;
    }

    private class UpdateAITask extends AsyncTask<String, String, String> {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        /**
         * This updates AIPlayer as a background task. The current configuration is for production
         * (uses pre-trained Tensoflow lite model). For training the model, uncomment server related
         * lines.
         * @param params URL (basically unnecessary for production) and current screen image capture as base64 string
         * @return string whether update was successful
         */
        @Override
        protected String doInBackground(String... params) {
            String urlStr = params[0];
            String data = params[1];
            // for training, uncomment lines below
            /*OutputStream os;
            try {
                URL url = new URL(urlStr);
                HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();
                httpURLConnection.setDoOutput(true);
                httpURLConnection.setRequestMethod("POST");
                os = new BufferedOutputStream(httpURLConnection.getOutputStream());

                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os, "UTF-8"));
                writer.write(data);
                writer.flush();
                writer.close();
                os.close();

                int responseCode=httpURLConnection.getResponseCode();
                if (responseCode == HttpURLConnection.HTTP_OK) {
                    BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(httpURLConnection.getInputStream()));
                    String response = bufferedReader.readLine();
                    CheckResponse(response);
                }

            } catch (Exception e) {
                System.out.println(e.getStackTrace());
                return "fail";
            }*/
            byte[] decodedString = Base64.decode(data, Base64.DEFAULT);
            Bitmap bitmap = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
            String action = MLManager.getAction(bitmap);
            CheckResponse(action);
            return "success";
        }

        /**
         * Response contains action for player when in AIPlayer mode (or response is null when nothing should be done)
         * @param response action command received from server, running neural network model
         */
        private void CheckResponse(String response) {
            if (response == null) {
                // reward was updated and needs to be initialized
                AIPlayer.reward = 0;
                return;
            }
            PlayerObject.boostPressed = false;
            PlayerObject.rightPressed = false;
            PlayerObject.lefPressed = false;
            if (response.equals("up")) PlayerObject.boostPressed = true;
            else if (response.equals("left")) {
                PlayerObject.boostPressed = true;
                PlayerObject.lefPressed = true;
            }
            else if (response.equals("right")) {
                PlayerObject.boostPressed = true;
                PlayerObject.rightPressed = true;
            }
        }
    }
}
