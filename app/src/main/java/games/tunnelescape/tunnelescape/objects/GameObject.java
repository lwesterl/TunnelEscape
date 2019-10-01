/**
 * @file GameObject.java
 * @author Lauri Westerholm
 * @details Abstract class for objects used in the game
 */

package games.tunnelescape.tunnelescape.objects;

import android.graphics.Canvas;

import games.tunnelescape.tunnelescape.Vector2f;
import games.tunnelescape.tunnelescape.resources.ImageType;
import games.tunnelescape.tunnelescape.resources.ResourceManager;

/**
 * @class GameObject
 * @brief Abstract class representing one object in the game
 * @details Inherit all object classes from this class and implement basic methods
 */
public abstract class GameObject {
    protected long objectId; /**< this will match the id in WorldWrapper */
    protected ImageType objectImage; /**< enum which tells correct image for the object */
    protected float x; /**< x dimensional position in the world, left corner */
    protected float y; /**< y dimensional position in the world, upper corner */
    protected @ObjectType.ObjectTypeDef int objectType; /**< ObjectType tells which object this is */

    /**
     * @brief Constructor
     * @param objectImage image for the main object
     * @param objectType tells object type
     * @param objectId objectId in the WorldWrapper
     */
    protected GameObject(ImageType objectImage, @ObjectType.ObjectTypeDef int objectType, long objectId) {
        this.objectImage = objectImage;
        this.objectType = objectType;
        this.objectId = objectId;
    }

    /**
     * @brief Draw object, implemented in inherited classes
     * @param canvas drawing surface for the object
     */
    public abstract void draw(Canvas canvas);

    /**
     * @brief Move the PhysicsObject
     * @return tells force applied to the physicsObject
     */
    public abstract Vector2f move();

    /**
     * @brief Update object position
     * @param position This is measured from the center of the object so transform is applied
     * @details Call this after each update cycle from SinglePlayer to update object positions to
     * match physical object position in WorldWrapper
     */
    public void updatePosition(Vector2f position) {
        x = position.getX() - getObjectWidth()/2.f;
        y = position.getY() - getObjectHeight()/2.f;
    }

    /**
     * @brief Get GameObject width
     * @return return matching bitmap width or 0 if there is no matching bitmap
     */
    public float getObjectWidth() {
        return ResourceManager.getImageWidth(objectImage);
    }

    /**
     * @brief Get GameObject height
     * @return return matching bitmap height or 0 if there is no matching bitmap
     */
    public float getObjectHeight() {
        return ResourceManager.getImageHeight(objectImage);
    }

    /**
     * @brief Get GameObject ObjectType
     * @return objectType
     */
    public @ObjectType.ObjectTypeDef int getObjectType() { return objectType; }

    /**
     * @brief Get objectId
     * @return objectId
     */
    public long getObjectId() { return objectId; }



}
