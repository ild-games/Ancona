from ild.dependency.dependency import *

class JsonCpp(Dependency):
    def get_name(self):
        return "JsonCpp"

    def get_git_repo_url(self):
        return "https://github.com/open-source-parsers/jsoncpp.git"

    def get_lib_dir(self):
        return os.path.join("src", "lib_json")

    def get_cmake_args(self):
        args = super().get_cmake_args()
        args.append(("JSONCPP_WITH_TESTS", "0"))
        return args
