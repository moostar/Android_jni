//
// Created by Apple on 16/5/16.
//

#include "clientndk.h"
#include <android/log.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>
#include <assert.h>


#ifdef __cplusplus
extern "C" {
#endif
#define JNIREG_CLASS "cn/dpocket/youja/ClientNDK"


#define  LOG_TAG    "log"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

char* jstringTostring(JNIEnv* env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);

        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }

    return rtn;
}
JNIEXPORT jstring JNICALL native_printf(JNIEnv *env, jclass clazz,jstring value) {
    char *tmp = jstringTostring(env,value);
    const char *str = "ldskfjlsakjdfsdjf";
    __android_log_print(ANDROID_LOG_ERROR, "tag", "call <native_printf> in java");

    LOGD("%s" ,tmp);
    return NULL;
}

//通过构造一个数组的数组， 返回 一个二维数组的形式
JNIEXPORT jobjectArray JNICALL getTwoArray (JNIEnv * env, jobject object, jint dimion)
{

    jclass intArrayClass = env->FindClass("[I"); //获得一维数组 的类引用，即jintArray类型
    //构造一个指向jintArray类一维数组的对象数组，该对象数组初始大小为dimion
    jobjectArray obejctIntArray  =  env->NewObjectArray(dimion ,intArrayClass , NULL);

    //构建dimion个一维数组，并且将其引用赋值给obejctIntArray对象数组
    for( int i = 0 ; i< dimion  ; i++ )
    {
        //构建jint型一维数组
        jintArray intArray = env->NewIntArray(dimion);

        jint temp[10]  ;  //初始化一个容器，假设 dimion  < 10 ;
        for( int j = 0 ; j < dimion ; j++)
        {
            temp[j] = i + j  ; //赋值
        }

        //设置jit型一维数组的值
        env->SetIntArrayRegion(intArray, 0 , dimion ,temp);
        //给object对象数组赋值，即保持对jint一维数组的引用
        env->SetObjectArrayElement(obejctIntArray , i ,intArray);

        env->DeleteLocalRef(intArray);  //删除局部引用
    }

    return   obejctIntArray; //返回该对象数组
}


//Native层回调Java类方法
JNIEXPORT void JNICALL doCallBack
        (JNIEnv * env , jobject obj)
{
    //回调Java中的方法

    jclass cls = env->GetObjectClass(obj);//获得Java类实例
    jmethodID callbackID = env->GetMethodID(cls , "callback" , "(Ljava/lang/String;)V") ;//或得该回调方法句柄

    if(callbackID == NULL)
    {
//        cout << "getMethodId is failed \n" << endl ;
        LOGD("getMethodID is fialed");
    }

    jstring native_desc = env->NewStringUTF(" I am Native");

    env->CallVoidMethod(obj , callbackID , native_desc); //回调该方法，并且传递参数值
}

/*
 * Class:     com_feixun_jni_HelloJni
 * Method:    printStuInfoAtNative
 * Signature: (Lcom/feixun/jni/Student;)V
 */
//在Native层输出Student的信息
JNIEXPORT void JNICALL printStuInfoAtNative
        (JNIEnv * env, jobject obj,  jobject obj_stu) //第二个类实例引用代表Student类，即我们传递下来的对象
{

    jclass stu_cls = env->GetObjectClass(obj_stu); //或得Student类引用

    if(stu_cls == NULL)
    {
//        cout << "GetObjectClass failed \n" ;
        LOGD("GetObjectClass is fialed");
    }
    //下面这些函数操作，我们都见过的。O(∩_∩)O~
    jfieldID ageFieldID = env->GetFieldID(stu_cls,"age","I"); //获得得Student类的属性id
    jfieldID nameFieldID = env->GetFieldID(stu_cls,"name","Ljava/lang/String;"); // 获得属性ID

    jint age = env->GetIntField(obj_stu , ageFieldID);  //获得属性值
    jstring name = (jstring)env->GetObjectField(obj_stu , nameFieldID);//获得属性值

    const char * c_name = env->GetStringUTFChars(name ,NULL);//转换成 char *

//    string str_name = c_name ;
    env->ReleaseStringUTFChars(name,c_name); //释放引用

//    cout << " at Native age is :" << age << " # name is " << str_name << endl ;
}


/*
 * Class:     com_feixun_jni_HelloJni
 * Method:    native_getListStudents
 * Signature: ()Ljava/util/ArrayList;
 */ //获得集合类型的数组
JNIEXPORT jobject JNICALL getListStudents
        (JNIEnv * env, jobject obj)
{
    jclass list_cls = env->FindClass("java/util/ArrayList");//获得ArrayList类引用



    if(list_cls == NULL)
    {
//        cout << "listcls is null \n" ;
    }
    jmethodID list_costruct = env->GetMethodID(list_cls , "<init>","()V"); //获得得构造函数Id

    jobject list_obj = env->NewObject(list_cls , list_costruct); //创建一个Arraylist集合对象
    //或得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
    jmethodID list_add  = env->GetMethodID(list_cls,"add","(Ljava/lang/Object;)Z");

    jclass stu_cls = env->FindClass("cn/dpocket/youja/Student");//获得Student类引用
    //获得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
    jmethodID stu_costruct = env->GetMethodID(stu_cls , "<init>", "(ILjava/lang/String;)V");//"(Lcn/dpocket/youja/ClientNDK;)V");

    for(int i = 0 ; i < 3 ; i++)
    {
        jstring str = env->NewStringUTF("CC");
        //通过调用该对象的构造函数来new 一个 Student实例
        jobject stu_obj = env->NewObject(stu_cls , stu_costruct , 10,str);  //构造一个对象

        env->CallBooleanMethod(list_obj , list_add , stu_obj); //执行Arraylist类实例的add方法，添加一个stu对象
    }

    return list_obj ;
}

static JNINativeMethod gMethods[] = {
        {"native_printf", "(Ljava/lang/String;)Ljava/lang/String;", (void *)native_printf},
        {"native_getListStudents","()Ljava/util/ArrayList;",(void*)getListStudents},
        {"printStuInfoAtNative","(Lcn/dpocket/youja/Student;)V",(void*)printStuInfoAtNative},
        {"getTwoArray","(I)[[I",(void*)getTwoArray},
        {"doCallBack","()V",(void*)doCallBack},

};

static int registerNativeMethods(JNIEnv *env, const char *className,
                                 JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass( className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static int registerNatives(JNIEnv *env) {
    if (!registerNativeMethods(env, JNIREG_CLASS, gMethods,
                               sizeof(gMethods) / sizeof(gMethods[0])))
        return JNI_FALSE;

    return JNI_TRUE;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;

    if (vm->GetEnv( (void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "tag", "load library error 1");
        return JNI_ERR;
    }
    assert(env != NULL);

    if (!registerNatives(env)) {
        __android_log_print(ANDROID_LOG_ERROR, "tag", "load library error 2");
        return JNI_ERR;
    }
    result = JNI_VERSION_1_4;
    __android_log_print(ANDROID_LOG_ERROR, "tag", "load library success: %d", result);
    return result;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    __android_log_print(ANDROID_LOG_ERROR, "tag", "library was unload");
}
#ifdef __cplusplus
}
#endif