package com.westerholmgmail.v.lauri.tunnelescape;

import android.graphics.Canvas;
import android.graphics.Color;
import android.support.annotation.ColorInt;
import android.view.MotionEvent;

import com.westerholmgmail.v.lauri.UI.GameScreen;
import com.westerholmgmail.v.lauri.UI.MenuScreen;
import com.westerholmgmail.v.lauri.tunnelescape.objects.GameObject;
import com.westerholmgmail.v.lauri.tunnelescape.objects.ObjectType;
import com.westerholmgmail.v.lauri.tunnelescape.objects.PlayerObject;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ResourceManager;
import com.westerholmgmail.v.lauri.tunnelescape.resources.ImageType;

import java.util.ArrayList;

/**
 * @class SinglePlayer
 * @brief Class which implements main framework for single player game mode
 */
public class
SinglePlayer implements GameScreen {

    static private Vector2f playerPosition = new Vector2f(0.f, 0.f);
    private final static int maxDiffX = 2 * (int) ResourceManager.getImageWidth(ImageType.PlayerImage); // used to detect when canvas should be transformed
    private final static int maxDiffY = 2 * (int) ResourceManager.getImageHeight(ImageType.PlayerImage); // used to detect when canvas should be transformed

    private WorldWrapper worldWrapper;
    private ArrayList<GameObject> gameObjects = new ArrayList<>();
    private @ColorInt int backgroundColor = Color.BLACK;
    private int canvasMultiplierX = 0;
    private int canvasMultiplierY = 0;


    /**
     * @brief Constructor
     */
    public SinglePlayer() {

        worldWrapper = new WorldWrapper();
        loadLevel(); // TODO implement properly
    }

    @Override
    public void update() {
        // update PhysicsWorld via WorldWrapper
        PairDeque collided = worldWrapper.update();
        // TODO check collided
        // update GameObject positions
        for (GameObject gameObject : gameObjects) {
            Vector2f position = worldWrapper.fetchPosition(gameObject.getObjectId()).getPosition();
            gameObject.updatePosition(position);
            // move also matching PhysicsObject
            Vector2f force = gameObject.move();
            if (force.getX() != 0.f || force.getY() != 0.f) {
                worldWrapper.setObjectForce(gameObject.getObjectId(), force);
            }
        }


    }

    @Override
    public void render(Canvas canvas) {
        transferCanvas(canvas);
        canvas.drawColor(backgroundColor);
        for (GameObject gameObject : gameObjects) {
            gameObject.draw(canvas);
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
        long id;
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
                break;
            case ObjectType.Ground:
                break;
            case ObjectType.Hazard:
                break;
            case ObjectType.Enemy:
                break;
            default:
                // gameObject remains null if this scope is entered
                System.out.println("Cannot add object");
        }
        // add gameObject to gameObjects
        if (gameObject != null) {
            gameObjects.add(gameObject);
        }
    }

    public void loadLevel() {
        // set correct gravity values
        PhysicsProperties.setGravityY(20000.f);
        addObject(ObjectType.Player, ImageType.PlayerImage, 200.f, 0.f);
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



}
