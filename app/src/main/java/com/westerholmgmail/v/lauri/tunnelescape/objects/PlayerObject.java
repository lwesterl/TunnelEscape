package com.westerholmgmail.v.lauri.tunnelescape.objects;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;

import com.westerholmgmail.v.lauri.tunnelescape.SinglePlayer;
import com.westerholmgmail.v.lauri.tunnelescape.Vector2f;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ImageType;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;

/**
 * @class PlayerObject
 * @brief Object which represent the player
 */
public class PlayerObject extends GameObject {
    public static volatile boolean boostPressed = false;
    public static volatile boolean lefPressed = false;
    public static volatile boolean rightPressed = false;

    private static float ForceX = 500000.f; // right
    private static float ForceY = -500000.f; // upwards

    /**
     * @brief Constructor
     * @details Uses PlayerImage and Player ObjectType to create GameObject
     * @param objectId matching id for PhysicsObject given by WorldWrapper
     */
    public PlayerObject(long objectId) {
        super(ImageType.PlayerImage, ObjectType.Player, objectId);
    }

    /**
     * @brief Draw Player to TunnelEscape
     * @param canvas drawing surface for the object
     */
    @Override
    public void draw(Canvas canvas) {
        Bitmap bitmap = ResourceManager.getBitmap(objectImage);
        if (bitmap != null) {
            canvas.drawBitmap(bitmap, x, y, new Paint());
            SinglePlayer.setPlayerPosition(x, y);
        }
        if (PlayerObject.boostPressed) {
            // draw also exhaust flames
            Bitmap flamesBitmap = ResourceManager.getBitmap(ImageType.ExhaustFlames);
            if (flamesBitmap != null) {
                // center the flames on the lower edge of the PlayerObject
                float exhaustFlamesX = x + 0.5f * getObjectWidth() - 0.5f * flamesBitmap.getWidth();
                canvas.drawBitmap(flamesBitmap, exhaustFlamesX, y + getObjectHeight(), new Paint());
            }

        }
    }


    /**
     * @brief Move player based on player input
     * @return force vector which should be applied to matching PhysicsObject
     */
    @Override
    public Vector2f move() {
        Vector2f force = new Vector2f();
        if (PlayerObject.boostPressed && PlayerObject.lefPressed && !PlayerObject.rightPressed) {
            force.update(-PlayerObject.ForceX, PlayerObject.ForceY);
        } else if (PlayerObject.boostPressed && PlayerObject.rightPressed && !PlayerObject.lefPressed) {
            force.update(PlayerObject.ForceX, PlayerObject.ForceY);
        } else if (PlayerObject.boostPressed) force.update(0.f, PlayerObject.ForceY);
        return force;
    }
}
