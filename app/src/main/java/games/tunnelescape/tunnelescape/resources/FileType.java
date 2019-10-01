/**
 * @file FileType.java
 * @author Lauri Westerholm
 * @details Contains FileType: constants for different files
 */

package games.tunnelescape.tunnelescape.resources;

import android.content.Context;
import android.support.annotation.IntDef;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;


/**
 * @class Class for file handling
 */
public class FileType {
    @Retention(RetentionPolicy.SOURCE)
    @IntDef({Bonus, Intro, Level1, Level2, Level3, Level4, DifficultySettingsFile, CompletedLevelsFile})
    public @interface FileTypeRef {}

    public static final int Bonus = -1;
    public static final int Intro = 0;
    public static final int Level1 = 1;
    public static final int Level2 = 2;
    public static final int Level3 = 3;
    public static final int Level4 = 4;
    public static final int DifficultySettingsFile = 5;
    public static final int CompletedLevelsFile = 6;

    public final int fileType;
    private static final Map<Integer, String> fileTypeToStr = Collections.unmodifiableMap( Init() );
    private static final Map<Integer, String> fileTypeToDescription = Collections.unmodifiableMap( Init2() );
    private static int maxCompletedLevel = -1; // no levels completed

    /**
     * Validate int value
     * @param fileType constant int value for FileType
     */
    public FileType(@FileTypeRef int fileType) { this.fileType = fileType; }

    /**
     * Create fileTypeToStr map
     * @return fileTypeToStr map which has FileType as key and outputs file as String
     */
    private static HashMap<Integer, String> Init() {
        HashMap<Integer, String> map = new HashMap<>();
        map.put(new Integer(FileType.Bonus), "Bonus level: free flying.tescape");
        map.put(new Integer(FileType.Intro), "Intro.tescape");
        map.put(new Integer(FileType.Level1), "Escape begins.tescape");
        map.put(new Integer(FileType.Level2), "Tunnel darkens.tescape");
        map.put(new Integer(FileType.Level3), "Inferno.tescape");
        map.put(new Integer(FileType.Level4), "The final escape.tescape");
        map.put(new Integer(FileType.DifficultySettingsFile), "DifficultySetting");
        map.put(new Integer(FileType.CompletedLevelsFile), "CompletedLevels");
        return map;
    }

    /**
     * Create fileTypeToDescription map
     * @return fileTypeToDescription map with FileType as key and String descriptions
     */
    private static HashMap<Integer, String> Init2() {
        HashMap<Integer, String> map = new HashMap<>();
        map.put(new Integer(FileType.Bonus), "This time no tunnels!\nJust free flying!");
        map.put(new Integer(FileType.Intro), "An easy intro level!\nAvoid collision with tunnel edges\nFind the end of the tunnel as fast as you can!");
        map.put(new Integer(FileType.Level1), "Be ready, prepare!\nThe first challenge\nRemember, treasures give a score bonus!");
        map.put(new Integer(FileType.Level2), "Tunnels get narrower\nMultiple paths, choose the correct one!\nAvoid flames!");
        map.put(new Integer(FileType.Level3), "Flames, flames and flames!\nBe determined and fast!");
        map.put(new Integer(FileType.Level4), "This is the final!\nBoost, boost , boost!");
        map.put(new Integer(FileType.DifficultySettingsFile), "");
        map.put(new Integer(FileType.CompletedLevelsFile), "");
        return map;
    }

    /**
     * Get matching filename
     * @param fileType FileType key
     * @return filename path as String
     */
    public static String getFilePath(@FileTypeRef int fileType) {
        return fileTypeToStr.get(new Integer((fileType)));
    }

    /**
     * Get matching description for level
     * @param fileType FileType key, this should be used only for level files
     * @return description as String
     */
    public static String getDescription(@FileTypeRef int fileType) {
        return fileTypeToDescription.get(new Integer(fileType));
    }

    /**
     * Get filename without ending
     * @param fileType constant used as key
     * @return filepath file ending removed
     */
    public static String getFileName(@FileTypeRef int fileType) {
        String filename = getFilePath(fileType);
        if (filename.contains(".")) filename = filename.substring(0, filename.lastIndexOf("."));
        return filename;
    }

    /**
     * Save single player difficulty to file
     * @param context MenuScreen context
     * @param hardDifficulty whether difficulty is hard or normal, this should be SinglePlayer.HardDifficulty
     */
    public static void saveDifficulty(Context context, boolean hardDifficulty) {
        int difficulty = hardDifficulty ? 1 : 0;
        try {
            FileOutputStream os = context.openFileOutput(getFilePath(FileType.DifficultySettingsFile), Context.MODE_PRIVATE);
            os.write(difficulty);
            os.close();
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Load single player difficulty from file
     * @param context MenuScreen context
     * @return true if difficulty hard, this should match SinglePlayer.HardDifficulty
     */
    public static boolean loadDifficulty(Context context) {
        int difficulty = 0;
        try {
            FileInputStream is = context.openFileInput(getFilePath(FileType.DifficultySettingsFile));
            difficulty = is.read();
            is.close();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
        return difficulty > 0;
    }

    /**
     * Change level
     * @param currentLevel this should be SinglePlayer.CurrentLevel
     * @param increase true -> try to increase, otherwise decrease currentLevel value
     * @return update currentLevel value, this should be assigned to SinglePlayer.CurrentLevel
     */
    public static @FileTypeRef int changeLevel(@FileTypeRef int currentLevel, boolean increase) {
        if (increase && currentLevel < FileType.DifficultySettingsFile - 1) currentLevel++;
        else if (!increase && currentLevel > -1) currentLevel--;
        return currentLevel;
    }

    /**
     * Save completed level value, call this after single player is successfully finished
     * @param context pass MenuScreen instance
     * @param completedLevel level which is completed
     */
    public static void saveCompletedLevels(Context context, @FileTypeRef int completedLevel) {
        if (completedLevel > maxCompletedLevel) {
            maxCompletedLevel = completedLevel;
            try {
                FileOutputStream os = context.openFileOutput(getFilePath(FileType.CompletedLevelsFile), Context.MODE_PRIVATE);
                os.write(completedLevel);
                os.close();
            } catch (java.io.IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Load maxCompletedLevel value to detect which levels user is allowed to play
     * @param context pass MenuScreen instance
     */
    public static void loadCompletedLevels(Context context) {
        int completedLevel;
        try {
            FileInputStream is = context.openFileInput(getFilePath(FileType.CompletedLevelsFile));
            completedLevel = is.read();
            if (completedLevel > maxCompletedLevel) maxCompletedLevel = completedLevel;
            is.close();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Check whether level is available
     * @details Only the following level and already completed levels should be available
     * @param level level FileType constant value
     * @return whether level is available
     */
    public static boolean isAvailable(@FileTypeRef int level) {
        return (level < maxCompletedLevel + 2);
    }

}
