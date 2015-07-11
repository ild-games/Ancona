from ild.dependency.dependency import *
from ild.utils import sscript

class SFML(Dependency):
    def get_name(self):
        return "SFML"

    def get_git_repo_url(self):
        return "https://github.com/SFML/SFML"

    def move_binaries(self):
        super().move_binaries()

        if self.build_info.platform.get_name() == "android":
            ext_path = os.path.join(self.get_src_dir(),"extlibs","libs-android",self.build_info.target_architecture)

        if ext_path:
            sscript.merge_copy(ext_path,self.build_info.get_lib_dir()) 
