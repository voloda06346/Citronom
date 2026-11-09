#include <jni.h>
#include <vector>
#include <random>
#include <cstdint>

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_voloda06346_citronom_ApkEmulatorCore_generateNativeFriendSeed(JNIEnv *env, jobject thiz) {
    // Размер файла LocalFriendCodeSeed_B всегда равен 32 байтам
    const size_t SEED_SIZE = 32;
    std::vector<uint8_t> seed_buffer(SEED_SIZE, 0);

    // Используем генератор случайных чисел для уникальности Console ID
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0x00, 0xFF);

    // 1. Инициализируем первые 8 байт (Console ID)
    for (int i = 0; i < 8; ++i) {
        seed_buffer[i] = dis(gen);
    }
    
    // Выставляем правильный заголовок типа консоли (Retail 3DS)
    seed_buffer[0] = 0x0B; 

    // 2. Заполняем блок подписи (следующие 16 байт) тестовым паттерном
    // Фанатские сервера вроде Pretendo принимают чистые эмулированные дампы
    for (int i = 8; i < 24; ++i) {
        seed_buffer[i] = dis(gen);
    }

    // 3. Последние 8 байт — хэш-заглушка
    for (int i = 24; i < SEED_SIZE; ++i) {
        seed_buffer[i] = dis(gen);
    }

    // Переносим массив в Java
    jbyteArray result = env->NewByteArray(SEED_SIZE);
    env->SetByteArrayRegion(result, 0, SEED_SIZE, reinterpret_cast<jbyte*>(seed_buffer.data()));

    return result;
}
