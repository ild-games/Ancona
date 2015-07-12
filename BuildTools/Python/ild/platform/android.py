from ild.platform.platform import *
from os import environ

class Android(Platform):
    def get_name(self):
        return "android"

    def get_toolchain_file(self):
        return "android.toolchain.cmake"

    def get_supported_architectures(self):
        return [ "armeabi" ]

    def get_default_architecture(self):
        return "armeabi"

    def get_cmake_args(self, target_architecture):
        args = super().get_cmake_args(target_architecture)
        args.append(("BuildTests", "0"))
        args.append(("ANDROID_ABI", target_architecture))
        args.append(("ANDROID_STL", "gnustl_shared"))
        args.append(("ANDROID_NATIVE_API_LEVEL", "android-14"))
        return args

    def get_ndk_path(self):
        return environ["ANDROID_NDK"]

