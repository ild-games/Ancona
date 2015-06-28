import os, shutil

##
# @brief Get an iterator that recursively walks over all of the files in
# the path.
#
# @param path Path that is the root of the walk.
# @param followlinks True if symbolic links should be followed
#
# @return Iterator over just the files
def walk_files(path,followlinks=False):
    for directory,child_directories,files in os.walk(path, followlinks=followlinks):
        for file_name in files:
            yield os.path.join(directory,file_name)

##
# @brief Prompts the user for yes or no
# 
# @param question Text to display to the user
# @param default Default answer, defaults to 'yes'
#
# @return True if user says yes, false if user says no
def input_yn(question, default="yes"):
    valid = {"yes": True, "y": True, "ye": True,
             "no": False, "n": False}
    if default is None:
        prompt = " [y/n] "
    elif default == "yes":
        prompt = " [Y/n] "
    elif default == "no":
        prompt = " [y/N] "
    else:
        raise ValueError("invalid default answer: '%s'" % default)

    while True:
        print(question + prompt, end=" ")
        choice = input().lower()
        if default is not None and choice == '':
            return valid[default]
        elif choice in valid:
            return valid[choice]
        else:
            print("Please respond with 'yes' or 'no' (or 'y' or 'n').\n")

def merge_copy(src_dir, dest_dir):
    for directory,child_directories,files in os.walk(src_dir):
        sub_dest_dir = os.path.join(dest_dir, os.path.relpath(directory, src_dir))

        os.makedirs(sub_dest_dir, exist_ok=True)
        for file_name in files:
            shutil.copy(os.path.join(directory, file_name), os.path.join(sub_dest_dir, file_name))
