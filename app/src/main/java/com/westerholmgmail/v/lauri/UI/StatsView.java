package com.westerholmgmail.v.lauri.UI;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;

import com.westerholmgmail.v.lauri.tunnelescape.resources.ScoreServerHandler;

/**
 * @class StatsView
 * A static class which opens browser to view user stats
 * If user isn't yet registered, register dialog should be created in the main activity
 */
public class StatsView {

    private static String UserScoreURL = "http://192.168.0.16/scores/"; // TODO change to correct address

    /**
     * Show stats if possible
     * @param context should be the main activity
     * @return true if user ok and stats can be viewed in browser, false when main activity should
     * create RegisterDialogFragment to allow user to register a new user
     */
    public static boolean showStats(Context context) {
        // check whether the user is already created
        String[] user = ScoreServerHandler.ReadUser(context);
        if (Integer.valueOf(user[1]) < 0) {
            return false;
        }
        ShowScores(context, user[0]);
        return true;
    }

    /**
     * Launch browser which shows user stats
     * @param context should be the main activity
     * @param username username stored in UserFile (@see ScoreServerHandler)
     */
    private static void ShowScores(Context context, String username) {
        Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(UserScoreURL + username));
        context.startActivity(browserIntent);
    }
}
