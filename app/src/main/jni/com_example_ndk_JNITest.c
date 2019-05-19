#include "/include/com_example_ndk_JNITest.h"
#include <jni.h>
#include <stdio.h>
#include <syslog.h>

/*
 * Class:     com_example_ndk_JNITest
 * Method:    getStringFromJNI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_ndk_JNITest_getStringFromJNI
        (JNIEnv *env, jobject object) {
    return (*env)->NewStringUTF(env, "hello from jni!");
}

/*
 * Class:     com_example_ndk_JNITest
 * Method:    javaStringToCString
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_JNITest_javaStringToCString
        (JNIEnv *env, jobject object, jstring javaString) {
    jboolean isCopy;
    const char *str = (*env)->GetStringUTFChars(env, javaString, &isCopy);
    if (str != 0) {
        syslog(LOG_INFO, "java string:%s", str);
        if (isCopy == JNI_TRUE) {
            syslog(LOG_INFO, "C string is a copy of the java string"); // 返回该结果
        } else {
            syslog(LOG_INFO, "C string points to actual string");
        }

        (*env)->ReleaseStringUTFChars(env, javaString, str);
    }
}

/*
 * Class:     com_example_ndk_JNITest
 * Method:    javaArrayCopyToCArray
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_JNITest_javaArrayCopyToCArray
        (JNIEnv *env, jobject object, jintArray javaArray) {
    // 获取数组长度
    jint arrayLength = (*env)->GetArrayLength(env, javaArray);
    syslog(LOG_INFO, "java array length is %d", arrayLength);
    
    // 将java数组复制给native数组
    jint nativeArray[arrayLength];
    (*env)->GetIntArrayRegion(env, javaArray, 0, arrayLength, nativeArray);

    for (jint i = 0; i < arrayLength; i++) {
        syslog(LOG_INFO, "after copy show native element %d", nativeArray[i]); // 打印复制后的数组元素
    }
}


/*
 * Class:     com_example_ndk_JNITest
 * Method:    cArrayCopyToJavaArray
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_com_example_ndk_JNITest_cArrayCopyToJavaArray
        (JNIEnv *env, jobject object) {
    // 创建一个返回给java的数组
    jintArray javaArray = (*env)->NewIntArray(env, 10);
    jint elements[10];
    for (jint i = 0; i < 10; i++) {
        elements[i] = i * 2;
    }

    // 将元素数组设置给java数组返回
    (*env)->SetIntArrayRegion(env, javaArray, 0, 10, elements);
    return javaArray;
}

/*
 * Class:     com_example_ndk_JNITest
 * Method:    javaField
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_JNITest_javaField
        (JNIEnv *env, jobject object) {
    // 获取java class
    jclass clazz = (*env)->GetObjectClass(env, object);

    // 获取class中实例域的id
    jfieldID instanceFieldId = (*env)->GetFieldID(env, clazz, "mInstanceField", "Ljava/lang/String;");
    // 获取class中实例域成员变量
    jstring instanceField = (*env)->GetObjectField(env, object, instanceFieldId);
    // 上面的是java字符串，要转换为native的字符串才可以使用，否则会闪退
    const char *instanceFieldStr = (*env)->GetStringUTFChars(env, instanceField, NULL);
    syslog(LOG_INFO, "java instance field value %s", instanceFieldStr);
    (*env)->ReleaseStringUTFChars(env, instanceField, instanceFieldStr);

    // 获取class中静态域的id
    jfieldID staticFieldId = (*env)->GetStaticFieldID(env, clazz, "sStaticField", "Ljava/lang/String;");
    // 获取class中静态域成员变量
    jstring staticField = (*env)->GetStaticObjectField(env, clazz, staticFieldId);
    const char *staticFieldStr = (*env)->GetStringUTFChars(env, staticField, NULL);
    syslog(LOG_INFO, "java static field value %s", staticFieldStr);
    (*env)->ReleaseStringUTFChars(env, staticField, staticFieldStr);
}

/*
 * Class:     com_example_ndk_JNITest
 * Method:    callMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_JNITest_callMethod
        (JNIEnv *env, jobject object) {
    // 获取java class
    jclass clazz = (*env)->GetObjectClass(env, object);

    // 获取class中实例方法的id
    jmethodID instanceMethodId = (*env)->GetMethodID(env, clazz, "instanceMethod", "()Ljava/lang/String;");
    // 调用java中实例方法
    jstring instanceMethodResult = (*env)->CallObjectMethod(env, object, instanceMethodId);
    const char *instanceMethodResultStr = (*env)->GetStringUTFChars(env, instanceMethodResult, NULL);
    syslog(LOG_INFO, "java instance method return value %s", instanceMethodResultStr);
    (*env)->ReleaseStringUTFChars(env, instanceMethodResult, instanceMethodResultStr);
    
    // 获取class中静态方法的id
    jmethodID staticMethodId = (*env)->GetStaticMethodID(env, clazz, "staticMethod", "()Ljava/lang/String;");
    // 调用java中静态方法
    jstring staticMethodResult = (*env)->CallStaticObjectMethod(env, clazz, staticMethodId);
    const char *staticMethodResultStr = (*env)->GetStringUTFChars(env, staticMethodResult, NULL);
    syslog(LOG_INFO, "java static method return value %s", staticMethodResultStr);
    (*env)->ReleaseStringUTFChars(env, staticMethodResult, staticMethodResultStr);
}


/*
 * Class:     com_example_ndk_JNITest
 * Method:    accessExceptionMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_JNITest_accessExceptionMethod
        (JNIEnv *env, jobject object) {
    // 获取java class
    jclass clazz = (*env)->GetObjectClass(env, object);
    // 获取class中的方法id
    jmethodID methodId = (*env)->GetMethodID(env, clazz, "throwingExceptionMethod", "()V");
    // 调用java中的方法
    (*env)->CallVoidMethod(env, object, methodId);
    // 检查调用的方法是否发生异常
    jthrowable exception = (*env)->ExceptionOccurred(env);
    if (exception != 0) {
        // 函数发生异常，检查完后清除异常
        syslog(LOG_ERR, "native catch exception");
        (*env)->ExceptionClear(env);
    }
}


/*
 * Class:     com_example_ndk_JNITest
 * Method:    throwExceptionMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_JNITest_throwExceptionMethod
        (JNIEnv *env, jobject object) {
    jclass exceptionClazz = (*env)->FindClass(env, "java/lang/NullPointerException");
    if (exceptionClazz != 0) {
        (*env)->ThrowNew(env, exceptionClazz, "native throw null pointer exception!");
    }
}

