##
# @brief Used to generate a template game prototype based off a given name and abbreviation.
#
# @author Tucker Lein

import os, shutil, errno, string, pyratemp

from ild.utils import sscript, stream, ildlib

# git repo where the template game code is stored
TEMPLATE_GIT_REPO = 'git@bitbucket.org:ilikeducks/ancona-template-game.git'

##
# @brief Starts the template process.
#
# @param game_name Name of the game being generated.
# @param game_abbr Abbreviation of the game being generated.
# 
# @returns true if template generation succeeded, otherwise false
def start_template(game_name, game_abbr):
    if game_name == "" or game_abbr == "":
        return False
    
    game_full_name = game_name
    game_name = ''.join(game_name.split(' '))
    try:
        prep_work()
        templatize_project(game_name, game_full_name, game_abbr)
        succeeded = create_prototype_folder(game_name)
    except:
        succeeded = False
    finally:
        clean_up(game_name) 
    return succeeded

##
# @brief Does preperation work for the prototype generation process.
def prep_work():
    if os.path.exists('__applied__'):
        shutil.rmtree('__applied__')
    if os.path.exists('__template__'):
        shutil.rmtree('__template__')
    os.system('git clone ' + TEMPLATE_GIT_REPO + ' __template__')

##
# @brief Creates the prototype's files and replaces template variable instances to prototype info.
#
# @param game_name Name of the game being generated.
# @param game_full_name Name as it was exactly entered by the user (includes spaces).
# @param game_abbr Abbrevation of the game being generated.
def templatize_project(game_name, game_full_name, game_abbr):
    template_files = stream.Stream(sscript.walk_files('__template__')) \
            .filter(lambda file: not includes_dot_files_or_directories(file))
    for old_file in template_files:
        move_file_to_applied(old_file, game_name, game_full_name, game_abbr)

##
# @brief Examines a file and its path and determines if there are any dot directories in its path or if
# itself is a dotfile
#
# @param file File to examine, can include any amount of its path.
#
# @returns True if the file or any of directories in its path begin with '.', otherwise false.
def includes_dot_files_or_directories(file):
    return ildlib.any_map(lambda path_part: path_part.startswith('.'), file.split(os.sep))

##
# @brief Moves the pre-templatized file to the applied folder and applies the template logic.
#
# @param old_file current file being moved to the applied folder
# @param game_name Name of the game being generated.
# @param game_full_name Name as it was exactly entered by the user (includes spaces).
# @param game_abbr Abbreviation of the game being generated.
def move_file_to_applied(old_file, game_name, game_full_name, game_abbr):
    new_file = old_file \
                .replace('$!GAME_ABBR!$', game_abbr) \
                .replace('$!GAME_NAME!$', game_name) \
                .replace('$!GAME_FULL_NAME!$', game_full_name) \
                .replace('__template__', '__applied__')
    if not os.path.exists(os.path.dirname(new_file)):
        os.makedirs(os.path.dirname(new_file))
    shutil.copyfile(old_file, new_file)

    apply_template_to_file(new_file, game_name, game_full_name, game_abbr)

##
# @brief Applies the template replacement logic to a given file.
#
# @param file File to apply the template logic to.
# @param game_name Name of the game being generated.
# @param game_full_name Name as it was exactly entered by the user (includes spaces).
# @param game_abbr Abbreviation of the game being generated.
def apply_template_to_file(file, game_name, game_full_name, game_abbr):
    template = pyratemp.Template(filename=file)
    result = template(GAME_NAME=game_name, GAME_FULL_NAME=game_full_name, GAME_ABBR=game_abbr)
    with open(file, "wt") as out_file:
        out_file.write(result)

##
# @brief Creates the folder the prototype will live in.
#
# @param game_name Name of the game being generated.
#
# @returns True if protoype was successfully made, otherwise false
def create_prototype_folder(game_name):
    project_path = 'Test/Prototype/' + game_name + '/'

    keep_going = True
    if os.path.exists(os.path.join(os.getcwd(), project_path)):
        keep_going = sscript.input_yn('This prototype already exists, do you want to delete it and continue?')
        if keep_going:
            shutil.rmtree(project_path)
    if keep_going:
        shutil.copytree('__applied__', 'Test/Prototype/' + game_name)
    return keep_going

##
# @brief Cleans up temporary folders used by the generation process.
#
# @param game_name Name of the game being generated.
def clean_up(game_name):
    if os.path.exists('__template__'):
        shutil.rmtree('__template__')
    if os.path.exists('__applied__'):
        shutil.rmtree('__applied__')

