package com.westerholmgmail.v.lauri.UI;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

import com.westerholmgmail.v.lauri.tunnelescape.GameEngine;
import com.westerholmgmail.v.lauri.tunnelescape.R;

public class MenuScreen extends AppCompatActivity {

    // load native lib during start up
    static {
        System.loadLibrary("physics-lib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // hide title and make window full-sized
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                             WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(new GameEngine(this));
    }

}
