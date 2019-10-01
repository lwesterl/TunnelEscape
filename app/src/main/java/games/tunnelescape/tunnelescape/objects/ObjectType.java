/**
 * @file ObjectType
 * @author Lauri Westerholm
 * @details Contains ObjectType: object type constants
 */

package games.tunnelescape.tunnelescape.objects;

import android.support.annotation.IntDef;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * @class ObjectType
 * @brief Hold constant values for different object types
 */
public class ObjectType {
    @Retention(RetentionPolicy.SOURCE)
    @IntDef ({Player, Ground, Barrier, Hazard, Enemy, Texture, End, Treasure})
    public @interface ObjectTypeDef {}

    public static final int Player = 0;
    public static final int Ground = 1;
    public static final int Barrier = 2;
    public static final int Hazard = 3;
    public static final int Enemy = 4;
    public static final int Texture = 5;
    public static final int End = 6;
    public static final int Treasure = 7;

    public final int objectType;

    /**
     * @brief Validates int
     * @param objectType constant value in ObjectTypeDef
     */
    public ObjectType(@ObjectTypeDef int objectType) {
        this.objectType = objectType;
    }

}

