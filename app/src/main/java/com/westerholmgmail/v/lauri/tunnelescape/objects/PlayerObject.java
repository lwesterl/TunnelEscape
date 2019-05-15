package com.westerholmgmail.v.lauri.tunnelescape.objects;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.Menu;

import com.westerholmgmail.v.lauri.tunnelescape.SinglePlayer;
import com.westerholmgmail.v.lauri.tunnelescape.Vector2f;
import com.westerholmgmail.v.lauri.tunnelescape.WorldWrapper;
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
    public static final float elasticity = 0.1f; /**< elasticity value, reduces bounciness a bit */
    public static final float density = 1.f; /**< use the standard density value from WorldWrapper */

    private static float ForceX = 500000.f; // right
    private static float ForceY = -500000.f; // upwards

    private boolean extraBoost = false; /**< used to detected when Player needs extra boost */
    private int HP = 100;

    /**
     * @brief Constructor
     * @details Uses Player and Player ObjectType to create GameObject
     * @param objectId matching id for PhysicsObject given by WorldWrapper
     */
    public PlayerObject(long objectId) {
        super(ImageType.Player, ObjectType.Player, objectId);
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
                float exhaustFlamesY = y + 0.66f * getObjectHeight(); // all of these value are pretty much defined based trial and error
                //float exhaustFlamesX = x + 0.5f * getObjectWidth() - 0.5f * flamesBitmap.getWidth();
                float exhaustFlamesX = x - flamesBitmap.getWidth() * 0.5f + 5.f;
                //canvas.drawBitmap(flamesBitmap, exhaustFlamesX, y + getObjectHeight(), new Paint());
                canvas.drawBitmap(flamesBitmap, exhaustFlamesX, exhaustFlamesY, new Paint());
                canvas.drawBitmap(flamesBitmap, x + getObjectWidth() - flamesBitmap.getWidth() + 5.f, exhaustFlamesY, new Paint());
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
        float forceY = extraBoost ? 20 * PlayerObject.ForceY : PlayerObject.ForceY;
        if (PlayerObject.boostPressed && PlayerObject.lefPressed && !PlayerObject.rightPressed) {
            force.update(-PlayerObject.ForceX, forceY);
        } else if (PlayerObject.boostPressed && PlayerObject.rightPressed && !PlayerObject.lefPressed) {
            force.update(PlayerObject.ForceX, forceY);
        } else if (PlayerObject.boostPressed) force.update(0.f, forceY);
        if (force.getY() != 0.f) extraBoost = false;
        return force;
    }

    /**
     * @brief Enables extra boost for following boost cycle
     */
    public void enableExtraBoost() { extraBoost = true; }

    /**
     * @brief Damage player
     * @param opponentType ObjectType for opponent object
     * @return true if player destroyed, otherwise false
     */
    public boolean damagePlayer(@ObjectType.ObjectTypeDef final int opponentType) {
        switch(opponentType) {
            case ObjectType.Barrier:
                HP -= 5;
                break;
            case ObjectType.Hazard:
                HP -= 20;
                break;
            default:
                break;
        }
        return HP <= 0;
    }

    /**
     * @brief Get PlayerObject HP
     * @return HP
     */
    public int getPlayerHP() { return HP; }
}
