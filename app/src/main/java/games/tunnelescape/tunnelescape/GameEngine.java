/**
 * @file GameEngine.java
 * @author Lauri Westerholm
 * @details Contains GameEngine which is one of the central classes for the game
 */

package games.tunnelescape.tunnelescape;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.Canvas;

import games.tunnelescape.UI.GameState;
import games.tunnelescape.UI.GameScreen;
import games.tunnelescape.UI.MenuScreen;
import games.tunnelescape.tunnelescape.objects.PlayerObject;
import games.tunnelescape.tunnelescape.resources.AudioManager;
import games.tunnelescape.tunnelescape.resources.AudioType;

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
     * Get game mode that matched Score server ids, these must absolute match the ScoreServer database counterparts
     * @param hardDifficulty whether difficulty is hard
     * @return ScoreServer database GameModes id
     */
    public static int getGameMode(boolean hardDifficulty) {
        return hardDifficulty ? 2 : 1;
    }

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
        JoinGameLoop();
        gameScreens.get(currentGameState).reset();
        currentGameState = GameState.MainMenu;
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
     * @brief Get current GameState
     * @return currentGameState
     */
    public GameState getCurrentGameState() { return currentGameState; }

    /**
     * @brief Create GameScreens and add those to gameScreens
     */
    private void CreateGameScreens() {
        gameScreens.put(GameState.SinglePlayer, new SinglePlayer(context));
        gameScreens.put(GameState.AIPlayer, new AIPlayer(context));
        // TODO add possible other game modes
    }


    public void exitGame() {}

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

    /**
     * @brief Join GameLoop, i.e. kill the worker thread
     */
    private void JoinGameLoop() {
        if (gameLoop.getRunning()) {
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
    }

}
