package com.westerholmgmail.v.lauri.tunnelescape;

import android.content.Context;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.Canvas;

public class GameEngine extends SurfaceView implements SurfaceHolder.Callback {

    private GameLoop gameLoop; /**< another thread running the update and render loop */

    /**
     * @brief Constructor
     * @param context android context for the view
     */
    public GameEngine(Context context) {
        super(context);
        getHolder().addCallback(this);
        gameLoop = new GameLoop(getHolder(), this);
        setFocusable(true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        gameLoop.run();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        // stop gameLoop
        while (true) {
            try {
                gameLoop.setRunning(false);
                gameLoop.join();
                break;
            } catch (InterruptedException e) {
                System.out.println(e.getStackTrace());
            }
        }
    }

    /**
     * @brief Update game periodically
     * @details This should be called from GameLoop
     */
    public void update() {
    }

    /**
     * @brief Render game periodically
     * @details This should be called from GameLoop
     */
    public void render(Canvas canvas) {

    }
}
