package com.westerholmgmail.v.lauri.tunnelescape;

import android.support.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

@RunWith(AndroidJUnit4.class)
public class Vector2fInstrumentedTest {
    // notice we are testing C++ components so physics-lib must be loaded
    static
    {
        System.loadLibrary("physics-lib");
    }

    @Test
    public void getXTest() {
        Vector2f vect = new Vector2f(3.f, 20.f);
        assertEquals(3.f, vect.getX(), 0.001f);
        vect = new Vector2f();
        assertEquals(0.f, vect.getX(), 0.001f);
        vect.update(200.f, 20.f);
        Vector2f vect2 = vect;
        assertEquals(200.f, vect2.getX(), 0.001f);
    }

    @Test
    public void getYTest() {
        Vector2f vect = new Vector2f(3.f, 20.f);
        assertEquals(20.f, vect.getY(), 0.001f);
        vect = new Vector2f();
        assertEquals(0.f, vect.getY(), 0.001f);
        vect.update(200.f, 20.f);
        Vector2f vect2 = vect;
        assertEquals(20.f, vect2.getY(), 0.001f);
    }

}