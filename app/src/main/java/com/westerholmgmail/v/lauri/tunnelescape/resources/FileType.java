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
    @IntDef({IntroLevel, Level1, DifficultySettingsFile})
    public @interface FileTypeRef {}

    public static final int IntroLevel = 0;
    public static final int Level1 = 1;
    public static final int DifficultySettingsFile = 2;

    public final int fileType;
    private static final Map<Integer, String> fileTypeToStr = Collections.unmodifiableMap( Init() );

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
        map.put(new Integer(FileType.IntroLevel), "IntroLevel.tespace");
        map.put(new Integer(FileType.Level1), "Level1.tescape");
        map.put(new Integer(FileType.DifficultySettingsFile), "DifficultySetting");
        return map;
    }

    /**
     * Get matching filename
     * @param fileType FileType key
     * @return filename path as String
     */
    public static String getFileName(@FileTypeRef int fileType) {
        return fileTypeToStr.get(new Integer((fileType)));
    }

    /**
     * Save single player difficulty to file
     * @param context MenuScreen context
     * @param hardDifficulty whether difficulty is hard or normal, this should be SinglePlayer.HardDifficulty
     */
    public static void saveDifficulty(Context context, boolean hardDifficulty) {
        int difficulty = hardDifficulty ? 1 : 0;
        try {
            FileOutputStream os = context.openFileOutput(getFileName(FileType.DifficultySettingsFile), Context.MODE_PRIVATE);
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
            FileInputStream is = context.openFileInput(getFileName(FileType.DifficultySettingsFile));
            difficulty = is.read();
            is.close();
        } catch(java.io.IOException e) {
            e.printStackTrace();
        }
        return difficulty > 0;
    }
}
