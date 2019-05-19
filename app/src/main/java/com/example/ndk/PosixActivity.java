package com.example.ndk;

import android.os.Bundle;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

/**
 * 使用POSIX线程实现生产者消费者
 */
public class PosixActivity extends AppCompatActivity {
    private PosixTest mPosixTest;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_posix);
        mPosixTest = new PosixTest();

        findViewById(R.id.btn_start).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mPosixTest.nativeInit();
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
        if (isFinishing()) {
            mPosixTest.nativeFree();
        }
    }
}
