package com.westerholmgmail.v.lauri.tunnelescape;

import android.support.test.runner.AndroidJUnit4;
import org.junit.Test;
import org.junit.runner.RunWith;
import static org.junit.Assert.*;

@RunWith(AndroidJUnit4.class)
public class RectfInstumentedTest {

    // testing C++ components so physics-lib must be loaded
    static {
        System.loadLibrary("physics-lib");
    }

    @Test
    public void getPosition() {
        Rectf rect = new Rectf();
        assertEquals(0.f, rect.getPosition().getX(), 0.001f);
        rect.setPosition(new Vector2f(20.f, 50.f));
        assertEquals(50.f, rect.getPosition().getY(), 0.001f);
    }

    @Test
    public void getWidth() {
        Rectf rect = new Rectf(new Vector2f(4.f, 5.f), 100.f, 20.f);
        assertEquals(100.f, rect.getWidth(), 0.001f);
        rect.setWidth(50.f);
        assertEquals(50.f, rect.getWidth(), 0.001f);
    }

    @Test
    public void getHeight() {
        Rectf rect = new Rectf(new Vector2f(4.f, 5.f), 100.f, 20.f);
        assertEquals(20.f, rect.getHeight(), 0.001f);
        rect.setHeight(50.f);
        assertEquals(50.f, rect.getHeight(), 0.001f);
    }

    @Test
    public void getSize() {
        Rectf rect = new Rectf();
        assertEquals(0.f, rect.getSize().getX(), 0.001f);
        rect.setSize(new Vector2f(100.f, 1000.f));
        assertEquals(100.f, rect.getSize().getX(), 0.001f);
        assertEquals(1000.f, rect.getSize().getY(), 0.001f);
    }

    @Test
    public void contains() {
        Rectf rect = new Rectf(new Vector2f(100.f,100.f), 20.f, 5.f);
        assertTrue(rect.contains(new Vector2f(110.f, 102.f)));
    }

    @Test
    public void contains1() {
        Rectf rect = new Rectf(new Vector2f(10.f, 10.f), 100.f, 100.f);
        assertTrue(rect.contains(50.f, 40.f));
    }
}