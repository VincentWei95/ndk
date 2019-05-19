#include "/include/com_example_ndk_JNITest.h"
#include <jni.h>
#include <stdio.h>
#include <syslog.h>
#include <pthread.h>
#include <unistd.h>

#define PRODUCE "1"
#define CONSUME "0"
#define SLEEP_TIMEOUT 10000

pthread_t producer_thread;
pthread_t consumer_thread;
pthread_mutex_t mutex;
pthread_cond_t cond;
jstring value = PRODUCE;

void * produce(void *data) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // 当前value已生产，等待
        if (value == PRODUCE) {
            pthread_cond_wait(&cond, &mutex);
        } else {
            syslog(LOG_INFO, "posix produce product");
            value = PRODUCE;
            pthread_cond_signal(&cond);
        }

        pthread_mutex_unlock(&mutex);
        usleep(SLEEP_TIMEOUT);
    }
}

void* consume(void *data) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // 当前value已消费，等待
        if (value == CONSUME) {
            pthread_cond_wait(&cond, &mutex);
        } else {
            syslog(LOG_INFO, "posix consume product");
            value = CONSUME;
            pthread_cond_signal(&cond);
        }

        pthread_mutex_unlock(&mutex);
        usleep(SLEEP_TIMEOUT);
    }
}

/*
 * Class:     com_example_ndk_PosixTest
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_PosixTest_nativeInit
        (JNIEnv *env, jobject object) {
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_init(&cond, NULL);

    pthread_create(&producer_thread, NULL, produce, NULL);

    pthread_create(&consumer_thread, NULL, consume, NULL);
}

/*
 * Class:     com_example_ndk_PosixTest
 * Method:    nativeFree
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ndk_PosixTest_nativeFree
        (JNIEnv *env, jobject object) {
    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&cond);
}
