package com.example.ndk;

public class JNITest {
    // 实例域
    private String mInstanceField = "instanceField";

    // 静态域
    private static String sStaticField = "staticField";

    // 实例方法
    private String instanceMethod() {
        return "instance method";
    }

    // 静态方法
    private static String staticMethod() {
        return "static method";
    }

    // 抛出异常方法
    private void throwingExceptionMethod() {
        throw new NullPointerException("native access throw null pointer exception!");
    }

    static {
        System.loadLibrary("ndk");
    }

    public native String getStringFromJNI();

    public native void javaStringToCString(String javaString);

    public native void javaArrayCopyToCArray(int[] javaArray);

    public native int[] cArrayCopyToJavaArray();

    public native void javaField();

    public native void callMethod();

    public native void accessExceptionMethod();

    public native void throwExceptionMethod();
}
