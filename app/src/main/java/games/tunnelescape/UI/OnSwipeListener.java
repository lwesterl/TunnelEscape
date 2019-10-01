/**
 * @file OnSwipeListener.java
 * @author Lauri Westerholm
 * @details Contains OnSwipeListener which is used for detecting swipe events
 */

package games.tunnelescape.UI;

import android.content.Context;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;

/**
 * @class OnSwipeListener
 * Handles swipe event, remember to Override onSwipeLeft and onSwipeRight when applied.
 * This handles only left and right swipes
 */
public class OnSwipeListener implements View.OnTouchListener {

    private final GestureDetector gestureDetector;

    /**
     * Constructor
     * @param context pass MenuScreen as context
     */
    public OnSwipeListener(Context context) {
        gestureDetector = new GestureDetector(context, new GestureListener());
    }

    /**
     * Implement handler for onTouch events
     * @param v View which created the event
     * @param event event itself
     * @return true if event handled
     */
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        return gestureDetector.onTouchEvent(event);
    }

    /**
     * Implement this when object is created
     */
    public void onSwipeLeft() {
    }

    /**
     * Implement this when object is created
     */
    public void onSwipeRight() {
    }

    /**
     * @class GestureListener
     * Used to detect Gestures
     */
    private final class GestureListener extends GestureDetector.SimpleOnGestureListener {

        private static final int SwipeDistanceTrigger = 100;
        private static final int SwipeVelocityTrigger = 100;

        @Override
        public boolean onDown(MotionEvent motionEvent) { return true; }

        /**
         * Detect left and right swipes
         * @param motionEvent1 received event start
         * @param motionEvent2 received event end
         * @param velocityX x dimensional swipe velocity
         * @param velocityY y dimensional swipe velocity
         * @return true if swipe handled, otherwise false
         */
        @Override
        public boolean onFling(MotionEvent motionEvent1, MotionEvent motionEvent2, float velocityX, float velocityY) {
            float distanceX = motionEvent2.getX() - motionEvent1.getX();
            float distanceY = motionEvent2.getY() - motionEvent1.getY();
            if (Math.abs(distanceX) > Math.abs(distanceY) && Math.abs(distanceX) > SwipeDistanceTrigger && Math.abs(velocityX) > SwipeVelocityTrigger) {
                if (distanceX > 0) onSwipeRight();
                else onSwipeLeft();
                return true;
            }
            return false;
        }
    }

}

