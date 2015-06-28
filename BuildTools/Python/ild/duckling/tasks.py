import os

from ild import building
from ild.dependency import get_depend

##
# @brief File that contains the different tasks that duckling can
# do for the user
#
# @author Jeff Swenson

class Tasks:

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
    def get_dependencies(self, platform):
        get_depend.main(self.project_root, platform)

    ##
    # @brief Build the Ancona based game for the given platform.
    #
    # @param platform Platform that is being built for.
    def build_ancona(self, platform):
        building.generate_ancona_build(self.project_root, platform)
