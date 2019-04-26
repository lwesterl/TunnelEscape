package com.westerholmgmail.v.lauri.tunnelescape.resources;


import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public enum ImageType {

    TestImage;

    /**< Map from ImageType values to asset paths */
    private final static Map<ImageType, String> imageTypeToStr = Collections.unmodifiableMap( Init() );

    /**
     * @@brief Create imageTypeToStr map
     * @return created map between ImageType values and image path in assets
     */
    private static HashMap<ImageType, String> Init() {
        HashMap<ImageType, String> map = new HashMap<>();
        map.put(ImageType.TestImage, "testi.png");
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
