package games.tunnelescape.tunnelescape.resources;


import android.content.Context;
import android.os.AsyncTask;

import org.json.JSONObject;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.concurrent.Callable;

import javax.net.ssl.HttpsURLConnection;


/**
 * @class ScoreServerHandler
 * A static class that handles api connections to ScoreServer
 */
public class ScoreServerHandler {

    private static String GetUserURL = "https://tunnelescape.games/api/users/user/";
    private static String AddUserURL = "https://tunnelescape.games/api/users/add_user/";
    private static String ScoreURL = "https://tunnelescape.games/api/scores/add_score/";
    private static String UserFile = "UserFile";
    private static @ApiStatus.ApiStatusRef int apiStatus;
    private static @ApiStatus.ApiStatusRef int scoreStatus;
    private static Callable<Void> callable;
    private static int ConnectionTimeout = 5000; /**< 5 s timeout, the server should respond in this time */
    public static String UserID;


    /**
     * Execute async server api call to create an user
     * @param username for the user to be created
     * @param callable post execute callback
     * @return AsyncTask
     */
    public static AsyncTask<String, Void, Void> createUser(String username, Callable<Void> callable) {
        ScoreServerHandler.callable = callable;
        return new ApiTask().execute("AddUser", username);
    }

    /**
     * Async task which adds scores to the server
     * @param context should be the main activity
     * @param callable function executed after the operation is finished
     * @param score level score
     * @param completed 1 or 0: whether the level was completed
     * @param level name of the played level
     * @return null if user not valid, otherwise return the async task which need to be executed
     */
    public static AsyncTask<Void, Void, Void> addScore(Context context, Callable<Void> callable, int score, int completed, String level, int gameMode) {
        String[] user = ScoreServerHandler.ReadUser(context);
        int userID = (Integer.valueOf(user[1]));
        if ((! user[0].equals("")) &&  (userID > -1)) {
            // valid user, try to add the score to the server
            return new AsyncTask<Void,Void, Void>() {
                @Override
                protected Void doInBackground(Void ...params) {
                    try {
                        if (ScoreServerHandler.AddScore(userID, score, completed, level, gameMode)) ScoreServerHandler.scoreStatus = ApiStatus.Ok;
                        else ScoreServerHandler.scoreStatus = ApiStatus.Error;
                    } catch (Exception e) {
                        e.printStackTrace();
                        ScoreServerHandler.scoreStatus = ApiStatus.Error;
                    }
                    return null;
                }
                @Override
                protected void onPostExecute(Void notUsed) {
                    try {
                        callable.call();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            };

        }
        return null;
    }

    /**
     * Get api status
     * @return apiStatus
     */
    public static @ApiStatus.ApiStatusRef int getApiStatus() { return ScoreServerHandler.apiStatus; }

    /**
     * Get score status
     * @return scoreStatus
     */
    public static @ApiStatus.ApiStatusRef int getScoreStatus() { return ScoreServerHandler.scoreStatus; }

    /**
     * Save username to file
     * @param context this should be the main activity
     * @param username to be saved
     * @param UserID user id, use ScoreServerHandler.UserID if user just created
     */
    public static void saveUser(Context context, String username, String UserID) {
        try {
            OutputStreamWriter os = new OutputStreamWriter(context.openFileOutput(ScoreServerHandler.UserFile, Context.MODE_PRIVATE));
            os.write(username + " \n" + UserID);
            os.close();
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Read username from UserFile
     * @param context this should be the main activity
     * @return username and user id stored in the file or empty Strings as an array
     * Note: if username is empty and id is negative, it's not a real user
     */
    public static String[] ReadUser(Context context) {
        String username = "";
        String userID = "";
        try {
            InputStream is = context.openFileInput(ScoreServerHandler.UserFile);
            InputStreamReader inputStreamReader = new InputStreamReader(is);
            BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
            username = bufferedReader.readLine(); // the first line must contain username and the second user id
            userID = bufferedReader.readLine();

        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
        finally {
            return new String[] {username, userID};
        }
    }

    /**
     * Check whether UserFile exists or not
     * @param context this should be the main activity
     * @return true if the file exists, otherwise false
     */
    public static boolean userFileExists(Context context) {
        File file = new File(context.getFilesDir(), UserFile);
        return file.exists();
    }

    /**
     *  Check whether specific user already exits
     * @param username to be checked from the ScoreServer api
     * @return true if user exits, otherwise false
     * Note: throws exceptions so implement error handling elsewhere
     */
    private static boolean CheckUserExistence(String username) throws Exception {
        String user = ScoreServerHandler.GetUserURL + username;
        java.net.URL url = new URL(user);
        HttpsURLConnection urlConnection = (HttpsURLConnection) url.openConnection();
        InputStream is = new BufferedInputStream(urlConnection.getInputStream());
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        StringBuilder message = new StringBuilder();
        for (String line; (line = reader.readLine()) != null; ) {
            message.append(line).append('\n');
        }
        urlConnection.disconnect();
        if (message.toString().contains("[]")) {
            return false;
        }
        return true;
    }

    /**
     * Try to create a new user
     * @param username for the new user
     * @return true on success, otherwise false
     * @throws Exception
     */
    private static boolean AddUser(String username) throws Exception {
        java.net.URL url = new URL(ScoreServerHandler.AddUserURL);
        HttpsURLConnection urlConnection = (HttpsURLConnection) url.openConnection();
        urlConnection.setConnectTimeout(ScoreServerHandler.ConnectionTimeout);
        urlConnection.setReadTimeout(ScoreServerHandler.ConnectionTimeout);
        urlConnection.setRequestMethod("POST");
        urlConnection.setRequestProperty("Content-Type", "application/json;charset=UTF-8");
        urlConnection.setRequestProperty("Accept", "application/json");
        urlConnection.setDoOutput(true);
        DataOutputStream os = new DataOutputStream(urlConnection.getOutputStream());
        JSONObject json = new JSONObject();
        json.put("name", username);
        os.writeBytes(json.toString());
        os.flush();
        os.close();
        int statusCode = urlConnection.getResponseCode();
        urlConnection.disconnect();
        if (statusCode == 200) {
            // user id is as response message
            InputStream is = new BufferedInputStream(urlConnection.getInputStream());
            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
            StringBuilder message = new StringBuilder();
            for (String line; (line = reader.readLine()) != null; ) {
                message.append(line).append('\n');
            }
            ScoreServerHandler.UserID = message.toString();
            return true;
        }
        return false;
    }

    /**
     * Add score to ScoresServer using the api
     * @param userID user ID, should be stored in the UserFile
     * @param score level score
     * @param completed 1, 0: whether the level was completed or not
     * @param level name of the played level
     * @return true on success, otherwise false
     * @throws Exception
     */
    private static boolean AddScore(int userID, int score, int completed, String level, int gameMode) throws Exception {
        java.net.URL url = new URL(ScoreServerHandler.ScoreURL);
        HttpsURLConnection urlConnection = (HttpsURLConnection) url.openConnection();
        urlConnection.setConnectTimeout(ScoreServerHandler.ConnectionTimeout);
        urlConnection.setReadTimeout(ScoreServerHandler.ConnectionTimeout);
        urlConnection.setRequestMethod("POST");
        urlConnection.setRequestProperty("Content-Type", "application/json;charset=UTF-8");
        urlConnection.setRequestProperty("Accept", "application/json");
        urlConnection.setDoOutput(true);
        DataOutputStream os = new DataOutputStream(urlConnection.getOutputStream());
        DateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss");

        JSONObject json = new JSONObject();
        json.put("score", score);
        json.put("time", dateFormat.format(Calendar.getInstance().getTime()));
        json.put("completed", completed);
        json.put("level", level);
        json.put("userID", userID);
        json.put("gameMode", gameMode);
        os.writeBytes(json.toString());
        os.flush();
        os.close();
        int statusCode = urlConnection.getResponseCode();
        if (statusCode == 200) return true;
        return false;
    }


    /**
     * @class ApiTask
     * Extends AsyncTask to create callable async task
     */
    private static class ApiTask extends AsyncTask<String, Void, Void> {

        /**
         * Task which is executed in another thread
         * @param params params[0] should contain task name and other params task values
         * @return void
         */
        @Override
        protected Void doInBackground(String... params) {
            try {
                if (params[0].equals("AddUser")) {
                    if (!CheckUserExistence(params[1])) {
                        if (AddUser(params[1])) ScoreServerHandler.apiStatus = ApiStatus.Ok;
                        else ScoreServerHandler.apiStatus = ApiStatus.Error;
                    } else ScoreServerHandler.apiStatus = ApiStatus.UserExists;
                } else ScoreServerHandler.apiStatus = ApiStatus.Error;

            } catch (Exception e) {
                e.printStackTrace();
                ScoreServerHandler.apiStatus = ApiStatus.Error;
            }
            return null;
        }

        /**
         * Callback called when the task finishes
         * @param notUsed only to Override
         */
        @Override
        protected void onPostExecute(Void notUsed) {
            try {
                ScoreServerHandler.callable.call();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    }
}
