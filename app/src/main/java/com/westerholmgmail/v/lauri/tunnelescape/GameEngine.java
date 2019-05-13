package com.westerholmgmail.v.lauri.tunnelescape;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.Canvas;
import android.view.View;

import com.westerholmgmail.v.lauri.UI.GameState;
import com.westerholmgmail.v.lauri.UI.GameScreen;
import com.westerholmgmail.v.lauri.UI.MenuScreen;
import com.westerholmgmail.v.lauri.tunnelescape.objects.PlayerObject;
import com.westerholmgmail.v.lauri.tunnelescape.resources.AudioManager;
import com.westerholmgmail.v.lauri.tunnelescape.resources.AudioType;

import java.util.HashMap;

/**
 * @class GameEngine
 * @brief Central class which creates and manages different game modes or statuses
 */

public class GameEngine extends SurfaceView implements SurfaceHolder.Callback {

    private GameLoop gameLoop; /**< another thread running the update and render loop */
    private GameState currentGameState = GameState.MainMenu;
    private HashMap<GameState, GameScreen> gameScreens = new HashMap<>();
    private Context context;
    private MenuScreen menuScreen;

    /**
     * @brief Constructor
     * @param context android context for the view
     * @param attributeSet AttributeSet
     */
    public GameEngine(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);
        this.context = context;
        init();
    }

    /**
     * @brief Another constructor
     * @param context android context for the view
     */
    public GameEngine(Context context) {
        super(context);
        this.context = context;
        init();
    }

    /**
     * @brief Another constructor
     * @param context android context for the view
     * @param attributeSet AttributeSet
     * @param defStyle android style parameter
     */
    public GameEngine(Context context, AttributeSet attributeSet, int defStyle) {
        super(context, attributeSet, defStyle);
        this.context = context;
        init();
    }

    /**
     * @brief Start the game loop
     * @param holder SurfaceHolder argument
     */
    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        gameLoop.setRunning(true);
        gameLoop.start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        // TODO implement

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
        GameScreen gameScreen = gameScreens.get(currentGameState);
        if (gameScreen != null) {
            gameScreen.handleMotionEvent(event);
            return true;
        }
        return false; // event shouldn't be handled by GameEngine
    }

    /**
     * @brief Init GameEngine
     */
    private void init() {
        this.menuScreen = (MenuScreen) context;
        //setZOrderOnTop(false);
        getHolder().addCallback(this);
        setFocusable(true);
        CreateGameScreens();
        gameLoop = new GameLoop(getHolder(), this);
    }

    /**
     * @brief Update game periodically
     * @details This should be called from GameLoop. This further calls correct GameScreen update
     */
    public void update() {
        GameScreen gameScreen = gameScreens.get(currentGameState);
        if (gameScreen != null) gameScreen.update();
    }

    /**
     * @brief Render game periodically
     * @details This should be called from GameLoop. This further calls correct GameScreen render
     */
    public void render(Canvas canvas) {
        GameScreen gameScreen = gameScreens.get(currentGameState);
        if (gameScreen != null) gameScreen.render(canvas);
    }

    /**
     * @brief Set currentGameState for GameEngine
     * @details This changes from one GameScreen to another
     * @param gameState new GameState
     */
    public void setGameState(GameState gameState) {
        // reset old GameScreen
        GameScreen gameScreen = gameScreens.get(currentGameState);
        if (gameScreen != null) gameScreen.reset();
        currentGameState = gameState;
    }

    /**
     * @brief Create GameScreens and add those to gameScreens
     */
    private void CreateGameScreens() {
        View view = ((Activity)context).getWindow().getDecorView().findViewById(android.R.id.content);
        gameScreens.put(GameState.SinglePlayer, new SinglePlayer(context));
        // TODO add possible other game modes
    }


    public void exitGame() {
        System.out.println("______________________Exit____________________ ");
        // TODO clear game related stuff properly
        menuScreen.exit();
    }

    /**
     * @brief boostButton is touched, this forwards the touch
     * @param pressed whether button is pressed or released
     */
    public void boostButtonClicked(boolean pressed) {
        PlayerObject.boostPressed = pressed;
        if (pressed) AudioManager.playAudio(AudioType.BoostAudio, true);
        else AudioManager.playAudio(AudioType.BoostAudio, false);
    }

    /**
     * @brief leftButton is touched, this forwards the touch
     * @param pressed whether button is pressed or released
     */
    public void leftButtonClicked(boolean pressed) {
        PlayerObject.lefPressed = pressed;
    }

    /**
     * @brief rightButton is touched, this forwards the touch
     * @param pressed whether button is pressed or released
     */
    public void rightButtonClicked(boolean pressed) {
        PlayerObject.rightPressed = pressed;
    }
}
