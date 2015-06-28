import os

class Platform:
    def __init__(self, cmake_dir):
        self.cmake_dir = cmake_dir

    def get_name(self):
        raise Exception("Child classes must implement get_name")

    def get_toolchain_file(self):
        raise Exception("Child classes must implement get_toolchain_file")

    def get_supported_architectures(self):
        raise Exception("Child classes must implement get_supported_architectures")

    def get_default_architecture(self):
        raise Exception("Child classes must implement get_default_architecture")

    def get_cmake_args(self, target_architecture):
        args = []
        if self.get_toolchain_file():
            args.append(("CMAKE_TOOLCHAIN_FILE", self.build_toolchain_file_arg()))
        return args

    def build_toolchain_file_arg(self):
        return os.path.join(self.cmake_dir,"BuildTools","Toolchain",self.get_toolchain_file())
