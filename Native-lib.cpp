#include <jni.h>
#include "citra/core.h" // Заголовочные файлы Citra

extern "C" JNIEXPORT void JNICALLTYPE
Java_org_citra_3ds_MainActivity_loadROM(
        JNIEnv* env, jobject thiz, jstring romPath) {
    const char* path = env->GetStringUTFChars(romPath, nullptr);
    // Вызов функции Citra для загрузки ROM
    Citra::LoadROM(path);
    env->ReleaseStringUTFChars(romPath, path);
}
