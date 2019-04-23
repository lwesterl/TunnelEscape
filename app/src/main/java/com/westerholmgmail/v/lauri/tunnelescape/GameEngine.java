package com.westerholmgmail.v.lauri.tunnelescape;

import android.content.Context;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.Canvas;
import com.westerholmgmail.v.lauri.UI.GameState;
import com.westerholmgmail.v.lauri.UI.GameScreen;
import com.westerholmgmail.v.lauri.UI.MainMenu;

import java.util.HashMap;

/**
 * @brief Central class which creates and manages different game modes or statuses
 */

public class GameEngine extends SurfaceView implements SurfaceHolder.Callback {

    private GameLoop gameLoop; /**< another thread running the update and render loop */
    private HashMap<GameState, GameScreen> gameScreens = new HashMap<>();
    private GameState currentGameState;

    /**
     * @brief Constructor
     * @param context android context for the view
     */
    public GameEngine(Context context) {
        super(context);
        getHolder().addCallback(this);
        gameLoop = new GameLoop(getHolder(), this);
        setFocusable(true);
        CreateGameScreens();
    }

    /**
     * @brief Start the game loop
     * @param holder SurfaceHolder argument
     */
    @Override
    public void surfaceCreated(SurfaceHolder holder) {

        gameLoop.run();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    /**
     * @brief Stop the thread running GameLoop
     * @param holder SurfaceHolder argument
     */
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
     * @brief onTouchEvent implementation, just pass the event to correct GameScreen
     * @param event MotionEvent received
     * @return true: event handled
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        gameScreens.get(currentGameState).handleMotionEvent(event);
        return true;
    }

    /**
     * @brief Update game periodically
     * @details This should be called from GameLoop. This further calls correct GameScreen update
     */
    public void update() {
        gameScreens.get(currentGameState).update();
    }

    /**
     * @brief Render game periodically
     * @details This should be called from GameLoop. This further calls correct GameScreen render
     */
    public void render(Canvas canvas) {
        gameScreens.get(currentGameState).render(canvas);
    }

    /**
     * @brief Set currentGameState for GameEngine
     * @details This changes from one GameScreen to another
     * @param gameState
     */
    public void setGameState(GameState gameState) {
        // reset old GameScreen
        gameScreens.get(currentGameState).reset();
        currentGameState = gameState;
    }

    /**
     * @brief Create GameScreens and add those to gameScreens
     */
    private void CreateGameScreens() {
        gameScreens.put(GameState.MainMenu, new MainMenu(this));
        gameScreens.put(GameState.SinglePlayer, new SinglePlayer());
    }
}
