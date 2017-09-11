package com.example.android.project_1;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


/**
 *
 * Main Acitvity menu with 2 Buttons
 *
 * Button1 - Switches to Check Phone Number activity
 * Button2 - Opens web browser to url "https://developer.android.com/index.html"
 *
 */
public class MainActivity extends AppCompatActivity {

    public static TextView message;
    private Button btn1, btn2;

    public void init(){
        message = (TextView) findViewById(R.id.TextView);

        btn1 = (Button) findViewById(R.id.button1);
        btn1.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                Intent dialer = new Intent(MainActivity.this, Main2Activity.class);
                startActivity(dialer);
            }
        });

        btn2 = (Button) findViewById(R.id.button2);
        btn2.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                String url = "https://developer.android.com/index.html";
                Intent i = new Intent(Intent.ACTION_VIEW);
                i.setData(Uri.parse(url));
                startActivity(i);
            }
        });
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }

}
