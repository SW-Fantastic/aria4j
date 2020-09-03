#include "main.h"
#include"aria2.h"
#include<iostream>
#include<cstring>

JavaVM* vm = nullptr;

jstring str2jstring(JNIEnv* env,const char* pat){
    jclass strClass = (env)->FindClass("Ljava/lang/String;");
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = (env)->NewByteArray(std::strlen(pat));
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = (env)->NewStringUTF("UTF8");
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}

int sessionCb(aria2::Session* session, aria2::DownloadEvent event,
            aria2::A2Gid gid, void* userData) {
    JNIEnv* env = nullptr;

    if(vm->AttachCurrentThread((void**)&env,nullptr) != JNI_OK) {
        return 0;
    }

    jclass impl = env->FindClass("org/swdc/aria2/impl/NativeImpl");
    jmethodID onEvnet = env->GetStaticMethodID(impl,"onEvent","(JILjava/lang/String;)V");
    env->CallStaticVoidMethod(impl,onEvnet,reinterpret_cast<std::uintptr_t>(session),event,str2jstring(env,aria2::gidToHex(gid).c_str()));
    return 0;

}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved){
    JNIEnv* env = NULL;
    jint result = -1;

    if (jvm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }
    vm = jvm;
    aria2::libraryInit();
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) {
    aria2::libraryDeinit();
}

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    finalizeNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_finalizeNative
  (JNIEnv * env, jclass clazz){
      return aria2::libraryDeinit();
  }

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    createSessionImpl
 * Signature: ()I
 */
JNIEXPORT jlong JNICALL Java_org_swdc_aria2_impl_NativeImpl_createSessionImpl
  (JNIEnv * env, jclass clazz){
    aria2::Session* session;
    aria2::SessionConfig config;
    config.downloadEventCallback = sessionCb;
    session = aria2::sessionNew(aria2::KeyVals(),config);
    return reinterpret_cast<std::uintptr_t>(session);
  }

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    closeSession
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_swdc_aria2_impl_NativeImpl_closeSession
  (JNIEnv * env, jclass clazz, jlong pointer){
    aria2::sessionFinal(reinterpret_cast<aria2::Session*>(pointer));
  }

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    doDownload
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_doDownload
 (JNIEnv * env, jclass clazz, jlong pointer){
     aria2::Session* session = reinterpret_cast<aria2::Session*>(pointer);
     int result = 0;
     do {
        result = aria2::run(session, aria2::RUN_ONCE);
     } while(result == 1);
     return 0;
 }

 /*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    addUrl
 * Signature: (Ljava/lang/String;Ljava/lang/String;J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_aria2_impl_NativeImpl_addUrl
  (JNIEnv * env, jclass clazz, jstring url, jstring name,jstring dir,jlong pointer){
      aria2::Session* session = reinterpret_cast<aria2::Session*>(pointer);
      const char* cUrl = env->GetStringUTFChars(url,0);
      const char* cName = env->GetStringUTFChars(name,0);
      const char* cDir = env->GetStringUTFChars(dir,0);

      std::vector<std::string> urls;
      urls.push_back(std::string(cUrl));

      aria2::KeyVals options;
      std::pair<std::string,std::string> nameOption("out",std::string(cName));
      std::pair<std::string,std::string> dirOption("dir",std::string(cDir));

      options.push_back(nameOption);
      options.push_back(dirOption);

      env->ReleaseStringUTFChars(name,cName);
      env->ReleaseStringUTFChars(url,cUrl);
      env->ReleaseStringUTFChars(dir,cDir);
      int rv = aria2::addUri(session, nullptr, urls, options);
      if(rv != 0) {
        return false;
      }
      return true;
  }

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    pauseDownload
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_pauseDownload
  (JNIEnv * env, jclass clazz, jlong pointer, jstring a2gid) {
   aria2::Session* session = reinterpret_cast<aria2::Session*>(pointer);
   const char* cA2gid = env->GetStringUTFChars(a2gid,0);
   int result = aria2::pauseDownload(session,aria2::hexToGid(cA2gid));
   env->ReleaseStringUTFChars(a2gid,cA2gid);
   return result;
}

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    unPauseDownload
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_unPauseDownload
  (JNIEnv * env, jclass clazz, jlong pointer, jstring a2gid) {
   aria2::Session* session = reinterpret_cast<aria2::Session*>(pointer);
   const char* cA2gid = env->GetStringUTFChars(a2gid,0);
   int result = aria2::unpauseDownload(session,aria2::hexToGid(cA2gid));
   env->ReleaseStringUTFChars(a2gid,cA2gid);
   return result;
}

/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    stopDownload
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_aria2_impl_NativeImpl_stopDownload
  (JNIEnv * env, jclass clazz, jlong pointer, jstring a2gid) {
   aria2::Session* session = reinterpret_cast<aria2::Session*>(pointer);
   const char* cA2gid = env->GetStringUTFChars(a2gid,0);
   int result = aria2::removeDownload(session,aria2::hexToGid(cA2gid));
   env->ReleaseStringUTFChars(a2gid,cA2gid);
   return result;
}



/*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    getActiveDownloads
 * Signature: (J)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_org_swdc_aria2_impl_NativeImpl_getActiveDownloads
  (JNIEnv * env, jclass clazz, jlong pointer) {

      jclass downloadItem = env->FindClass("org/swdc/aria2/SDownload");
      jmethodID dConstructor = env->GetMethodID(downloadItem,"<init>","(Ljava/lang/String;)V");

      jclass listClazz = env->FindClass("java/util/ArrayList");
      jmethodID dList = env->GetMethodID(listClazz,"<init>","()V");
      jmethodID dListAdd = env->GetMethodID(listClazz,"add","(Ljava/lang/Object;)Z");

      jobject result = env->NewObject(listClazz,dList);

      aria2::Session* session = reinterpret_cast<aria2::Session*>(pointer);
      std::vector<aria2::A2Gid> gids = aria2::getActiveDownload(session);

      for(const aria2::A2Gid& gid: gids) {

        aria2::DownloadHandle* handler = aria2::getDownloadHandle(session,gid);
        if(handler != nullptr) {
            jobject item = env->NewObject(downloadItem,dConstructor,str2jstring(env,aria2::gidToHex(gid).c_str()));
            jmethodID length = env->GetMethodID(downloadItem,"setLength","(J)V");
            env->CallVoidMethod(item,length,handler->getTotalLength());

            jmethodID completeLength = env->GetMethodID(downloadItem,"setCompleteLength","(J)V");
            env->CallVoidMethod(item,completeLength,handler->getCompletedLength());

            jmethodID fileName = env->GetMethodID(downloadItem,"setFileName","(Ljava/lang/String;)V");
            env->CallVoidMethod(item,fileName,str2jstring(env,(handler->getOption("out")).c_str()));

            jmethodID fileLocation = env->GetMethodID(downloadItem,"setFileLocation","(Ljava/lang/String;)V");
            env->CallVoidMethod(item,fileLocation,str2jstring(env,(handler->getOption("dir")).c_str()));

            env->CallBooleanMethod(result,dListAdd,item);
        }

      }
      return result;
  }

  /*
 * Class:     org_swdc_aria2_impl_NativeImpl
 * Method:    refreshDownload
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_swdc_aria2_impl_NativeImpl_refreshDownload
  (JNIEnv * env, jclass clazz,jobject item,jstring a2gid, jlong sessionPointer) {

    aria2::Session* session = reinterpret_cast<aria2::Session*>(sessionPointer);

    const char* cGid = env->GetStringUTFChars(a2gid,0);
    aria2::A2Gid gid = aria2::hexToGid(std::string(cGid));
    std::vector<aria2::A2Gid> gids = aria2::getActiveDownload(session);

    aria2::DownloadHandle* handler = aria2::getDownloadHandle(session,gid);
    if(handler == nullptr) {
        return;
    }

    jclass downloadItem = env->FindClass("org/swdc/aria2/SDownload");

    jmethodID length = env->GetMethodID(downloadItem,"setLength","(J)V");
    env->CallVoidMethod(item,length,handler->getTotalLength());

    jmethodID completeLength = env->GetMethodID(downloadItem,"setCompleteLength","(J)V");
    env->CallVoidMethod(item,completeLength,handler->getCompletedLength());

    jmethodID fileName = env->GetMethodID(downloadItem,"setFileName","(Ljava/lang/String;)V");
    env->CallVoidMethod(item,fileName,str2jstring(env,(handler->getOption("out")).c_str()));

    jmethodID fileLocation = env->GetMethodID(downloadItem,"setFileLocation","(Ljava/lang/String;)V");
    env->CallVoidMethod(item,fileLocation,str2jstring(env,(handler->getOption("dir")).c_str()));

    env->ReleaseStringUTFChars(a2gid,cGid);

  }

