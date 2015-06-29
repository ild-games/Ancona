import os
import ild.platform.platform


class BuildInfo:
    EXTLIB_DIR = "extlibs"

    def __init__(self, platform, proj_dir, architecture=None, src_dir=None, inc_dest_dir=None, bin_dest_dir=None):
        self.platform = platform
        self.proj_dir = proj_dir
        self.src_dir = src_dir or os.path.join(proj_dir, self.EXTLIB_DIR, "src")
        self.inc_dest_dir = inc_dest_dir or os.path.join(proj_dir, self.EXTLIB_DIR, "include")
        self.bin_dest_dir = bin_dest_dir or os.path.join(proj_dir, self.EXTLIB_DIR, "lib")
        self.target_platform = platform.get_name()
        self.target_architecture = architecture or platform.get_default_architecture()

    def get_dependency_dir(self, dependency_name):
        return os.path.join(self.src_dir, dependency_name)

    def get_lib_dir(self):
        return os.path.join(self.bin_dest_dir, self.target_platform, self.target_architecture)
