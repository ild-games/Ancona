import os

class BuildInfo:
    def __init__(self, proj_dir, src_dir=None, inc_dest_dir=None, bin_dest_dir=None, toolchain_file=None, target_platform=None, target_architecture=None):
        self.proj_dir = proj_dir
        self.src_dir = src_dir or os.path.join(proj_dir, "depedency", "src")
        self.inc_dest_dir = inc_dest_dir or os.path.join(proj_dir, "depedency", "include")
        self.bin_dest_dir = bin_dest_dir or os.path.join(proj_dir, "depedency", "lib")
        self.toolchain_file = toolchain_file
        self.target_platform = target_platform or "system"
        self.target_architecture = target_architecture or "system"

    def get_dependency_dir(self, dependency_name):
        return os.path.join(self.src_dir, dependency_name)

    def get_lib_dir(self):
        return os.path.join(self.bin_dest_dir, self.target_platform, self.target_architecture)
