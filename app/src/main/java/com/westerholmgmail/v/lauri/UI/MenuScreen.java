package com.westerholmgmail.v.lauri.UI;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;

import com.westerholmgmail.v.lauri.tunnelescape.GameEngine;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;
import com.westerholmgmail.v.lauri.tunnelescape.R;

public class MenuScreen extends AppCompatActivity implements View.OnClickListener {
    private Button singlePlayerButton;
    private Button exitButton;
    private ImageView mainMenuImage;
    private GameEngine gameEngine;


    static {
        // load native lib during start up
        System.loadLibrary("physics-lib");
    }


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
        gameEngine = findViewById(R.id.gameEngine);
        CreateUI();
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()) {
            case R.id.singlePlayerButton:
                hideMenu();
                gameEngine.setGameState(GameState.SinglePlayer);
                break;
            case R.id.exitButton:
                gameEngine.exitGame();
                break;
            default:
                System.out.println("Unhandled click");
        }
    }

    /**
     * @brief Create UI for TunnelEscape
     */
    private void CreateUI() {
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


}
