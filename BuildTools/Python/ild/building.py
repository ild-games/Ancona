import os,sys

TOOL_CHAINS = {"android": "android.toolchain.cmake"}

def get_toolchain(cmake_dir, platform):
    platform = platform.lower()
    if platform in TOOL_CHAINS:
        return os.path.join(cmake_dir,"BuildTools","Toolchain",TOOL_CHAINS[platform])
    return ""

def generate_ancona_build(cmake_dir, platform):
    build_cmake_project(
            cmake_dir,
            os.path.join(cmake_dir,"build"),
            get_toolchain(cmake_dir,platform)
            )

##
# @brief Create an object for RAII style directory changes
class DirContext:
    def __init__(self, new_working_dir):
        self.old_dir = os.getcwd()
        self.new_dir = new_working_dir
    def __enter__(self):
        print("Entering",self.new_dir)
        os.chdir(self.new_dir)
        return self
    def __exit__(self,type,value,traceback):
        print("Exiting", self.old_dir)
        os.chdir(self.old_dir)

##
# @brief Execute a system command
#
# @param cmd command to execute
# @param directory directory the command should be executed in
#
# @return 
def command(cmd,directory=None):
    exit_code = 0
    if directory:
        with DirContext(directory):
            exit_code = os.system(cmd)
    else:
        exit_code = os.system(cmd)

##
# @brief Get the directory libraries are downloaded to
#
# @param cmake_dir CMaker root directory
# @param depend_name Name of the dependency (EX SFML)
#
# @return 
def get_lib_dir(cmake_dir, depend_name):
    return os.path.join(cmake_dir,'lib',depend_name)


##
# @brief Find the path to the executable
#
# @param program Name of the command to find
#
# @return Path to the command if it exists.  None if the command is not found.
def which(program):
    def is_exe(fpath):
        return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            path = path.strip('"')
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                return exe_file

    return None

##
# @brief Apply patch to the git repo
#
# @param repo_dir Directory to the repository
# @param patch_file Absolute path to a patch file
def apply_git_patch(repo_dir,patch_file):
    command("git apply {}".format(patch_file), repo_dir)

##
# @brief Produce the patch name for the path
#
# @param cmake_dir Root of the cmake directory
# @param patch_name Name of the patch to find
#
# @return Absolute path to the patch file
def get_patch(cmake_dir,patch_name):
    return os.path.join(cmake_dir,"BuildTools","Patch",patch_name + ".patch")

##
# @brief Clone a git repo into the libs folder
#
# @param dest_dir Destination of the git repo
# @param giturl URL of the repo to clone
# @param tag Tag of the repo to clone
# @param patch Absolute path to a patch file that should be applied
#
# @return Absolute path to the cloned repository
def get_git_repo(dest_dir, giturl,tag=None,patch=None):
    #Only clone the repo if it does not exist already
    if not os.path.isdir(dest_dir):
        #Create the directory the repository will be cloned to
        os.makedirs(dest_dir,exist_ok=True)
        print("Cloning repo into {}!".format(dest_dir))
        with DirContext(dest_dir):
            print("Cloning in directory",os.getcwd())
            #Clone the repo into the directory
            command("git clone {} .".format(giturl)) 
            if tag:
                #Checkout the correct tag
                command("git checkout tags/{}".format(tag))
            if patch:
                apply_git_patch(dest_dir,patch)
    return dest_dir

##
# @brief Check if all of the tools needed by the Android NDK are installed.
#
# @return True if everything is found, otherwise false. 
def is_android_ndk_installed():
    if "ANDROID_NDK" not in os.environ:
        print("Error: You must set ANDROID_NDK to be the location of the android NDK")
        return False
    if not which("ant"):
        print("Error: You must install 'ant'")
        return False
    if not which("ndk-build"): 
        print("Error: You must add $ANDROID_NDK to the PATH variable")
        return False
    if not which("android"):
        print("Error: You must install the android sdk and add <SDK_Path>/tools to your \
                path variable")
    if not which("javac"):
        print("Error: You must install JDK7")
    return True

##
# @brief Used to build a CMake project
#
# @param src_dir Root of the cmake directory for the project
# @param build_dir Directory that the project should be built in
# @param toolchain_file (OPTIONAL) Toolchain file that will be used to build the project
# @param install (OPTIONAL) If true make install will be run after the build
def build_cmake_project(src_dir, build_dir, toolchain_file,install=False):
    os.makedirs(build_dir,exist_ok=True)
    with DirContext(build_dir):
        if toolchain_file:
            #TODO: Make this command less hacky
            cmake_cmd = "cmake -DCMAKE_TOOLCHAIN_FILE={} -DANDROID_ABI=armeabi -DANDROID_STL=gnustl_static -DANDROID_NATIVE_API_LEVEL=android-9 {}".format(toolchain_file,src_dir)
        else:
            cmake_cmd = "cmake {}".format(src_dir)
        command(cmake_cmd)
        command("make -j5")

##
# @brief Generate doxygen documentation
#
# @param config_file Path to the doxygen configuration file
def generate_documentation(config_file):
    os.system("doxygen {}".format(config_file))


##
# @brief Get the absolute path to a the Android build directory for the target
#
# @param build_dir Directory the build is in
# @param target_name The name of the target being built
#
# @return Absolute path to the android build directory
def get_android_build_dir(build_dir, target_name):
    return os.path.join(build_dir, "Android", target_name)
