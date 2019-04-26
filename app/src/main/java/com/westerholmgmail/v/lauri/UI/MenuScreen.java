package com.westerholmgmail.v.lauri.UI;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import com.westerholmgmail.v.lauri.tunnelescape.GameEngine;
import com.westerholmgmail.v.lauri.tunnelescape.R;

public class MenuScreen extends AppCompatActivity implements View.OnClickListener {
    private Button singlePlayerButton;
    private Button exitButton;
    private GameEngine gameEngine;

    // load native lib during start up
    static {
        System.loadLibrary("physics-lib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // hide title and make window full-sized
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                             WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.main_menu_layout);
        gameEngine = findViewById(R.id.gameEngine);
        addButtons();
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()) {
            case R.id.singlePlayerButton:
                gameEngine.setGameState(GameState.SinglePlayer);
                break;
            case R.id.exitButton:
                gameEngine.exitGame();
                break;
            default:
                System.out.println("Unhandled click");
        }
    }

    public void addButtons() {
        singlePlayerButton = findViewById(R.id.singlePlayerButton);
        singlePlayerButton.setOnClickListener(this);
        exitButton = findViewById(R.id.exitButton);
        exitButton.setOnClickListener(this);
    }


}
