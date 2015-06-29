import ild.building as building, shutil, os
import ild.utils.sscript as sscript

class Dependency:
    def __init__(self, build_info):
        self.build_info = build_info

    def clone_src(self):
        building.get_git_repo(self.get_src_dir(), self.get_git_repo_url(), self.get_git_tag())

    def build(self):
        src_dir = self.get_src_dir()
        full_build_dir = os.path.join(src_dir, self.get_build_dir())
        building.build_cmake_project(src_dir, full_build_dir, self.build_info.platform.get_cmake_args(self.build_info.target_architecture) + self.get_cmake_args())

    def move_includes(self):
        full_inc_dir = os.path.join(self.get_src_dir(), self.get_include_dir())
        sscript.merge_copy(full_inc_dir, self.build_info.inc_dest_dir)

    def move_binaries(self):
        full_lib_dir = os.path.join(self.get_src_dir(), self.get_build_dir(), self.get_lib_dir())
        sscript.merge_copy(full_lib_dir, self.build_info.get_lib_dir())

    def install(self):
        if not os.path.isdir(self.get_src_dir()):
            self.clone_src()
        if not self.is_installed():
            self.build()
            self.move_includes()
            self.move_binaries()
        else:
            print("{0} is already installed for this platform".format(self.get_name()))

    def get_build_dir(self):
        return os.path.join("build", self.build_info.target_platform, self.build_info.target_architecture)

    def get_include_dir(self):
        return "include"

    def get_lib_dir(self):
        return "lib"

    def get_name(self):
        raise Exception("Child classes must implement get_name")

    def get_git_repo_url(self):
        raise Exception("Child classes must implement get_git_repo_url")

    def get_git_tag(self):
        return None

    def get_src_dir(self):
        return self.build_info.get_dependency_dir(self.get_name())

    def is_installed(self):
        return os.path.isdir(os.path.join(self.get_src_dir(), self.get_build_dir()))

    def get_cmake_args(self):
        return []
