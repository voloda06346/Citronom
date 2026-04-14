public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("citra-android");
    }

    public native void loadROM(String romPath);

    // ... остальной код
}
