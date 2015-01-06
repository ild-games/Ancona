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

To build on Android:

    1. Download the android NDK
    2. Add ndk/tools to your PATH environment variable
    3. Set the NDK and ANDROID_NDK environment variables to be the path to the android NDK
    4. Clone SFML from github
    5. Set the ANDROID_CMAKE_TOOLCHAIN environment variable to the toolchain file located in SFML/cmake/toolchains
    6. Open a terminal and navigate to the SFML/tools/android environment
    7. Run the make_all.sh script
    8. Open a terminal in the ancona root
    9. Run the ancona script in the root with "Android" as the argument
    10. Change into the "build" directory and run make

The binaries will be in the Build/bin folder.

Coming Soon:
Windows VS build instructions.

For any questions related to modifying the build files contact Jeff.
