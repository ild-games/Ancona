# README #

Before build you must symbolic link your Resources/ folder to the root directory of the of ancona. 

C++ Version of Ancona Engine

To get started on a Posix OS:

	1. Download cmake and sfml
	2. Open a shell in the project directory
	3. Create a dir named build
	4. Change into build directory
	5. Run the command "cmake .."
	6. Run the command "make"

The binaries will be in the Build/bin folder.

To build on Android:

    1. Download and install android studio.
    2. Install JDK 8, Android Studio, the Android SDK (V22), and Android NDK.
    3. Add ndk to your PATH environment variable.
    4. Add gradle from Android Studio to your path.
    5. Add <path_to_androidsdk>/platformtools to you PATH.
    5. Run the android command to open the SDK manager.  
    6. Using the SDK manager install the android-22 platform and the newest build tools.
    7. Set the ANDROID_NDK environment variables to be the path to the android NDK.
    8. Set the ANDROID_HOME environment variables to be the path to the android SDK.
    9. Run the 'duckling -b android' in the root directory.
    10. Change into the "build/Android/project" and run "gradle debugInstall" to install the app on your phone.
    11. Rund ddms to view log output.

Coming Soon:
Windows VS build instructions.

For any questions related to modifying the build files contact Jeff.
