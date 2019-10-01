/**
 * @file GameScreen.java
 * @author Lauri Westerholm
 * Contains GameScreen: base class for different game modes / screens
 */

package games.tunnelescape.UI;

import android.graphics.Canvas;
import android.view.MotionEvent;

/**
 * @brief Interface for different game screens
 * @details Each GameScreen should implement at least update, render, reset and handleMotionEvent methods
 * The screens itself should be crated and updated from GameEngine
 */
public interface GameScreen {

    /**
     * @brief Update the screen periodically, e.g. update object positions
     */
    void update();

    /**
     * @brief Render the screen periodically, e.g. redraw all object which need to be drawn
     */
    void render(Canvas canvas);

    /**
     * @brief Reset the screen to safe state
     */
    void reset();

    /**
     * @brief Handle incoming motion event
     * @param motionEvent should be passed by GameEngine
     */
    void handleMotionEvent(MotionEvent motionEvent);
}
