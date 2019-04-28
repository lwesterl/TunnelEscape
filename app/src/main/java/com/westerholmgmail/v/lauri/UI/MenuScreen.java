package com.westerholmgmail.v.lauri.UI;

import android.content.Intent;
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

import com.westerholmgmail.v.lauri.tunnelescape.GameEngine;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;
import com.westerholmgmail.v.lauri.tunnelescape.R;

public class MenuScreen extends AppCompatActivity implements View.OnClickListener, View.OnTouchListener {
    private Button singlePlayerButton;
    private Button exitButton;
    private ImageButton boostButton;
    private ImageButton leftArrowButton;
    private ImageButton rightArrowButton;
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
        // hide title and make window full-sized
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getSupportActionBar().hide();
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                             WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.main_menu_layout);
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
                //gameEngine.exitGame();
                exit();
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
        // create Buttons
        singlePlayerButton = findViewById(R.id.singlePlayerButton);
        singlePlayerButton.setOnClickListener(this);
        exitButton = findViewById(R.id.exitButton);
        exitButton.setOnClickListener(this);
        // create other UI related object
        mainMenuImage = findViewById(R.id.mainMenuImage);
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
    }
}
