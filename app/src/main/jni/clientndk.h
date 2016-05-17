//
// Created by Apple on 16/5/16.
//

#ifndef MYAPPLICATION_CLIENTNDK_H
#define MYAPPLICATION_CLIENTNDK_H
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT jstring JNICALL native_printf(JNIEnv *env, jclass clazz,jstring value);

JNIEXPORT jobjectArray JNICALL getTwoArray
        (JNIEnv * env, jobject object, jint dimion);




#ifdef __cplusplus
}
#endif


#endif //MYAPPLICATION_CLIENTNDK_H
