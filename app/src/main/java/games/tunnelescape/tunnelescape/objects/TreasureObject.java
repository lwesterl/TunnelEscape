package games.tunnelescape.tunnelescape.objects;

import java.util.concurrent.ThreadLocalRandom;

import games.tunnelescape.tunnelescape.resources.ImageType;

/**
 * @class TreasureObject
 * @brief Object for Treasures, provides wrapper for StaticObject
 */
public class TreasureObject extends StaticObject {

    public static final float Density = 0.f;
    public static final float Elasticity = 0.1f;
    private static final int MinRand = ImageType.Coin.toInt();
    private static final int MaxRand = ImageType.Diamond.toInt();
    private static ImageType TreasureImage = TreasureObject.RandImageType();

    /**
     * @brief Constructor
     * @param Id this must match WorldWrapper PhysicsObject id
     */
    public TreasureObject(long Id) {
        super(TreasureImage, ObjectType.Treasure, Id);
        TreasureObject.TreasureImage = TreasureObject.RandImageType(); // update new rand image
    }

    /**
     * @brief Randomly choose ImageType from Treasure images
     * @return randomly chosen Treasure ImageType
     */
    private static ImageType RandImageType() {
        int rand = ThreadLocalRandom.current().nextInt(TreasureObject.MinRand, TreasureObject.MaxRand + 1);
        return ImageType.fromInt(rand);
    }

    /**
     * @brief Get current ImageType used for TreasureObject
     * @return TreasureImage
     */
    public static ImageType getCurrentImageType() { return TreasureObject.TreasureImage; }

    /**
     * @brief Get random x position for TreasureObject
     * @param minX level smallest x coordinate
     * @param maxX level greatest x coordinate
     * @return random x coordinate between the min and max values
     */
    public static float getRandomX(float minX, float maxX) {
        return (float) ThreadLocalRandom.current().nextInt((int) minX, (int) maxX);
    }

    /**
     * @brief Get random y position for TreasureObject
     * @param minY level smallest y coordinate
     * @param maxY level greatest y coordinate
     * @return random x coordinate between the min and max values
     */
    public static float getRandomY(float minY, float maxY) {
        return (float) ThreadLocalRandom.current().nextInt((int) minY, (int) maxY);
    }
}
