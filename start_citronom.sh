#!/bin/bash

# Script to build and launch the citronom.apk file

# Navigate to the directory where the APK is located
cd /path/to/your/apk/directory

# Build the APK (modify the command based on your build system)
./gradlew build

# Launch the APK (modify the command based on your emulator or device)
adb install -r app/build/outputs/apk/debug/app-debug.apk

# Replace 'app/build/outputs/apk/debug/app-debug.apk' with the correct path to your APK