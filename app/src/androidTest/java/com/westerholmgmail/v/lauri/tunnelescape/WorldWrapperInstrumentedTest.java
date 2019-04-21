package com.westerholmgmail.v.lauri.tunnelescape;

import android.support.test.runner.AndroidJUnit4;
import org.junit.Test;
import org.junit.runner.RunWith;
import static org.junit.Assert.*;

@RunWith(AndroidJUnit4.class)

public class WorldWrapperInstrumentedTest {

    // notice we are testing C++ components so physics-lib must be loaded
    static
    {
        System.loadLibrary("physics-lib");
    }

    @Test
    public void setPhysicsWorldUpdateInterval() {
        WorldWrapper.setPhysicsWorldUpdateInterval(0.05f);
    }

    @Test
    public void update() {
        WorldWrapper world = new WorldWrapper();
        long key1 = world.addObject(true, new Vector2f(50.f, 50.f), 10.f, 10.f);
        long key2 = world.addObject(false, new Vector2f(10.f, 0.f), 5.f, 10.f);
        // check initial positions ok
        assertEquals(50.f, world.fetchPosition(key1).getPosition().getX(), 0.001f);
        assertEquals(50.f, world.fetchPosition(key1).getPosition().getY(), 0.001f);
        assertEquals(10.f, world.fetchPosition(key2).getPosition().getX(), 0.001f);
        assertEquals(0.f, world.fetchPosition(key2).getPosition().getY(), 0.001f);
        // update, dynamic object should have new position and static the same position
        PairDeque collided = world.update();
        assertEquals(50.f, world.fetchPosition(key1).getPosition().getX(), 0.001f);
        assertEquals(50.f, world.fetchPosition(key1).getPosition().getY(), 0.001f);
        assertNotEquals(0.f, world.fetchPosition(key2).getPosition().getY(), 0.001f);
        // there should be no collisions during the first update
        System.out.printf("dynamic object position (x,y): %f %f%n", world.fetchPosition(key2).getPosition().getX(), world.fetchPosition(key2).getPosition().getY());
        assertEquals(0, collided.size());
        long key3 = world.addObject(false, new Vector2f(54.f, 50.f), 2.f, 5.f);
        collided = world.update();
        // now there should be a collision between object 1 and 3
        assertEquals(1, collided.size());
        Pair collision_pair = collided.getitem(0);
        // it's not possible to know order of collided objects but there should be keys 1 and 3
        assertEquals(key1 + key3, collision_pair.getFirst() + collision_pair.getSecond());
    }

    @Test
    public void addObject() {
        WorldWrapper world = new WorldWrapper();
        long key1 = world.addObject(true, new Vector2f(50.f, 50.f), 100.f, 100.f);
        long key2 = world.addObject(false, new Vector2f(10.f, 200.f), 50.f, 100.f);
        assertNotEquals(key1, key2);
        assertEquals(50.f, world.fetchPosition(key1).getPosition().getX(), 0.001f);
        assertEquals(50.f, world.fetchPosition(key1).getPosition().getY(), 0.001f);
        assertEquals(10.f, world.fetchPosition(key2).getPosition().getX(), 0.001f);
        assertEquals(200.f, world.fetchPosition(key2).getPosition().getY(), 0.001f);
    }

    @Test
    public void removeObject() {
        WorldWrapper world = new WorldWrapper();
        long key1 = world.addObject(false, new Vector2f(100.f, 0.f), 40.f, 50.f);
        long key2 = world.addObject(true, new Vector2f(500.f, 500.f), 20.f, 50.f);
        world.update(); // no interest for the return value
        assertTrue(world.fetchPosition(key1).getExists() && world.fetchPosition(key2).getExists());
        world.removeObject(key2);
        assertTrue(world.fetchPosition(key1).getExists() && !world.fetchPosition(key2).getExists());
        world.removeObject(key1);
        assertTrue(!world.fetchPosition(key1).getExists() && !world.fetchPosition(key2).getExists());
    }

    @Test
    public void setObjectPhysicsProperties() {
        WorldWrapper world = new WorldWrapper();
        long key = world.addObject(false, new Vector2f(0.f, 0.f), 10.f, 40.f);
        world.setObjectPhysicsProperties(key, 0.5f, 0.5f);
        world.update();
        // currently now way to test this implementation but it's a really basic one
    }

    @Test
    public void setObjectCollisionMask() {
        long mask = 0xff; // no collisions
        WorldWrapper world = new WorldWrapper();
        long key1 = world.addObject(true, new Vector2f(50.f, 50.f), 10.f, 10.f);
        long key2 = world.addObject(false, new Vector2f(54.f, 50.f), 2.f, 5.f);
        // set collisions off from object 2
        world.setObjectCollisionMask(key2, mask);
        // no there should be no collisions, compare to update test
        PairDeque pairs = world.update();
        assertEquals(0, pairs.size());
    }

    @Test
    public void setObjectOriginTransform() {
        WorldWrapper world = new WorldWrapper();
        long key = world.addObject(true, new Vector2f(100.f, 100.f), 10.f, 10.f);
        Vector2f pos = world.fetchPosition(key).getPosition();
        assertEquals(100.f, pos.getX(), 0.001f);
        world.setObjectOriginTransform(key, new Vector2f(100.f, 100.f));
        // @see PhysicsObject.hpp
        assertEquals(0.f, world.fetchPosition(key).getPosition().getX(), 0.001f);
        assertEquals(0.f, world.fetchPosition(key).getPosition().getY(), 0.001f);
    }

    @Test
    public void setObjectForce() {
        WorldWrapper world = new WorldWrapper();
        long key = world.addObject(false, new Vector2f(0.f, 0.f), 10.f, 20.f);
        world.update(); // no need for the return value
        float delta_x = world.fetchPosition(key).getPosition().getX();
        // now only gravity is applied in y-direction so delta_x should be 0
        assertEquals(0.f, delta_x, 0.001f);
        // apply force in x-dimension so that x dimensional position should change
        world.setObjectForce(key, new Vector2f(1000000.f, 0.f));
        world.update();
        assertNotEquals(delta_x, world.fetchPosition(key).getPosition().getX(), 0.1f);
    }

    @Test
    public void setObjectVelocity() {
        // this is relatively same as setObjectForce
        WorldWrapper world = new WorldWrapper();
        long key = world.addObject(false, new Vector2f(0.f, 0.f), 10.f, 20.f);
        world.update(); // no need for the return value
        float delta_x = world.fetchPosition(key).getPosition().getX();
        // now only gravity is applied in y-direction so delta_x should be 0
        assertEquals(0.f, delta_x, 0.001f);
        // apply velocity in x-dimension so that x dimensional position should change
        world.setObjectVelocity(key, new Vector2f(1000.f, 0.f));
        world.update();
        assertNotEquals(delta_x, world.fetchPosition(key).getPosition().getX(), 0.1f);
    }

    @Test
    public void setObjectPosition() {
        WorldWrapper world = new WorldWrapper();
        long key = world.addObject(false, new Vector2f(0.f, 0.f), 20.f, 20.f);
        assertEquals(0.f, world.fetchPosition(key).getPosition().getX(), 0.001f);
        assertEquals(0.f, world.fetchPosition(key).getPosition().getX(), 0.001f);
        world.setObjectPosition(key, new Vector2f(300.f, 150.f));
        assertEquals(300.f, world.fetchPosition(key).getPosition().getX(), 0.001f);
        assertEquals(150.f, world.fetchPosition(key).getPosition().getY(), 0.001f);
        // same should work also for 'static objects'
        long key2 = world.addObject(true, new Vector2f(0.f, 0.f), 20.f, 20.f);
        assertEquals(0.f, world.fetchPosition(key2).getPosition().getX(), 0.001f);
        assertEquals(0.f, world.fetchPosition(key2).getPosition().getX(), 0.001f);
        world.setObjectPosition(key2, new Vector2f(300.f, 150.f));
        assertEquals(300.f, world.fetchPosition(key2).getPosition().getX(), 0.001f);
        assertEquals(150.f, world.fetchPosition(key2).getPosition().getY(), 0.001f);
    }

    @Test
    public void fetchPosition() {
        // this has been already tested in other tests
        WorldWrapper world = new WorldWrapper();
        long key = world.addObject(false, new Vector2f(400.f, 0.f), 20.f, 50.f);
        ObjectStatus status = world.fetchPosition(key);
        assertTrue(status.getExists());
        assertEquals(400.f, status.getPosition().getX(), 0.001f);
        assertEquals(0.f, status.getPosition().getY(), 0.001f);
    }
}