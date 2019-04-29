package com.westerholmgmail.v.lauri.tunnelescape.objects;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;

import com.westerholmgmail.v.lauri.tunnelescape.Vector2f;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ImageType;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;

/**
 * @class ImageObject
 * @brief This class implement objects which have only image and no PhysicsObject in PhysicsWorld
 * @details These object are intended to be used as background textures.
 * This also means that these object must be drawn first so that they don't get drawn on top of other objects.
 * @remark These object must be added to another container than other GameObjects
 */
public class ImageObject extends GameObject {
    static private long Id = 0; /**< These object don't use the same ids as other GameObjects, should be stored in another container */

    /**
     * @brief Constructor
     * @param imageType correct ImageType
     * @param x position x coordinate, left corner
     * @param y position y coordinate, upper corner
     */
    public ImageObject(ImageType imageType, float x, float y) {
        super(imageType, ObjectType.Texture, ImageObject.Id);
        this.x = x;
        this.y = y;
        ImageObject.Id ++; // keep these unique
    }

    /**
     * @brief Draw ImageObject
     * @param canvas drawing surface for the object
     */
    @Override
    public void draw(Canvas canvas) {
        Bitmap bitmap = ResourceManager.getBitmap(objectImage);
        if (bitmap != null) {
            canvas.drawBitmap(bitmap, x, y, new Paint());
        }
    }

    /**
     * @brief This should be empty
     * @return empty Vector2f
     */
    @Override
    public Vector2f move() {
        return new Vector2f();
    }

    /**
     * @brief update object position
     * @param position This is measured from the left upper corner of the object
     */
    @Override
    public void updatePosition(Vector2f position) {
        x = position.getX();
        y = position.getY();
    }


}
