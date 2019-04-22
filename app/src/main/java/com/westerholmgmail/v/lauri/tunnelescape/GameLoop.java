package com.westerholmgmail.v.lauri.tunnelescape;

import android.graphics.Canvas;
import android.view.SurfaceHolder;

public class GameLoop extends Thread {

    static final long FrameRate = 60;
    private static Canvas canvas;
    SurfaceHolder surfaceHolder;
    private GameEngine gameEngine;
    private volatile boolean running;


    GameLoop(SurfaceHolder surfaceHolder, GameEngine gameEngine) {
        super();
        this.surfaceHolder = surfaceHolder;
        this.gameEngine = gameEngine;
        running = true;
    }

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

    public void setRunning(boolean running) {
        this.running = running;
    }

}
