#!/usr/bin/env python3
##
# @brief Script used to download and build project dependencies
# @author Jeff Swenson
#
# usage: python3 get_depend.py [cmake_dir] [platform]

import os,sys

if __name__ == "__main__":
    #Add ancona python import to the search path
    python_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
    sys.path.append(python_dir)

from ild.building import *


#Repo [url, tag]
SFML_REPO = ["SFML", "http://github.com/LaurentGomila/SFML", "2.2"]


def main(cmake_dir, platform):
    toolchain = get_toolchain(cmake_dir, platform)

    #Clone the SFML Repo
    if not SFML_installed(get_lib_dir(cmake_dir,"SFML"),platform):
        sfml_repo = get_git_repo(cmake_dir, *SFML_REPO,patch=get_patch(cmake_dir,"SFML"))
        build_SFML(sfml_repo,platform,toolchain)
    else:
        print("SFML is already installed for this platform")

def get_build_dir(lib_src, platform):
    return os.path.join(lib_src,"build",platform)

def build_SFML(lib_src,platform,toolchain):
    build_dir = get_build_dir(lib_src,platform)
    build_cmake_project(lib_src,build_dir,toolchain,install=True)

def SFML_installed(lib_src,platform):
    return os.path.isdir(get_build_dir(lib_src,platform))
        

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: {} [cmake_src_dir] [platform]".format(sys.argv[0]))
        sys.exit(1)
    main(os.path.abspath(sys.argv[1]),sys.argv[2])
