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
    private int count = 0;
    private static float ForceX = 500000.f; // right
    private static float ForceY = -1000000.f; // upwards

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
    }


    /**
     * @brief Move player based on player input
     * @return force vector which should be applied to matching PhysicsObject
     */
    @Override
    public Vector2f move() {
        count ++;
        Vector2f force = new Vector2f();
        if (count == 20) {
            force.update(PlayerObject.ForceX, PlayerObject.ForceY);
            count = 0;
        }
        return force;
    }
}
