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
       tv.setText(String.valueOf(vect.getX()));
       Rectf rect = new Rectf(vect, 100.f, 40.f);
       rect.contains(100.f, 20.f);
       Shape shape = new Shape(299.f, 20.f);
       Vector2f size = shape.getCenter();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    //public native String stringFromJNI();



}
