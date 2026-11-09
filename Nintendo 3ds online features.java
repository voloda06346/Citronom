import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Random;

public class Nintendo3dsOnlineFeatures {

    public static void checkAndGenerateNetworkFiles(String baseStoragePath) {
        // Путь к системной папке данных (sysdata) внутри NAND эмулятора
        File sysdataDir = new File(baseStoragePath + "/nand/data/0000000000000000/sysdata/00010011");
        
        if (!sysdataDir.exists()) {
            sysdataDir.mkdirs();
        }

        File friendSeedFile = new File(sysdataDir, "LocalFriendCodeSeed_B");

        // Если файла нет — генерируем заглушку, чтобы Citronom не падал
        if (!friendSeedFile.exists()) {
            byte[] fakeSeed = new byte[32];
            Random random = new Random();
            random.nextBytes(fakeSeed);
            
            // Выставляем валидный стартовый байт для обхода внутренней проверки
            fakeSeed[0] = 0x0B; 

            try (FileOutputStream fos = new FileOutputStream(friendSeedFile)) {
                fos.write(fakeSeed);
                System.out.println("Citronom: Сгенерирован эмулируемый LocalFriendCodeSeed_B");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
