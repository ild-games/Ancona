#!/usr/bin/env python3
##
# @brief Script used to download and build project dependencies
# @author Jeff Swenson
# @author Tucker Lein
#
# usage: python3 get_depend.py [cmake_dir] [platform]

import os,sys

if __name__ == "__main__":
    #Add ancona python import to the search path
    python_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
    sys.path.append(python_dir)

from ild.building import *


# Dependency format:
# { 
#     "name": name,
#     "repo": [url, tag (optional)]
# }
DEPENDENCIES = [ \
    { \
        "name": "SFML", \
        "repo": ["git@bitbucket.org:JeffSwenson/sfml.git", "2.2"] \
    }, \
    { \
        "name": "JsonCpp", \
        "repo": ["https://github.com/open-source-parsers/jsoncpp.git"] \
    } \
]


##
# @brief Runs the get_dependency script
# 
# @param cmake_dir CMake directory
# @param platform Target platform to install on
def main(cmake_dir, platform):
    install_dependencies(DEPENDENCIES, cmake_dir, platform)

##
# @brief installs all the dependencies specified in DEPENDENCIES
# 
# @param dependencies The dependencies to install
# Dependency format:
# { 
#     "name": name,
#     "repo": [url, tag (optional)]
# }
# @param cmake_dir CMake directory
# @param platform Target platform to install on
def install_dependencies(dependencies, cmake_dir, platform):
    for dependency in DEPENDENCIES:
        install_dependency(dependency, cmake_dir, platform)
    
##
# @brief Install a specific dependency
# 
# @param dependency_info The dependency to install
# Dependency format:
# { 
#     "name": name,
#     "repo": [url, tag (optional)]
# }
# @param cmake_dir CMake directory
# @param platform Target platform to install on
def install_dependency(dependency_info, cmake_dir, platform):
    if not dependency_installed(get_lib_dir(cmake_dir,dependency_info["name"]),platform):
        git_repo = get_git_repo(cmake_dir, dependency_info["name"], *dependency_info["repo"])
        build_dependency(git_repo, cmake_dir, platform)
    else:
        print("{0} is already installed for this platform".format(dependency_info["name"]))

##
# @brief Checks if a given dependency is already installed
# 
# @param lib_src library source path for dependency
# @param platform Target platform to install on
def dependency_installed(lib_src,platform):
    return os.path.isdir(get_build_dir(lib_src,platform))

##
# @brief Gets the build directory for a given library source path
# 
# @param lib_src library source path for dependency
# @param platform Target platform to install on
def get_build_dir(lib_src, platform):
    return os.path.join(lib_src,"build",platform)

##
# @brief Builds the dependency
#
# @param lib_src library source path for dependency
# @param cmake_dir CMake directory
# @param platform Target platform to install on
def build_dependency(lib_src, cmake_dir, platform):
    build_dir = get_build_dir(lib_src,platform)
    toolchain = get_toolchain(cmake_dir, platform)
    build_cmake_project(lib_src,build_dir,toolchain,install=True)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: {} [cmake_src_dir] [platform]".format(sys.argv[0]))
        sys.exit(1)
    main(os.path.abspath(sys.argv[1]),sys.argv[2])
