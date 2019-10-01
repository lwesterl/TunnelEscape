/**
 * @file AudioType.java
 * @author Lauri Westerholm
 * @details Contains AudioType: constants for different audio sources
 */

package games.tunnelescape.tunnelescape.resources;

import android.support.annotation.IntDef;


import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * @class AudioType
 * @brief Contains constants for identifying different audio files
 */
public class AudioType {
    @Retention(RetentionPolicy.SOURCE)
    @IntDef({BoostAudio, MainMenuAudio, SinglePlayerAudio})
    public @interface AudioTypeRef {}

    /** These values need to start from 0 and increase by one */
    public static final int BoostAudio = 0;
    public static final int MainMenuAudio = 1;
    public static final int SinglePlayerAudio = 2;
    private static final String[] audioFileNames = { "EffectsVolume", "MainMenuVolume", "BackGroundVolume" };

    public final int audioType;


    /**
     * @brief Validate int that it's valid AudioType
     * @param audioType AudioType int constant
     */
    public AudioType(@AudioTypeRef int audioType) {
        this.audioType = audioType;
    }

    /**
     * @brief Get how many different audio types exits
     * @return amount of existing audio types
     * @remark very bad implementation
     */
    public static int getAmountOfAudios() {
        return AudioType.SinglePlayerAudio + 1;
    }

    /**
     * @brief Get matching audio file name for AudioType
     * @param audioType constant int value
     * @return file path used to store the audio related info by AudioManager
     */
    public static String getAudioFileName(@AudioTypeRef int audioType) {
        return AudioType.audioFileNames[audioType]; /** make sure that each AudioType has matching string constant */
    }

}
