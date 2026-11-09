package com.voloda06346.citronom;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Nintendo3dsOnlineFeatures {

    public static void initializeFriendSeed(String externalFilesDir) {
        // Конструируем официальный путь NAND памяти 3DS для системных данных
        String sysdataPath = externalFilesDir + "/nand/data/0000000000000000/sysdata/00010011";
        File directory = new File(sysdataPath);

        // Создаем папки, если их еще нет в эмуляторе
        if (!directory.exists()) {
            directory.mkdirs();
        }

        File seedFile = new File(directory, "LocalFriendCodeSeed_B");

        // Если файла нет — дёргаем нативное ядро и создаем правильный сид с нуля
        if (!seedFile.exists()) {
            try {
                ApkEmulatorCore core = new ApkEmulatorCore();
                byte[] generatedSeed = core.generateNativeFriendSeed();

                try (FileOutputStream fos = new FileOutputStream(seedFile)) {
                    fos.write(generatedSeed);
                    System.out.println("Citronom Network: Успешно сгенерирован новый LocalFriendCodeSeed_B");
                }
            } catch (IOException e) {
                System.err.println("Citronom Network: Ошибка записи сида друга: " + e.getMessage());
            } catch (UnsatisfiedLinkError e) {
                System.err.println("Citronom Network: Нативная библиотека ядра не загружена: " + e.getMessage());
            }
        }
    }
}
