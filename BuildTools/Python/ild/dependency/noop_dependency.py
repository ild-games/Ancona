from ild.dependency.dependency import Dependency

class NoopDependency(Dependency):
    def is_installed(self):
        return False

    def clone_src(self):
        None

    def build(self):
        None

    def move_includes(self):
        None

    def move_binaries(self):
        None

    def clean(self):
        None
