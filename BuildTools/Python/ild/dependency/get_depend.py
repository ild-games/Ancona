#!/usr/bin/env python3
##
# @brief Script used to download and build project dependencies
# @author Jeff Swenson
# @author Tucker Lein
#
# usage: python3 get_depend.py [cmake_dir] [platform_name]

import os,sys

if __name__ == "__main__":
    #Add ancona python import to the search path
    python_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
    sys.path.append(python_dir)

from ild.building import *
from ild.dependency.jsoncpp import *
from ild.dependency.sfml import *
from ild.dependency.build_info import *
from ild.dependency.cppstl import *
from ild.platform.platform import *
from ild.platform.system import *
from ild.platform.android import *

DEPENDENCIES = [ JsonCpp, SFML, CppStl ]


##
# @brief Runs the get_dependency script
# 
# @param cmake_dir CMake directory
# @param platform Target platform to install on
def main(cmake_dir, platform):
    build_info = BuildInfo(platform, cmake_dir)
    install_dependencies(DEPENDENCIES, build_info)

##
# @brief Clean all of the dependency build folders generated for the platform.
#
# @param cmake_dir Root directory of the project.
# @param platform Platform that the build files should be cleaned for.
def clean_dependencies(cmake_dir, platform):
    for arch in platform.get_supported_architectures():
        build_info = BuildInfo(platform, cmake_dir, arch)
        for depend in DEPENDENCIES:
            depend(build_info).clean()
            

##
# @brief installs all the dependencies specified in DEPENDENCIES
# 
# @param dependencies The dependencies to install
# @param build_info BuildInfo instance for the dependencies
def install_dependencies(dependencies, build_info): 
    for dependency in DEPENDENCIES:
        dependency(build_info).install()
    
##
# @brief Gets the build directory for a given library source path
# 
# @param lib_src library source path for dependency
# @param platform Target platform to install on
def get_build_dir(lib_src, platform):
    return os.path.join(lib_src,"build",platform)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: {} [cmake_src_dir] [platform_name]".format(sys.argv[0]))
        sys.exit(1)
    main(os.path.abspath(sys.argv[1]),sys.argv[2])