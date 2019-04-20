package com.westerholmgmail.v.lauri.tunnelescape;

import android.support.test.runner.AndroidJUnit4;
import org.junit.Test;
import org.junit.runner.RunWith;
import static org.junit.Assert.*;

@RunWith(AndroidJUnit4.class)

public class ShapeInstrumentedTest {

    // testing C++ implementations import on Java so physics-lib must be loaded
    static {
        System.loadLibrary("physics-lib");
    }

    @Test
    public void getCenter() {
        Shape shape = new Shape();
        assertEquals(0.f, shape.getCenter().getX(), 0.001f);
        shape = new Shape(100.f, 50.f);
        assertEquals(0.f, shape.getCenter().getY(), 0.001f);
    }

    @Test
    public void getFrame() {
        Shape shape = new Shape(100.f, 100.f);
        Vector2fDeque frame = shape.getFrame();
        // the first Vector2f in frame should be the left upper corner of the shape
        // notice that Vector2 compare operators haven't been converted to Java (C++ code implements those as overloads)
        Vector2f cmp_vect = new Vector2f(-50.f, -50.f);
        Vector2f frame_item = frame.getitem(0);
        assertEquals(cmp_vect.getX(), frame_item.getX(), 0.001f);
        assertEquals(cmp_vect.getY(), frame_item.getY(), 0.001f);
    }

    @Test
    public void getMin() {
        Shape shape = new Shape(10.f, 100.f);
        assertEquals(-5.f, shape.getMin().getX(), 0.001f);
        assertEquals(-50.f, shape.getMin().getY(), 0.001f);
    }

    @Test
    public void getMax() {
        Shape shape = new Shape(10.f, 100.f);
        assertEquals(5.f, shape.getMax().getX(), 0.001f);
        assertEquals(50.f, shape.getMax().getY(), 0.001f);
    }

    @Test
    public void getArea() {
        float width = 10.f;
        float height = 20.f;
        Shape shape = new Shape(width, height);
        assertEquals(width * height, shape.getArea(), 0.001f);
    }

    @Test
    public void getWidth() {
        float width = 20.f;
        float height = 15.f;
        Shape shape = new Shape(width, height);
        assertEquals(width, shape.getWidth(), 0.001f);
    }

    @Test
    public void getHeight() {
        float width = 20.f;
        float height = 15.f;
        Shape shape = new Shape(width, height);
        assertEquals(height, shape.getHeight(), 0.001f);
    }
}