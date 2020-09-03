/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni.h"
/* Header for class org_swdc_aria2_impl_NativeImpl */

#ifndef _Included_org_swdc_aria2_impl_NativeImpl
#define _Included_org_swdc_aria2_impl_NativeImpl
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    createSessionImpl
 * Signature: ()I
 */
JNIEXPORT jlong JNICALL Java_org_swdc_aria2_impl_NativeImpl_createSessionImpl
  (JNIEnv *, jclass);

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    closeSession
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_swdc_aria2_impl_NativeImpl_closeSession
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    addUrl
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_aria2_impl_NativeImpl_addUrl
  (JNIEnv *, jclass, jstring, jstring, jstring, jlong);
/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    doDownload
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_doDownload
  (JNIEnv *, jclass, jlong);
/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    pauseDownload
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_pauseDownload
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    unPauseDownload
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_unPauseDownload
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    stopDownload
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_stopDownload
  (JNIEnv *, jclass, jlong, jstring);


/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    getActiveDownloads
 * Signature: (J)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_org_swdc_aria2_impl_NativeImpl_getActiveDownloads
  (JNIEnv *, jclass, jlong);

  /*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    refreshDownload
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_swdc_aria2_impl_NativeImpl_refreshDownload
  (JNIEnv *, jclass,jobject, jstring, jlong);

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *, void *);

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM*, void*);

#ifdef __cplusplus
}
#endif
#endif
