package com.westerholmgmail.v.lauri.tunnelescape;

import android.content.Context;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.util.Base64;

import com.westerholmgmail.v.lauri.tunnelescape.objects.PlayerObject;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

public class AIPlayer extends SinglePlayer {

    static public int reward = 0;
    static public final int LevelCompletedReward = 100000000;
    static public final int LevelFailedReward = -5000000;
    static public final int TimeReward = -10;
    static public final int EdgeHitReward = -20000;
    static public final int HazardHitReward = -100000;
    static private String RewardURL = "http://192.168.0.14:10000/reward";
    static private String StateURL = "http://192.168.0.14:10000/update";

    public AIPlayer(Context context) {
        super(context);
        AIPlayer.reward = 0;
    }

    /**
     * Send reward and game state as bitmap to server
     * @param bitmap if null -> send only reward for previous action (used when game ends)
     */
    @Override
    protected void ProcessCanvasBitmap(Bitmap bitmap) {
        new UpdateAITask().execute(AIPlayer.RewardURL, String.valueOf(AIPlayer.reward));
        if (bitmap != null) new UpdateAITask().execute(AIPlayer.StateURL, BitmapToBase64(bitmap));

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

    private class UpdateAITask extends AsyncTask<String, String, String> {
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
        }

        @Override
        protected String doInBackground(String... params) {
            String urlStr = params[0];
            String data = params[1];
            OutputStream os;
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
            }
            return "success";
        }

        /**
         * Response contains action for player when in AIPlayer mode (or response is null when nothing should be done)
         * @param response action command received from server, running neural network model
         */
        private void CheckResponse(String response) {
            if (response == null) return;
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
