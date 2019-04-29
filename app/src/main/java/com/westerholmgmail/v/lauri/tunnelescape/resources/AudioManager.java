package com.westerholmgmail.v.lauri.tunnelescape.resources;


import android.media.MediaPlayer;
import java.util.ArrayList;

import com.westerholmgmail.v.lauri.UI.MenuScreen;
import com.westerholmgmail.v.lauri.tunnelescape.R;



/**
 * @class AudioManager
 * @brief Class which handles all audio playbacks
 */
public class AudioManager {

    static private ArrayList<MediaPlayer> mediaPlayers = new ArrayList<>(AudioType.getAmountOfAudios());
    public static final int MaxVolume = 10;


    /**
     * @brief Init AudioManager
     * @param menuScreen context to load audio files, call this from MenuScreen onCreate
     */
    public static void init(MenuScreen menuScreen) {
            MediaPlayer mediaPlayer = MediaPlayer.create(menuScreen, R.raw.boost_audio);
            mediaPlayer.setLooping(true);
            mediaPlayers.add(0, mediaPlayer);
            mediaPlayer = MediaPlayer.create(menuScreen, R.raw.main_menu_audio);
            mediaPlayer.setLooping(true);
            mediaPlayers.add(1, mediaPlayer);
            mediaPlayer = MediaPlayer.create(menuScreen, R. raw.single_player_audio);
            mediaPlayer.setLooping(true);
            mediaPlayers.add(2, mediaPlayer);
    }

    /**
     * @brief Start / pause audio playback
     * @param audioType tells which audio should be played or stopped
     * @param start true -> start playback, false -> stop playback
     */
    public static void playAudio(@AudioType.AudioTypeRef int audioType, boolean start) {
        MediaPlayer mediaPlayer = AudioManager.mediaPlayers.get(audioType);
        if (start) mediaPlayer.start();
        else if(mediaPlayer.isPlaying()) mediaPlayer.pause();
    }

    public static void setVolume(@AudioType.AudioTypeRef int audioType, int volume) {
        if (volume > AudioManager.MaxVolume) volume = AudioManager.MaxVolume;
        if (volume < 0) volume = 0;
        float volumeLevel = 1.f - (float) (Math.log(AudioManager.MaxVolume - volume) / Math.log(AudioManager.MaxVolume));
        mediaPlayers.get(audioType).setVolume(volumeLevel, volumeLevel);
    }

    /**
     * @brief Make AudioManager static class so that it can't have instance created from it
     */
    private AudioManager() {}
}
