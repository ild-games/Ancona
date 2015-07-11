import os

from ild import building
from ild.dependency import get_depend
from ild.platform.platform import *
from ild.platform.system import *
from ild.platform.android import *

##
# @brief File that contains the different tasks that duckling can
# do for the user
#
# @author Jeff Swenson

class Tasks:
    PLATFORMS = { "desktop": System, "android": Android }

    def __init__(self, project_root):
        self.project_root = project_root

    ##
    # @brief Generate doxygen documentation for the project.
    def generate_documentation(self):
        building.generate_documentation(os.path.join(self.project_root,"Doc",".doxyrc"))

    ##
    # @brief Clean up the build directory
    def clean_build_directory(self):
        building.command("rm -rf build/*",directory=self.project_root)

    ##
    # @brief Download and build dependencies for a specified platform
    def get_dependencies(self, platform_name):
        platform = self.PLATFORMS[platform_name](self.project_root)
        get_depend.main(self.project_root, platform)

    ##
    # @brief Build the Ancona based game for the given platform.
    #
    # @param platform Platform that is being built for.
    def build_ancona(self, platform_name, target_architecture=None):
        platform = self.PLATFORMS[platform_name](self.project_root)
        if not target_architecture:
            target_architecture = platform.get_default_architecture()
        building.generate_ancona_build(self.project_root, platform, target_architecture)

    ##
    # @brief Clean the ancona build folder and dependency build folders.
    def clean(self):
        self.clean_build_directory()
        for platform in self.PLATFORMS.values():
            get_depend.clean_dependencies(self.project_root, platform(self.project_root))

