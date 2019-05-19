package com.example.ndk;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ndk");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_jni).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                start(new Intent(MainActivity.this, JniActivity.class));
            }
        });
        findViewById(R.id.btn_posix).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                start(new Intent(MainActivity.this, PosixActivity.class));
            }
        });
    }

    private void start(Intent intent) {
        if (isActivityExist(intent)) startActivity(intent);
    }

    private boolean isActivityExist(Intent intent) {
        return getPackageManager().resolveActivity(intent, 0) != null;
    }
}
