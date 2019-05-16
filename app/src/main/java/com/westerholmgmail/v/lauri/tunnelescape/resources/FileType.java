package com.westerholmgmail.v.lauri.tunnelescape.resources;

import android.content.Context;
import android.support.annotation.IntDef;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
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
    @IntDef({Intro, Level1, DifficultySettingsFile})
    public @interface FileTypeRef {}

    public static final int Intro = 0;
    public static final int Level1 = 1;
    public static final int DifficultySettingsFile = 2;

    public final int fileType;
    private static final Map<Integer, String> fileTypeToStr = Collections.unmodifiableMap( Init() );
    private static final Map<Integer, String> fileTypeToDescription = Collections.unmodifiableMap( Init2() );

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
        map.put(new Integer(FileType.Intro), "Intro.tespace");
        map.put(new Integer(FileType.Level1), "Level1.tescape");
        map.put(new Integer(FileType.DifficultySettingsFile), "DifficultySetting");
        return map;
    }

    /**
     * Create fileTypeToDescription map
     * @return fileTypeToDescription map with FileType as key and String descriptions
     */
    private static HashMap<Integer, String> Init2() {
        HashMap<Integer, String> map = new HashMap<>();
        map.put(new Integer(FileType.Intro), "An easy intro level!\nAvoid collision with tunnel edges\nFind the end of the tunnel as fast as you can!");
        map.put(new Integer(FileType.Level1), "Be ready, prepare!\nThe first challenge\nRemember to avoid flames!");
        map.put(new Integer(FileType.DifficultySettingsFile), "");
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
     * @param fileType Filetype key, this should be used only for level files
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
        else if (!increase && currentLevel > 0) currentLevel--;
        return currentLevel;
    }
}
