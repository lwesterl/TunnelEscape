package com.westerholmgmail.v.lauri.UI;

import android.app.UiAutomation;
import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.VideoView;

import com.westerholmgmail.v.lauri.tunnelescape.GameEngine;
import com.westerholmgmail.v.lauri.tunnelescape.SinglePlayer;
import com.westerholmgmail.v.lauri.tunnelescape.resources.AudioManager;
import com.westerholmgmail.v.lauri.tunnelescape.resources.AudioType;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;
import com.westerholmgmail.v.lauri.tunnelescape.R;

public class MenuScreen extends AppCompatActivity implements View.OnClickListener, View.OnTouchListener, SeekBar.OnSeekBarChangeListener {
    private Button singlePlayerButton;
    private Button exitButton;
    private Button settingsButton;
    private ImageButton boostButton;
    private ImageButton leftArrowButton;
    private ImageButton rightArrowButton;
    public ProgressBar HPBar;
    private ImageView mainMenuImage;
    private GameEngine gameEngine;
    public static int ScreenWidth; /**< tells screen width */
    public static int ScreenHeight; /**< tells screen height */


    static {
        // load native lib during start up
        System.loadLibrary("physics-lib");
    }


    /**
     * @brief Entry point for TunnelEscape app
     * @param savedInstanceState possible previous app state
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // load resources during start up
        ResourceManager.loadResources(this);
        AudioManager.init(this);

        // hide title and make window full-sized
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                             WindowManager.LayoutParams.FLAG_FULLSCREEN);
        InitScreenSize();
        CreateMenuUI();
    }

    /**
     * @brief Handle user button clicks
     * @param v View which created the click
     */
    @Override
    public void onClick(View v) {
        switch(v.getId()) {
            case R.id.singlePlayerButton:
                hideMenu();
                LoadSinglePlayerUI();
                break;
            case R.id.exitButton:
                exit();
                break;
            case R.id.settingsButton:
                CreateSettingsUI();
                break;
            case R.id.MenuButton:
                CreateMenuUI();
                break;
            case R.id.WinScreenMenuButton:
                CreateMenuUI();
                break;
            case R.id.TryAgainButton:
                // todo implement
                break;
            case R.id.NextLevelButton:
                // todo implement
                break;
            default:
                System.out.println("Unhandled click");
        }
    }

    /**
     * @brief onTouch implementation, passes button press info to gameEngine
     * @param v View which created the event
     * @param event touch event
     * @return true if this handled the event, otherwise false
     */
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        switch(v.getId()) {
            case R.id.boostButton:
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    gameEngine.boostButtonClicked(true);
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    gameEngine.boostButtonClicked(false);
                }
                return true;
            case R.id.leftArrowButton:
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    gameEngine.leftButtonClicked(true);
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    gameEngine.leftButtonClicked(false);
                }
                return true;
            case R.id.rightArrowButton:
                if (event.getAction() == MotionEvent.ACTION_DOWN) {
                    gameEngine.rightButtonClicked(true);
                } else if (event.getAction() == MotionEvent.ACTION_UP) {
                    gameEngine.rightButtonClicked(false);
                }
                return true;
        }
        return false;
    }

    /**
     * @brief Create UI for TunnelEscape
     */
    private void CreateMenuUI() {
        setContentView(R.layout.main_menu_layout);
        // create Buttons
        singlePlayerButton = findViewById(R.id.singlePlayerButton);
        singlePlayerButton.setOnClickListener(this);
        exitButton = findViewById(R.id.exitButton);
        exitButton.setOnClickListener(this);
        settingsButton = findViewById(R.id.settingsButton);
        settingsButton.setOnClickListener(this);
        // create other UI related object
        mainMenuImage = findViewById(R.id.mainMenuImage);
        // start main_menu_audio
        AudioManager.playAudio(AudioType.MainMenuAudio, true);
    }

    /**
     * @brief Exit whole app
     * @details This should be called after GameEngine has exited properly
     */
    public void exit() {
        Intent intent = new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_HOME);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
    }

    /**
     * @brief Hide main menu
     * @details Hides all menu buttons, images etc.
     */
    public void hideMenu() {
        singlePlayerButton.setVisibility(View.INVISIBLE);
        exitButton.setVisibility(View.INVISIBLE);
        settingsButton.setVisibility(View.INVISIBLE);
        mainMenuImage.setVisibility(View.INVISIBLE);
    }

    /**
     * @brief Set correct values for the static screen related values (ScreenHeight and ScreenWidth)
     */
    private void InitScreenSize() {
        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        MenuScreen.ScreenHeight = displayMetrics.heightPixels;
        MenuScreen.ScreenWidth = displayMetrics.widthPixels;
    }

    /**
     * @brief Load UI for single player
     * @details Changes view to SinglePlayer.
     * Creates boostButton, leftArrowButton and rightArrowButton
     */
    private void LoadSinglePlayerUI() {
        setContentView(R.layout.single_player_layout);
        gameEngine = findViewById(R.id.gameEngine);
        gameEngine.setGameState(GameState.SinglePlayer);
        boostButton = findViewById(R.id.boostButton);
        leftArrowButton = findViewById(R.id.leftArrowButton);
        rightArrowButton = findViewById(R.id.rightArrowButton);
        boostButton.setOnTouchListener(this);
        leftArrowButton.setOnTouchListener(this);
        rightArrowButton.setOnTouchListener(this);
        HPBar = findViewById(R.id.HPBar);
        android.view.ViewGroup.LayoutParams layoutParams = gameEngine.getLayoutParams();
        layoutParams.height = MenuScreen.ScreenHeight - SinglePlayer.UIBarHeight;
        layoutParams.width = MenuScreen.ScreenWidth;
        gameEngine.setLayoutParams(layoutParams);
        // set single_player_audio playback
        AudioManager.playAudio(AudioType.MainMenuAudio, false);
        AudioManager.playAudio(AudioType.SinglePlayerAudio, true);
    }

    /**
     * @brief Create screen for settings menu
     * @details Switches to setting_menu layout and creates correct seekBars
     */
    private void CreateSettingsUI() {
        hideMenu();
        setContentView(R.layout.settings_menu);
        SeekBar seekBar = findViewById(R.id.menuVolumeSeekBar);
        seekBar.setOnSeekBarChangeListener(this);
        seekBar.setProgress(AudioManager.MenuVolume);
        seekBar = findViewById(R.id.backgroundVolumeSeekBar);
        seekBar.setOnSeekBarChangeListener(this);
        seekBar.setProgress(AudioManager.BackGroundVolume);
        seekBar = findViewById(R.id.effectsVolumeSeekBar);
        seekBar.setOnSeekBarChangeListener(this);
        seekBar.setProgress(AudioManager.EffectVolume);
    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {}

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {}

    /**
     * @brief Implementation for seekBar event
     * @param seekBar id of the activated SeekBar
     * @param progress change in value
     * @param fromUser user input or software based input source
     */
    @Override
    public void onProgressChanged(SeekBar seekBar, int progress,
                                  boolean fromUser) {
        if (fromUser) {
            switch (seekBar.getId()) {
                case R.id.menuVolumeSeekBar:
                    AudioManager.setVolume(AudioType.MainMenuAudio, (byte) progress, this);
                    break;
                case R.id.backgroundVolumeSeekBar:
                    AudioManager.setVolume(AudioType.SinglePlayerAudio, (byte) progress, this);
                    break;
                case R.id.effectsVolumeSeekBar:
                    AudioManager.setVolume(AudioType.BoostAudio, (byte) progress, this);
                    break;
            }
        }
    }

    /**
     * @brief Overload for Android back button
     * @details Return to main menu
     * @Todo change so that it works also when user returns from single player
     */
    @Override
    public void onBackPressed() {
        if (gameEngine != null && gameEngine.getCurrentGameState() == GameState.SinglePlayer) {
            singlePlayerOver(false);
        }
        CreateMenuUI();
    }

    /**
     * @brief Single player over
     * @details Game ended, return to menu and show win / lose screen. Reset SinglePlayer via GameEngine.
     * Change to menu music
     */
    public void singlePlayerOver(boolean GameOver) {
        gameEngine.exitGame();
        AudioManager.playAudio(AudioType.SinglePlayerAudio, false);
        AudioManager.playAudio(AudioType.BoostAudio, false);
        AudioManager.playAudio(AudioType.MainMenuAudio, true);
        if (GameOver) {
            createEndScreenUI();
        }

    }

    public void createEndScreenUI() {
        // todo replace SinglePlayer.PlayerWon if other game modes are created
        if (SinglePlayer.PlayerWon) {
            // create win screen
            setContentView(R.layout.win_screen_layout);
            VideoView videoView = findViewById(R.id.win_screen_videoView);
            if (videoView != null) {
                String uri = "android.resource://" + getPackageName() + "/" + R.raw.win_video;
                videoView.setVideoURI(Uri.parse(uri));
                videoView.start();
            }
            Button WinScreenButton = findViewById(R.id.WinScreenMenuButton);
            WinScreenButton.setOnClickListener(this);
            Button NextLevelButton = findViewById(R.id.NextLevelButton);
            NextLevelButton.setOnClickListener(this);
            TextView ScoreView = findViewById(R.id.LevelScore);
            ScoreView.setText("Level score: " + String.valueOf(SinglePlayer.Score));
        } else {
            // create lose screen
            setContentView(R.layout.lose_screen_layout);
            VideoView videoView = findViewById(R.id.lose_screen_videoView);
            if (videoView != null) {
                String uri = "android.resource://" + getPackageName() + "/" + R.raw.fail_video;
                videoView.setVideoURI(Uri.parse(uri));
                videoView.start();
            }
            Button mainMenuButton = findViewById(R.id.MenuButton);
            mainMenuButton.setOnClickListener(this);
            Button tryAgain = findViewById(R.id.TryAgainButton);
            tryAgain.setOnClickListener(this);
        }

    }

}


