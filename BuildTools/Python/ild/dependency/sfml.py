from ild.dependency.dependency import *

class SFML(Dependency):
    def get_name(self):
        return "SFML"

    def get_git_repo_url(self):
        return "https://github.com/SFML/SFML"
