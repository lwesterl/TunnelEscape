package com.westerholmgmail.v.lauri.tunnelescape;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MenuScreen extends AppCompatActivity {

    /*// Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }*/
    static {
        System.loadLibrary("physics-lib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu_screen);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI());

       Vector2f vect= new Vector2f(100.f, 10.f);
       tv.setText(vect.toString());
       Rectf rect = new Rectf(vect, 100.f, 40.f);
       Vector2f pos = rect.getPosition();
       rect.contains(100.f, 20.f);
       Shape shape = new Shape(299.f, 20.f);
       Vector2f center = shape.getCenter();
       String text = String.valueOf(shape.getMin().getX()) + " hello " + String.valueOf(center.getY());
       tv.setText(text);
       PhysicsProperties physics = new PhysicsProperties(0.4f, 23.f, false);
       /*PhysicsObject obj;
       DynamicObject dyn = new DynamicObject(shape, 19.f);
       PhysicsObject dyn1 = new DynamicObject();*/
    }



}
