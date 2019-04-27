package com.westerholmgmail.v.lauri.tunnelescape.resources;


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
    PlayerImage;


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
        map.put(ImageType.PlayerImage, "Flames.png"); //TODO replace this
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

}
