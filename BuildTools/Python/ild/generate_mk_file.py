#!/usr/bin/env python3
##
# @brief Script used to generate a Android.mk file for
#        a target
# @author Jeff Swenson
#
# usage: python3 generate_mk.py [target] [cmake_dir] [build_dir]
#               -s [source files ...]
#               -d [dynamic libs ...] 
#               -l [static libs ...]
#               -i [include directories ...]
import os,sys,argparse

if __name__ == "__main__":
    #Add ancona python import to the search path
    python_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
    sys.path.append(python_dir)

from ild import building
import pyratemp

##
# @brief Generate an Android.mk file for the target.
#
# @param target_name Name of the target being built.
# @param source_files List of source files to add compile.
# @param cmake_dir Root of the cmake directory.
# @param build_dir Root of the build directory.
# @param dynamic_libs List of dynamic libraries that should be linked against the the target.
# @param static_libs List of static libraries that should be linked against the target.
# @param include_dirs List of include directories that the project depends on.
#
# @return The filepath to the generated Android.mk file.
def generate_mk(target_name, cmake_dir, build_dir, source_files, dynamic_libs, static_libs, include_dirs):
    #Find the destination directory and create it if needed
    destination_dir = building.get_android_build_dir(build_dir,target_name)
    os.makedirs(os.path.join(destination_dir, "jni"),exist_ok=True)
    destination_file_name = os.path.join(destination_dir,"jni","Android.mk")

    #Find and generate the Android.mk template
    template_file = os.path.join(cmake_dir,"BuildTools","Templates", "Android.mk")
    template = pyratemp.Template(filename=template_file)
    result = template(
                build_dir=build_dir,
                source_files=source_files,
                dynamic_libraries=dynamic_libs,
                static_libraries=static_libs,
                target=target_name,
                include_paths=include_dirs
            )
    
    #Write the Android.mk file to disk
    with open(destination_file_name, "w") as android_mk_file:
        android_mk_file.write(result)

    return destination_file_name

if __name__ == "__main__":
    def file_name(file_path):
        return os.path.split(file_path)[-1]
    parser = argparse.ArgumentParser(description="Generate an Android.mk file for an Ancona target.")

    parser.add_argument('target',metavar="[target]", type=str, help="Name of the ancona target") 
    parser.add_argument('cmake_dir',metavar="[cmake_dir]", type=str, help="Root of the source directory") 
    parser.add_argument('build_dir',metavar="[build_dir]", type=str, help="Root of the build directory") 

    parser.add_argument('-s', nargs='+',dest="source_files",
            metavar="main.cpp", type=file_name, help="Source files to build")
    parser.add_argument('-d', nargs='*',dest="dynamic_libs",
            metavar="Dynamic_Lib", type=str, help="Libs that should be linked dynamically")
    parser.add_argument('-l', nargs='*',dest="static_libs",
            metavar="Ancona_Util", type=str, help="Libs that should be linked statically")
    parser.add_argument('-i', nargs='*',dest="include_paths",
            metavar="path/to/include", type=os.path.realpath, help="Header paths to be included")

    args = vars(parser.parse_args())

    generate_mk(
            args['target'],
            args['cmake_dir'],
            args['build_dir'],
            args['source_files'],
            args['dynamic_libs'],
            args['static_libs'],
            args['include_paths']
            )
