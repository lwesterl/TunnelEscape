package com.westerholmgmail.v.lauri.tunnelescape.resources;


import android.content.Context;
import android.media.MediaPlayer;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;

import com.westerholmgmail.v.lauri.UI.MenuScreen;
import com.westerholmgmail.v.lauri.tunnelescape.R;



/**
 * @class AudioManager
 * @brief Class which handles all audio playbacks
 */
public class AudioManager {

    public static final byte MaxVolume = 100;
    public static byte BackGroundVolume = 40;
    public static byte MenuVolume = 40;
    public static byte EffectVolume = 50;
    private static ArrayList<MediaPlayer> mediaPlayers = new ArrayList<>(AudioType.getAmountOfAudios());


    /**
     * @brief Init AudioManager
     * @param menuScreen context to load audio files, call this from MenuScreen onCreate
     */
    public static void init(MenuScreen menuScreen) {
        ReadAudioFiles(menuScreen);
        MediaPlayer mediaPlayer = MediaPlayer.create(menuScreen, R.raw.boost_audio);
        mediaPlayer.setLooping(true);
        InitAudioVolumes(mediaPlayer, EffectVolume);
        mediaPlayers.add(0, mediaPlayer);
        mediaPlayer = MediaPlayer.create(menuScreen, R.raw.main_menu_audio);
        mediaPlayer.setLooping(true);
        InitAudioVolumes(mediaPlayer, MenuVolume);
        mediaPlayers.add(1, mediaPlayer);
        mediaPlayer = MediaPlayer.create(menuScreen, R. raw.single_player_audio);
        mediaPlayer.setLooping(true);
        InitAudioVolumes(mediaPlayer, BackGroundVolume);
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

    /**
     * @brief Set volume for specific audio playback
     * @param audioType specifies audio file
     * @param volume should be in the range of 0 - 99 (scales volumes to this scale)
     * @param context android app context
     */
    public static void setVolume(@AudioType.AudioTypeRef int audioType, byte volume, Context context) {
        if (volume > AudioManager.MaxVolume) volume = AudioManager.MaxVolume - 1;
        if (volume < 0) volume = 0;
        float volumeLevel = 1.f - (float) (Math.log(AudioManager.MaxVolume - volume) / Math.log(AudioManager.MaxVolume));
        mediaPlayers.get(audioType).setVolume(volumeLevel, volumeLevel);
        UpdateAudioVolume(audioType, volume);
        WriteVolumeFile(audioType, volume, context);
    }

    /**
     * @brief Write updated value to correct audio file
     * @param audioType specifies audio file
     * @param volume volume value to be written to the file
     * @param context android app context
     */
    private static void WriteVolumeFile(@AudioType.AudioTypeRef int audioType, int volume, Context context) {
        try {
            FileOutputStream file = context.openFileOutput(AudioType.getAudioFileName(audioType), Context.MODE_PRIVATE);
            file.write(volume);
            file.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * @brief Reads all audio files and updates volume parameters
     * @param context android app context
     */
    private static void ReadAudioFiles(Context context) {
        for (int i = 0; i < AudioType.getAmountOfAudios(); i++) {
            try {
                FileInputStream isStream = context.openFileInput(AudioType.getAudioFileName(i));
                byte volume = (byte) isStream.read();
                UpdateAudioVolume(i, volume);
            } catch(IOException e) {
                e.printStackTrace();
                continue; // audio file not yet written
            }
        }
    }

    /**
     * @brief Update specific audio value
     * @param audioType tells which audio value should be updated, must be one of AudioTypes
     * @param volume new volume value, implement value check before this function is called
     */
    private static void UpdateAudioVolume(@AudioType.AudioTypeRef int audioType, byte volume) {
        switch (audioType) {
            case AudioType.BoostAudio:
                EffectVolume = volume;
                break;
            case AudioType.MainMenuAudio:
                MenuVolume = volume;
                break;
            case AudioType.SinglePlayerAudio:
                BackGroundVolume = volume;
                break;
        }
    }

    /**
     * @brief This should be called from Init to set correct audio volumes for each MediaPlayer instance
     * @param mediaPlayer the MediaPlayer which handles this specific audio playback
     * @param volume audio volume, this should be read from matching file
     */
    private static void InitAudioVolumes(MediaPlayer mediaPlayer, byte volume) {
        float volumeLevel = 1.f - (float) (Math.log(AudioManager.MaxVolume - volume) / Math.log(AudioManager.MaxVolume));
        mediaPlayer.setVolume(volumeLevel, volumeLevel);
    }

    /**
     * @brief Make AudioManager static class so that it can't have instance created from it
     */
    private AudioManager() {}
}
