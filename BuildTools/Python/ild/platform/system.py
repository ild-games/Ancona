from ild.platform.platform import *

class System(Platform):
    def get_name(self):
        return "system"

    def get_toolchain_file(self):
        return None

    def get_supported_architectures(self):
        return [ "system" ]

    def get_default_architecture(self):
        return "system"
