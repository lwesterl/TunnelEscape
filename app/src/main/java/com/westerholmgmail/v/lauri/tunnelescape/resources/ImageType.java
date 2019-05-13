package com.westerholmgmail.v.lauri.tunnelescape.resources;


import com.westerholmgmail.v.lauri.tunnelescape.objects.ObjectType;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * @enum ImageType
 * @brief Specifies image type and path for the image
 */
public enum ImageType {

    BlackGround,
    DarkBrownGround,
    DarkBrownGroundMarks,
    DeepSky,
    ExhaustFlames,
    Flames,
    Grass,
    GrassMarks,
    GroundGrass,
    LightSky,
    Player,
    End;



    /**< Map from ImageType values to asset paths */
    private final static Map<ImageType, String> imageTypeToStr = Collections.unmodifiableMap( Init() );

    /**
     * @@brief Create imageTypeToStr map
     * @return created map between ImageType values and image paths in assets
     */
    private static HashMap<ImageType, String> Init() {
        HashMap<ImageType, String> map = new HashMap<>();
        map.put(ImageType.BlackGround, "BlackGround.png");
        map.put(ImageType.DarkBrownGround, "DarkBrownGround.png");
        map.put(ImageType.DarkBrownGroundMarks, "DarkBrownGroundMarks.png");
        map.put(ImageType.DeepSky, "DeepSky.png");
        map.put(ImageType.ExhaustFlames, "ExhaustFlames.png");
        map.put(ImageType.Flames, "Flames.png");
        map.put(ImageType.Grass, "Grass.png");
        map.put(ImageType.GrassMarks, "GrassMarks.png");
        map.put(ImageType.GroundGrass, "GroundGrass.png");
        map.put(ImageType.LightSky, "LightSky.png");
        map.put(ImageType.Player, "Player.png");
        map.put(ImageType.End, "End.png");
        return map;
    }

    /**< Map between ImageType strings and ImageTypes */
    private final static Map<String, ImageType> strToImageType = Collections.unmodifiableMap( Init2() );

    /**
     * @brief Initialize strToImageType
     * @return strToImageType
     */
    private static HashMap<String, ImageType> Init2() {
        HashMap<String, ImageType> map = new HashMap<>();
        map.put("BlackGround", ImageType.BlackGround);
        map.put("DarkBrownGround", ImageType.DarkBrownGround);
        map.put("DarkBrownGroundMarks", ImageType.DarkBrownGroundMarks);
        map.put("DeepSky", ImageType.DeepSky);
        map.put("ExhausFlames", ImageType.ExhaustFlames);
        map.put("Flames", ImageType.Flames);
        map.put("Grass", ImageType.Grass);
        map.put("GrassMarks", ImageType.GrassMarks);
        map.put("GroundGrass", ImageType.GroundGrass);
        map.put("LightSky", ImageType.LightSky);
        map.put("Player", ImageType.Player);
        map.put("End", ImageType.End);
        return map;
    }

    /**
     * @brief Get asset path for ImageType
     * @details ResourceManager uses this to load image resources
     * @param imageType tells requested image path
     * @return matching asset path, or null if no match for imageType (should be possible in normal situation)
     */
    public static String getImagePath(ImageType imageType) {
        return imageTypeToStr.get(imageType);
    }

    /**
     * @brief Get ImageType for matching string
     * @param typeName ImageType in string format
     * @return correct ImageType value
     */
    public static ImageType getImageType(final String typeName) { return strToImageType.get(typeName); }

    /**
     * @brief Convert ImageType to ObjectType
     * @param imageType enum value
     * @param imageObject true -> this object is used as texture (not added to PhysicsWorld)
     * @return matching ObjectType
     */
    public static @ObjectType.ObjectTypeDef int convertImageTypeToObjectType(final ImageType imageType, boolean imageObject) {
        if (imageObject) return ObjectType.Texture;
        if (imageType == Flames) return ObjectType.Hazard;
        if (imageType == BlackGround || imageType == DarkBrownGround || imageType == DarkBrownGroundMarks) return ObjectType.Barrier;
        if (imageType == Player) return ObjectType.Player;
        if (imageType == End) return ObjectType.End;
        return ObjectType.Ground;
    }

}
