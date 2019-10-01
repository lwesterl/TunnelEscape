/**
 * @file GameState.java
 * @author Lauri Westerholm
 * @details Contains GameState: enum for different game states
 */

package games.tunnelescape.UI;

/**
 * @enum GameState
 * @brief Simple enum which hold current game state i.e. which screen should be rendered and
 * updated
 */
public enum GameState {
    MainMenu,
    SinglePlayer,
    AIPlayer
}
