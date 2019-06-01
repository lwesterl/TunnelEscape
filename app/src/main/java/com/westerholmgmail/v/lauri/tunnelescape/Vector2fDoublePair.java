package com.westerholmgmail.v.lauri.tunnelescape;

/**
 * Just simple pair class for Vector2f and double because Java lacks proper template pair class
 */
public class Vector2fDoublePair {

    public Vector2fDoublePair(Vector2f vector2f, double value) {
        first = vector2f;
        second = value;
    }

    public Vector2f first;
    public double second;

}
