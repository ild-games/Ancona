from ild.dependency.noop_dependency import *
from ild.platform.android import *

from os import path
import shutil

class CppStl(NoopDependency):
    def get_name(self):
        return "CppStl"

    def move_binaries(self):
        if isinstance(self.build_info.platform, Android):
            self.move_android_stl()

    def move_android_stl(self):
        stl_lib_dir_path = self.get_android_stl_dir()
        platform_stl_path = path.join(stl_lib_dir_path,"libs",self.build_info.target_architecture)
        stl_lib = path.join(platform_stl_path,"libgnustl_shared.so")
        shutil.copy(stl_lib,self.build_info.get_lib_dir())

    def get_android_stl_dir(self):
        ndk_path = self.build_info.platform.get_ndk_path()
        return path.join(ndk_path,"sources","cxx-stl","gnu-libstdc++","4.9")
