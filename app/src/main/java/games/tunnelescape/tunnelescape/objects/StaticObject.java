package games.tunnelescape.tunnelescape.objects;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;

import games.tunnelescape.tunnelescape.Vector2f;
import games.tunnelescape.tunnelescape.resources.ImageType;
import games.tunnelescape.tunnelescape.resources.ResourceManager;

/**
 * @class StaticObject
 * @brief Implements static objects which have PhysicsObject counterpart in PhysicsWorld
 * @details StaticObject should be used to create static objects which can be collided and interacted
 */
public class StaticObject extends GameObject {

    /**
     * @brief Constructor
     * @param objectImage specifies which image is used for the StaticObject
     * @param objectType specifies StaticObject type, this should be used to implement some game logic
     * @param Id This must match PhysicsObject id, this object is fetched based on this id
     */
    public StaticObject(ImageType objectImage, @ObjectType.ObjectTypeDef int objectType, long Id) {
        super(objectImage, objectType, Id);
    }

    /**
     * @brief Draw StaticObject
     * @param canvas drawing surface for the object
     */
    public void draw(Canvas canvas) {
        Bitmap bitmap = ResourceManager.getBitmap(objectImage);
        if (bitmap != null) {
            canvas.drawBitmap(bitmap, x, y, new Paint());
        }
    }

    /**
     * @brief Move implementation, left intentionally plain
     * @return empty native Vector2f
     */
    public Vector2f move() {
        return new Vector2f();
    }
}
