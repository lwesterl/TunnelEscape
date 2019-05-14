package com.westerholmgmail.v.lauri.tunnelescape;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.support.annotation.ColorInt;
import android.view.MotionEvent;

import com.westerholmgmail.v.lauri.UI.GameScreen;
import com.westerholmgmail.v.lauri.UI.MenuScreen;
import com.westerholmgmail.v.lauri.tunnelescape.objects.GameObject;
import com.westerholmgmail.v.lauri.tunnelescape.objects.ObjectType;
import com.westerholmgmail.v.lauri.tunnelescape.objects.PlayerObject;
import com.westerholmgmail.v.lauri.tunnelescape.objects.StaticObject;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ImageType;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * @class SinglePlayer
 * @brief Class which implements main framework for single player game mode
 */
public class
SinglePlayer implements GameScreen {

    public static int UIBarHeight = 80; /**< tells the height of UI bar which is positioned on the lower edge of the screen, this must be match single_player_layout */
    private static Vector2f playerPosition = new Vector2f(0.f, 0.f);
    private final static int maxDiffX = 2 * (int) ResourceManager.getImageWidth(ImageType.Player); // used to detect when canvas should be transformed
    private final static int maxDiffY = UIBarHeight + 2 * (int) ResourceManager.getImageHeight(ImageType.Player); // used to detect when canvas should be transformed

    private WorldWrapper worldWrapper;
    private Context context;
    private HashMap<Long, GameObject> gameObjects = new HashMap<>();
    private ArrayList<GameObject> imageObjects = new ArrayList<>(); // these don't have PhysicsObject counterpart
    private @ColorInt int backgroundColor = Color.WHITE;
    private int canvasMultiplierX = 0;
    private int canvasMultiplierY = 0;


    /**
     * @brief Constructor
     */
    public SinglePlayer(Context context) {
        this.context = context;
        worldWrapper = new WorldWrapper();
        loadLevel("Level1.tescape"); // TODO implement properly
    }

    /**
     * @brief Update objects and game status based on PhysicsWorld
     */
    @Override
    public void update() {
        // update PhysicsWorld via WorldWrapper
        PairDeque collided = worldWrapper.update();
        if (! GameLogicUpdate(collided)) {
            // exit single player
        }
        // update GameObject positions
        for (HashMap.Entry<Long, GameObject> item : gameObjects.entrySet()) {
            GameObject gameObject = item.getValue();
            Vector2f position = worldWrapper.fetchPosition(gameObject.getObjectId()).getPosition();
            gameObject.updatePosition(position);
            // move also matching PhysicsObject
            Vector2f force = gameObject.move();
            if (force.getX() != 0.f || force.getY() != 0.f) {
                worldWrapper.setObjectForce(gameObject.getObjectId(), force);
            }
        }
    }

    /**
     * @brief Draw single player TunnelEscape
     * @param canvas drawing surface
     */
    @Override
    public void render(Canvas canvas) {
        transferCanvas(canvas);
        canvas.drawColor(backgroundColor);
        for (HashMap.Entry<Long, GameObject> item : gameObjects.entrySet()) {
            item.getValue().draw(canvas);
        }
        for (GameObject imageObject : imageObjects) {
            imageObject.draw(canvas);
        }

    }

    @Override
    public void reset() {
        //TODO implement properly
        // create new WorldWrapper
        if (worldWrapper != null) {
            worldWrapper.delete();
        }
        worldWrapper = new WorldWrapper();
    }

    @Override
    public void handleMotionEvent(MotionEvent motionEvent) {

    }

    /**
     * @brief Add object to WorldWrapper and gameObjects
     * @param objectType ObjectType, int constant
     * @param imageType ImageType
     * @param x Left corner position
     * @param y Upper corner position
     */
    public void addObject(@ObjectType.ObjectTypeDef int objectType, ImageType imageType, float x, float y) {
        long id = 0;
        // WorldWrapper needs object central coordinates
        float x_center = x + ResourceManager.getImageWidth(imageType)/2.f;
        float y_center = y + ResourceManager.getImageHeight(imageType)/2.f;
        GameObject gameObject = null;
        switch (objectType) {
            case ObjectType.Player:
                id = worldWrapper.addObject(false, new Vector2f(x_center, y_center),
                        ResourceManager.getImageWidth(imageType), ResourceManager.getImageHeight(imageType));
                setPlayerPosition(x, y);
                gameObject = new PlayerObject(id);
                worldWrapper.setObjectPhysicsProperties(id, PlayerObject.elasticity, PlayerObject.density);
                break;
            case ObjectType.Ground:
                id = worldWrapper.addObject(true, new Vector2f(x_center, y_center),
                        ResourceManager.getImageWidth(imageType), ResourceManager.getImageHeight(imageType));
                gameObject = new StaticObject(imageType, objectType, id);
                break;
            case ObjectType.Barrier:
                id = worldWrapper.addObject(true, new Vector2f(x_center, y_center),
                        ResourceManager.getImageWidth(imageType), ResourceManager.getImageHeight(imageType));
                gameObject = new StaticObject(imageType, objectType, id);
                break;
            case ObjectType.Hazard:
                id = worldWrapper.addObject(true, new Vector2f(x_center, y_center),
                        ResourceManager.getImageWidth(imageType), ResourceManager.getImageHeight(imageType));
                gameObject = new StaticObject(imageType, objectType, id);
                break;
            case ObjectType.Texture:
                gameObject = new ImageObject(imageType, x, y); // this has no PhysicsObject in PhysicsWorld
                break;
            case ObjectType.Enemy:
                break;
            default:
                // gameObject remains null if this scope is entered
                System.out.println("Cannot add object");
        }
        // add gameObject to gameObjects
        if (gameObject != null && objectType != ObjectType.Texture) {
            gameObjects.put(id, gameObject);
        } else imageObjects.add(gameObject);
    }

    /**
     * @brief Load level
     * @param levelName specifies level to load
     * @return true if successful, otherwise false
     */
    public boolean loadLevel(String levelName) {
        // set correct gravity values
        PhysicsProperties.setGravityY(20000.f);
        //addObject(ObjectType.Player, ImageType.Player, 300.f, 0.f);
        try {
            InputStream inputStream = context.getAssets().open(levelName);
            InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
            BufferedReader br = new BufferedReader(inputStreamReader);
            String line;
            try {
                while ((line = br.readLine()) != null) {
                    String[] content = line.split(",");
                    ParseLevelContent(content);
                }
                return true;
            } catch (java.io.IOException e) {
                e.printStackTrace();
            }

        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    /**
     * @brief Parse level content to new object
     * @param content contains one input file line in array of Strings
     */
    private void ParseLevelContent(String[] content) {
        int i;
        float x = 0.f, y = 0.f;
        boolean imageObject = false;
        String imageTypeStr = "";
        for (i = 0; i < content.length; i++) {
            switch (i) {
                case 0:
                    // should be ImageType as string
                    imageTypeStr = content[i].trim();
                    break;
                case 1:
                    // should be x position
                    x = Float.valueOf(content[i].trim()).floatValue();
                    break;
                case 2:
                    // should be y position
                    y = Float.valueOf(content[i].trim()).floatValue();
                    break;
                case 3:
                    // should be width, not used
                    break;
                case 4:
                    // should be height, not used
                    break;
                case 5:
                    // should be "ImageObject" or "PhysicsObject"
                    if (content[i].trim().equals("ImageObject")) imageObject = true;
                    break;
            }
        }
        if (i == 6) {
            // parse successful, add object
            ImageType imageType = ImageType.getImageType(imageTypeStr);
            @ObjectType.ObjectTypeDef int objectType = ImageType.convertImageTypeToObjectType(imageType, imageObject);
            addObject(objectType, imageType, x, y);
        }
    }

    /**
     * @brief Set playerPosition
     * @remark Call this from PlayerObject draw (do not call this elsewhere)
     * @param x current player x coordinate
     * @param y current player y coordinate
     */
    public static void setPlayerPosition(float x, float y) {
        SinglePlayer.playerPosition.update(x, y);
    }

    /**
     * @brief Set correct transform for canvas based on playerPosition and screen size
     * @param canvas to be transformed
     * @remark change maxDiffY and maxDiffX if needed
     */
    private void transferCanvas(Canvas canvas) {
        if ((int) playerPosition.getX() > ((canvasMultiplierX + 1) * (MenuScreen.ScreenWidth - SinglePlayer.maxDiffX))) {
            canvasMultiplierX++;
        }
        else if ((int) playerPosition.getX() < (canvasMultiplierX * (MenuScreen.ScreenWidth - SinglePlayer.maxDiffX))) {
            canvasMultiplierX--;
        }
        if ((int) playerPosition.getY() > ((canvasMultiplierY + 1) * (MenuScreen.ScreenHeight - SinglePlayer.maxDiffY))) {
            canvasMultiplierY++;
        }
        else if ((int) playerPosition.getY() < (canvasMultiplierY * (MenuScreen.ScreenHeight - SinglePlayer.maxDiffY))) {
            canvasMultiplierY--;
        }
        canvas.translate((float) (-canvasMultiplierX * (MenuScreen.ScreenWidth - SinglePlayer.maxDiffX)),
                         (float) (-canvasMultiplierY * (MenuScreen.ScreenHeight - SinglePlayer.maxDiffY)));

    }

    /**
     * @brief Update game based on collisions, todo
     * @param collided deque of collision pairs
     * @return
     */
    private boolean GameLogicUpdate(PairDeque collided) {
        for (int i = 0; i < collided.size(); i++) {
            Pair pair = collided.getitem(i);
            long firstKey = pair.getFirst();
            long secondKey = pair.getSecond();
            GameObject firstObject = gameObjects.get(firstKey);
            GameObject secondObject = gameObjects.get(secondKey);
            if (firstObject.getObjectType() == ObjectType.Player) {
                PlayerObject player = (PlayerObject) firstObject;
                player.enableExtraBoost();
            } else if (secondObject.getObjectType() == ObjectType.Player) {
                PlayerObject player = (PlayerObject) secondObject;
                player.enableExtraBoost();
            }

        }
        return true;
    }



}
