/**
 * @file ImageObject.java
 * @author Lauri Westerholm
 * @details Contains ImageObject which is used to create non-physical objects
 */

package games.tunnelescape.tunnelescape.objects;

import games.tunnelescape.tunnelescape.resources.ImageType;

/**
 * @class ImageObject
 * @brief This extends StaticObject and just implements new constructor which won't take id
 * parameter. ImageObjects have separate incremented id so they must NOT be added to same container
 * than other GameObject (these object don't have physical counterparts)
 */
public class ImageObject extends StaticObject {

    private static long ImageObjectId = 0; /**< this id is incremented when new object is created */

    /**
     * @brief Constructor
     * @param objectImage Specifies image used to draw the object
     * @param x left edge position, this isn't moved
     * @param y upper edge position, this isn't moved
     */
    public ImageObject(ImageType objectImage, float x, float y) {
        super(objectImage, ObjectType.Texture, ImageObjectId);
        this.x = x;
        this.y = y;
        ImageObjectId ++;
    }
}
