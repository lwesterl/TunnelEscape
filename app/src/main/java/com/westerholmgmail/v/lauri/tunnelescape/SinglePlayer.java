package com.westerholmgmail.v.lauri.tunnelescape;

import android.content.Context;
import android.content.res.ColorStateList;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.os.Handler;
import android.support.annotation.ColorInt;
import android.view.MotionEvent;
import android.view.PixelCopy;
import android.view.SurfaceView;

import com.westerholmgmail.v.lauri.UI.GameScreen;
import com.westerholmgmail.v.lauri.UI.MenuScreen;
import com.westerholmgmail.v.lauri.tunnelescape.objects.GameObject;
import com.westerholmgmail.v.lauri.tunnelescape.objects.ImageObject;
import com.westerholmgmail.v.lauri.tunnelescape.objects.ObjectType;
import com.westerholmgmail.v.lauri.tunnelescape.objects.PlayerObject;
import com.westerholmgmail.v.lauri.tunnelescape.objects.StaticObject;
import com.westerholmgmail.v.lauri.tunnelescape.objects.TreasureObject;
import com.westerholmgmail.v.lauri.tunnelescape.resources.FileType;
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
    public static boolean PlayerWon = false; /**< tells whether player won or lost */
    public static int Score = 0; /**< Single player score */
    public static boolean HardDifficulty = false;
    public static @FileType.FileTypeRef int CurrentLevel = FileType.Intro;
    private static Vector2f playerPosition = new Vector2f(0.f, 0.f);
    private final static int maxDiffX = 2 * (int) ResourceManager.getImageWidth(ImageType.Player); // used to detect when canvas should be transformed
    private final static int maxDiffY = UIBarHeight + 2 * (int) ResourceManager.getImageHeight(ImageType.Player); // used to detect when canvas should be transformed
    private final static float PlayerCircleRadius = 100.f;

    private WorldWrapper worldWrapper;
    private Context context;
    private HashMap<Long, GameObject> gameObjects = new HashMap<>();
    private ArrayList<GameObject> imageObjects = new ArrayList<>(); // these don't have PhysicsObject counterpart
    private @ColorInt int backgroundColor = Color.argb(255, 20, 20, 20);
    private int canvasMultiplierX = 0;
    private int canvasMultiplierY = 0;
    private float[] maxPoint = {Float.MIN_VALUE, Float.MIN_VALUE}; // this must have format x, y
    private float[] minPoint = {Float.MAX_VALUE, Float.MAX_VALUE}; // this must have format x, y
    private long startTime = 0; // this should be in seconds
    private int prevTimeScore = 0;
    private ArrayList<Long> gameObjectsToBeRemoved = new ArrayList<>();
    private boolean gameRunning;
    private int renderCycles = 0;

    /**
     * @brief Constructor
     */
    public SinglePlayer(Context context) {
        this.context = context;
        worldWrapper = new WorldWrapper();
        loadLevel(FileType.getFilePath(SinglePlayer.CurrentLevel));
        gameRunning = true;
    }

    /**
     * @brief Update objects and game status based on PhysicsWorld
     */
    @Override
    public void update() {
        if (gameRunning) {
            // update PhysicsWorld via WorldWrapper
            PairDeque collided = worldWrapper.update();
            if (! GameLogicUpdate(collided)) {
                // exit single player
                stopSinglePlayer();
                return;
            }
            // remove collided objects
            for (Long i : gameObjectsToBeRemoved) {
                worldWrapper.removeObject(i);
                gameObjects.remove(i);
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
            CalculateScore();
        }

    }

    /**
     * @brief Draw single player TunnelEscape
     * @param canvas drawing surface
     */
    @Override
    public void render(Canvas canvas) {
        Canvas surfaceCanvas = null;
        Bitmap surfaceBitmap = null;
        renderCycles ++;
        if (renderCycles % 10 == 0) {
            surfaceBitmap = Bitmap.createBitmap(MenuScreen.ScreenWidth, MenuScreen.ScreenHeight, Bitmap.Config.ARGB_8888);
            surfaceCanvas = new Canvas(surfaceBitmap);
            transferCanvas(surfaceCanvas);
            renderCycles = 0;
        }
        transferCanvas(canvas);
        canvas.drawColor(backgroundColor);
        for (GameObject imageObject : imageObjects) {
            imageObject.draw(canvas);
            if (surfaceCanvas != null) imageObject.draw(surfaceCanvas);
        }
        for (HashMap.Entry<Long, GameObject> item : gameObjects.entrySet()) {
            item.getValue().draw(canvas);
            if (surfaceCanvas != null) item.getValue().draw(surfaceCanvas);
        }
        if (SinglePlayer.HardDifficulty) {
            // create only circle as visible area
            Bitmap tmpBitmap = Bitmap.createBitmap(MenuScreen.ScreenWidth, MenuScreen.ScreenHeight, Bitmap.Config.ARGB_8888); // this creates a mutable bitmap
            Canvas tmpCanvas = new Canvas(tmpBitmap);
            // counterTransform must match values in transferCanvas
            float xCounterTransform = canvasMultiplierX * (MenuScreen.ScreenWidth - SinglePlayer.maxDiffX);
            float yCounterTransform = canvasMultiplierY * (MenuScreen.ScreenHeight - SinglePlayer.maxDiffY);
            tmpCanvas.drawColor(Color.BLACK);
            Paint p = new Paint();
            p.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.CLEAR));
            tmpCanvas.drawCircle(playerPosition.getX() - xCounterTransform + ResourceManager.getImageWidth(ImageType.Player) * 0.5f,
                    playerPosition.getY() - yCounterTransform + ResourceManager.getImageHeight(ImageType.Player) * 0.5f, SinglePlayer.PlayerCircleRadius, p);
            canvas.drawBitmap(tmpBitmap, xCounterTransform, yCounterTransform, null);
        }
        if (surfaceBitmap != null) {
            Bitmap scaled = Bitmap.createScaledBitmap(surfaceBitmap, 200, 100, false);
            ProcessCanvasBitmap(scaled);
        }

    }

    protected void ProcessCanvasBitmap(Bitmap bitmap) {

    }

    @Override
    public void reset() {
        PlayerObject.lefPressed = false;
        PlayerObject.rightPressed = false;
        PlayerObject.boostPressed = false;
        // create new WorldWrapper
       if (worldWrapper != null) {
            worldWrapper.delete();
        }
        worldWrapper = new WorldWrapper();
        gameObjects.clear();
        imageObjects.clear();
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
            case ObjectType.End:
                id = worldWrapper.addObject(true, new Vector2f(x_center, y_center),
                        ResourceManager.getImageWidth(imageType), ResourceManager.getImageHeight(imageType));
                gameObject = new StaticObject(imageType, objectType, id);
                break;
            case ObjectType.Texture:
                gameObject = new ImageObject(imageType, x, y); // this has no PhysicsObject in PhysicsWorld
                break;
            case ObjectType.Enemy:
                break;
            case ObjectType.Treasure:
                id = worldWrapper.addObject(true, new Vector2f(x_center, y_center),
                        ResourceManager.getImageWidth(imageType), ResourceManager.getImageHeight(imageType));
                worldWrapper.setObjectPhysicsProperties(id, TreasureObject.Elasticity, TreasureObject.Density);
                gameObject = new TreasureObject(id);
                break;
            default:
                // gameObject remains null if this scope is entered
                System.out.println("Cannot add object");
        }
        // add gameObject to gameObjects
        if (gameObject != null && objectType != ObjectType.Texture) {
            gameObjects.put(id, gameObject);
        } else if (gameObject != null) imageObjects.add(gameObject);
    }

    /**
     * @brief Load level
     * @param levelName specifies level to load
     * @return true if successful, otherwise false
     */
    public boolean loadLevel(String levelName) {
        // set correct gravity values
        PhysicsProperties.setGravityY(20000.f);
        SinglePlayer.PlayerWon = false;
        SinglePlayer.Score = 0;
        InitMinMaxPoints();
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
                CreateTreasures();
                startTime = System.currentTimeMillis()/1000;
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
            UpdateMinMaxPoints(x, y);
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
            try {
                if (firstObject.getObjectType() == ObjectType.Player) {
                    if (! PlayerLogicUpdate((PlayerObject) firstObject, secondObject)) return false;
                } else if (secondObject.getObjectType() == ObjectType.Player) {
                    if (! PlayerLogicUpdate((PlayerObject) secondObject, firstObject)) return false;
                }
            } catch (NullPointerException e) {
                e.printStackTrace();
                return false;
            }
        }
        return true;
    }


    /**
     * @brief Update PlayerObject and whole game based on collision
     * @param player PlayerObject
     * @param otherObject Other GameObject PlayerObject collided with
     * @return true if game still on, false if game should be stopped
     */
    private boolean PlayerLogicUpdate(PlayerObject player, GameObject otherObject) {
        if (otherObject.getObjectType() == ObjectType.End) {
            SinglePlayer.PlayerWon = true;
            return false;
        } else if (otherObject.getObjectType() == ObjectType.Treasure) {
            SinglePlayer.Score += 10;
            gameObjectsToBeRemoved.add(new Long(otherObject.getObjectId()));
            player.boost();
        }
        player.enableExtraBoost();
        if (player.damagePlayer(otherObject.getObjectType())) return false;
        UpdateHPBar(player.getPlayerHP());
        return true;
    }

    /**
     * @brief Update HPBar progress based on Player HP
     * @param HP Player HP
     */
    private void UpdateHPBar(int HP) {
        MenuScreen menuScreen = (MenuScreen) context;
        if (HP < 0) HP = 0;
        else if (HP > 100) HP = 100;
        final int HP_value = HP;
        menuScreen.HPBar.post(() -> {
            menuScreen.HPBar.setProgress(HP_value);
            if (HP_value > 75) menuScreen.HPBar.setProgressTintList(ColorStateList.valueOf(Color.GREEN));
            else if (HP_value > 40) menuScreen.HPBar.setProgressTintList(ColorStateList.valueOf(Color.YELLOW));
            else menuScreen.HPBar.setProgressTintList(ColorStateList.valueOf(Color.RED));
        });
    }

    private void stopSinglePlayer() {
        gameRunning = false;
        if (! SinglePlayer.PlayerWon) {
            SinglePlayer.Score = 0;
            // update possible AIPlayer reward
            AIPlayer.reward = AIPlayer.LevelFailedReward;
            ProcessCanvasBitmap(null);
        }
        else {
            CalculateScore();
            // update possible AIPlayer reward
            AIPlayer.reward = AIPlayer.LevelCompletedReward;
            ProcessCanvasBitmap(null);
        }
        //SinglePlayer.PlayerWon = true;
        // Get a handler that can be used to post to the main thread
        android.os.Handler mainHandler = new android.os.Handler(context.getMainLooper());

        Runnable myRunnable = () -> {
            MenuScreen menuScreen = (MenuScreen) context;
            menuScreen.singlePlayerOver(true);
        };
        mainHandler.post(myRunnable);
    }


    /**
     * @brief Update minPoint and maxPoint
     * @param x item x coordinate in level
     * @param y item y coordinate in level
     */
    private void UpdateMinMaxPoints(float x, float y) {
        if (x < minPoint[0]) minPoint[0] = x;
        else if (x > maxPoint[0]) maxPoint[0] = x;
        if (y < minPoint[1]) minPoint[1] = y;
        else if (y > maxPoint[1]) maxPoint[1] = y;
    }

    /**
     * @brief Init MinPoints and MaxPoints
     */
    private void InitMinMaxPoints() {
        maxPoint[0] = Float.MIN_VALUE;
        maxPoint[1] = Float.MIN_VALUE;
        minPoint[0] = Float.MAX_VALUE;
        minPoint[1] = Float.MAX_VALUE;
    }

    /**
     * @brief Wrapper call for creating treasures to the level
     */
    private void CreateTreasures() {
        // the constant values are just result of trial and error
        int treasureAmount = (int) ((maxPoint[0] - minPoint[0]) * 0.000005 * (maxPoint[1] - minPoint[1]));
        for (int i = 0; i < treasureAmount; i++) {
            addObject(ObjectType.Treasure, TreasureObject.getCurrentImageType(),
                    TreasureObject.getRandomX(minPoint[0] + 100.f, maxPoint[0] - 100.f), TreasureObject.getRandomY(minPoint[1] + 100.f, maxPoint[1] - 100.f));
        }
    }

    /**
     * @brief Calculate time based score when level is successfully completed
     */
    private void CalculateScore() {
        // timeElapsed in seconds
        Score -= prevTimeScore;
        double timeElapsed = (double) (System.currentTimeMillis()/1000 - startTime);
        int timeBonus = (int) (100.d * (600.d / (600.d + timeElapsed)));
        Score += timeBonus;
        prevTimeScore = timeBonus;
        MenuScreen menuScreen = (MenuScreen) context;
        menuScreen.CurrentScoreView.post(()-> {
            menuScreen.CurrentScoreView.setText(String.valueOf(SinglePlayer.Score));
        });

    }

}
