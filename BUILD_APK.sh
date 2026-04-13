#!/bin/bash
# Citronom APK Build Script
# This script builds and launches the Citronom 3DS Emulator APK
echo "Building Citronom APK..."

# Build the APK using Gradle
./gradlew assembleRelease

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "APK location: app/build/outputs/apk/release/citronom.apk"
    
    # Optionally install to connected device
    read -p "Install APK to device? (y/n) " -n 1 -r
echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        adb install -r app/build/outputs/apk/release/citronom.apk
        echo "APK installed successfully!"
    fi
else
    echo "Build failed!"
    exit 1
fi
