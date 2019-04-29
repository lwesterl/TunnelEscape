package com.westerholmgmail.v.lauri.tunnelescape.objects;

import android.support.annotation.IntDef;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * @class ObjectType
 * @brief Hold constant values for different object types
 */
public class ObjectType {
    @Retention(RetentionPolicy.SOURCE)
    @IntDef ({Player, Ground, Hazard, Enemy, Texture})
    public @interface ObjectTypeDef {}

    public static final int Player = 0;
    public static final int Ground = 1;
    public static final int Hazard = 2;
    public static final int Enemy = 3;
    public static final int Texture = 4;

    public final int objectType;

    /**
     * @brief Validates int
     * @param objectType constant value in ObjectTypeDef
     */
    public ObjectType(@ObjectTypeDef int objectType) {
        this.objectType = objectType;
    }

}

