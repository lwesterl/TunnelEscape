package com.westerholmgmail.v.lauri.tunnelescape;

import android.graphics.Canvas;
import android.view.SurfaceHolder;

/**
 * @brief Class which implements and runs the game loop
 * @details Uses Thread to create another thread used purely for game loop. Game is running with locked
 * frame rate
 */

public class GameLoop extends Thread {

    static final long FrameRate = 60;
    private static Canvas canvas;
    SurfaceHolder surfaceHolder;
    private GameEngine gameEngine;
    private volatile boolean running;

    /**
     * @brief Constructor
     * @param surfaceHolder used to lock surface
     * @param gameEngine GameEngine which should be run
     */
    GameLoop(SurfaceHolder surfaceHolder, GameEngine gameEngine) {
        super();
        this.surfaceHolder = surfaceHolder;
        this.gameEngine = gameEngine;
        running = false;
    }

    /**
     * @brief Crates thread and starts running gameEngine
     */
    @Override
    public void run() {
        long prevTime = System.nanoTime();
        long timeInterval = 1000000000 / GameLoop.FrameRate; // in nanos
        while (running) {
            long currentTime = System.nanoTime();
            if (currentTime - prevTime > timeInterval) {
                // time to update and render
                prevTime = currentTime;
                GameLoop.canvas = null;

                try {
                    GameLoop.canvas = surfaceHolder.lockCanvas();
                    synchronized (surfaceHolder) {
                        gameEngine.update();
                        gameEngine.draw(GameLoop.canvas);
                    }
                } catch (Exception e) {
                    System.out.println(e.getStackTrace());
                } finally {
                    if(GameLoop.canvas != null) {
                        try {
                            surfaceHolder.unlockCanvasAndPost(GameLoop.canvas);
                        } catch (Exception e) {
                            System.out.println(e.getStackTrace());
                        }

                    }
                }

                // sleep some time to reduce unnecessary loop cycles
                long sleepTime = timeInterval - (System.nanoTime() - prevTime); // in nanos
                sleepTime /= 1000000; // in millis
                if (sleepTime > 0) {
                    try {
                        sleep(sleepTime);
                    } catch (InterruptedException e) {
                        System.out.println(e.getStackTrace());
                    }
                }

            }
        }
    }

    /**
     * @brief Start or stop the game loop
     * @param running false -> stop the game loop
     */
    public void setRunning(boolean running) {
        this.running = running;
    }

}
