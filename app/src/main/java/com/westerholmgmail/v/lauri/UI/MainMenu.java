package com.westerholmgmail.v.lauri.UI;

import android.graphics.Canvas;
import android.view.MotionEvent;

import com.westerholmgmail.v.lauri.UI.GameScreen;
import com.westerholmgmail.v.lauri.tunnelescape.GameEngine;

/**
 * @brief Class which creates and updates the main menu
 */
public class MainMenu implements GameScreen {

    private GameEngine gameEngine;

    /**
     * @brief Constructor
     * @param gameEngine GameEngine instance which should be invoked through button input
     */
    public MainMenu(GameEngine gameEngine) {
        this.gameEngine = gameEngine;
    }

    @Override
    public void update() {

    }

    @Override
    public void render(Canvas canvas) {

    }

    @Override
    public void reset() {

    }

    @Override
    public void handleMotionEvent(MotionEvent motionEvent) {

    }
}
