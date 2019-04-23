package com.westerholmgmail.v.lauri.tunnelescape;

import android.graphics.Canvas;
import android.view.MotionEvent;

import com.westerholmgmail.v.lauri.UI.GameScreen;

/**
 * @brief Class which implements main framework for single player game mode
 */
public class SinglePlayer implements GameScreen {

    private WorldWrapper worldWrapper;

    /**
     * @brief Constructor
     */
    public SinglePlayer() {
        worldWrapper = new WorldWrapper();
    }

    @Override
    public void update() {

    }

    @Override
    public void render(Canvas canvas) {

    }

    @Override
    public void reset() {
        // create new WorldWrapper
        if (worldWrapper != null) {
            worldWrapper.delete();
        }
        worldWrapper = new WorldWrapper();
    }

    @Override
    public void handleMotionEvent(MotionEvent motionEvent) {

    }

    public void loadLevel() {

    }


}
