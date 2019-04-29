package com.westerholmgmail.v.lauri.tunnelescape.resources;

import android.support.annotation.IntDef;
import android.widget.HeaderViewListAdapter;

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
     */
    public static int getAmountOfAudios() {
        return BoostAudio + 1;
    }

}
