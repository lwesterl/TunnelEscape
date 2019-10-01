package games.tunnelescape.UI;

import android.graphics.Canvas;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import games.tunnelescape.tunnelescape.GameEngine;

/**
 * @brief Class which creates and updates the main menu
 * @details Currently not used
 */
public class MainMenu implements GameScreen, View.OnClickListener {

    private GameEngine gameEngine;
    private MenuScreen menuScreen;
    private Button startGameButton;
    private Button exitButton;

    /**
     * @brief Constructor
     * @param gameEngine GameEngine instance which should be invoked through button input
     */
    public MainMenu(GameEngine gameEngine, MenuScreen menuScreen) {

        this.gameEngine = gameEngine;
        this.menuScreen = menuScreen;
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

    @Override
    public void onClick(View v) {
        switch(v.getId()) {
            /*case R.id.SinglePlayerButton:
                gameEngine.setGameState(GameState.SinglePlayer);
                break;
            case R.id.ExitButton:
                gameEngine.exitGame();
                break;*/
            default:
                System.out.println("Unhandled click");
        }
    }
}
