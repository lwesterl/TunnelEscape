package com.westerholmgmail.v.lauri.tunnelescape.objects;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;

import com.westerholmgmail.v.lauri.tunnelescape.Vector2f;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ImageType;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;

/**
 * @class PlayerObject
 * @brief Object which represent the player
 */
public class PlayerObject extends GameObject {

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
        if (bitmap != null) canvas.drawBitmap(bitmap, x, y, new Paint());
    }


    /**
     * @brief Move player based on player input
     * @return force vector which should be applied to matching PhysicsObject
     */
    @Override
    public Vector2f move() {
        return new Vector2f();
    }
}
