package com.westerholmgmail.v.lauri.tunnelescape.resources;


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
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.Callable;


/**
 * @class ScoreServerHandler
 * A static class that handles api connections to ScoreServer
 */
public class ScoreServerHandler {

    private static String GetUserURL = "http://192.168.0.16/api/users/user/"; // TODO add correct addresses
    private static String AddUserURL = "http://192.168.0.16/api/users/add_user/";
    private static String ScoreURL = "http://192.168.0.16/api/add_score/";
    private static String UserFile = "UserFile";
    private static @ApiStatus.ApiStatusRef int apiStatus;
    private static Callable<Void> callable;
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
     * Get api status
     * @return apiStatus
     */
    public static @ApiStatus.ApiStatusRef int getApiStatus() { return ScoreServerHandler.apiStatus; }

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
        HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
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
        HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
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
