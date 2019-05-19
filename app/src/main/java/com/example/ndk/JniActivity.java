package com.example.ndk;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

public class JniActivity extends AppCompatActivity {
    private JNITest mJniTest;
    private TextView mTvNdk;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni);
        mJniTest = new JNITest();
        mTvNdk = findViewById(R.id.tv_ndk);

        getStringFromJNI();
        javaStringToCString();
        javaArrayCopyToCArray();
        cArrayCopyToJavaArray();
        javaField();
        callMethod();
        accessExceptionMethod();
        throwExceptionMethod();
    }

    private void getStringFromJNI() {
        mTvNdk.append("getStringFromJNI() = " + mJniTest.getStringFromJNI());
        mTvNdk.append("\n");
    }

    private void javaStringToCString() {
        mJniTest.javaStringToCString("this is a java string");
    }

    private void javaArrayCopyToCArray() {
        mTvNdk.append("javaArrayCopyToCArray()");
        mTvNdk.append("\n");
        int[] array = new int[10];
        for (int i = 0; i < 10; i++) {
            array[i] = i * 2;
        }
        mJniTest.javaArrayCopyToCArray(array);
    }

    private void cArrayCopyToJavaArray() {
        int[] javaArray = mJniTest.cArrayCopyToJavaArray();
        if (javaArray != null) {
            mTvNdk.append("cArrayCopyToJavaArray()");
            mTvNdk.append("\n");
            for (int i = 0; i < javaArray.length; i++) {
                mTvNdk.append("element[" + i + "] = " + javaArray[i]);
                mTvNdk.append("\n");
            }
        }
    }

    private void javaField() {
        mJniTest.javaField();
    }

    private void callMethod() {
        mJniTest.callMethod();
    }

    private void accessExceptionMethod() {
        mJniTest.accessExceptionMethod();
    }

    private void throwExceptionMethod() {
        try {
            mJniTest.throwExceptionMethod();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
