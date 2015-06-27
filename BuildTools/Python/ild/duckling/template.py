import os, shutil, errno, string, pyratemp

from ild.utils import sscript, stream, ildlib

TEMPLATE_GIT_REPO = 'git@bitbucket.org:ilikeducks/ancona-template-game.git'

def start_template(game_name, game_abbr):
    game_name = ''.join(game_name.split(' '))
    prep_work()
    templatize_project(game_name, game_abbr)
    tear_down(game_name) 

def prep_work():
    if os.path.exists('__applied__'):
        shutil.rmtree('__applied__')
    if os.path.exists('__template__'):
        shutil.rmtree('__template__')
    os.system('git clone ' + TEMPLATE_GIT_REPO + ' __template__')

def templatize_project(game_name, game_abbr):
    template_files = stream.Stream(sscript.walk_files('__template__')) \
            .filter(lambda file: not includes_dot_files_or_directories(file))
    for old_path in template_files:
        move_file_to_applied(old_path, game_name, game_abbr)

def includes_dot_files_or_directories(file_path):
    return ildlib.any_map(lambda path_part: path_part.startswith('.'), file_path.split(os.sep))

def move_file_to_applied(old_file, game_name, game_abbr):
    new_file = old_file \
                .replace('$!GAME_ABBR!$', game_abbr) \
                .replace('$!GAME_NAME!$', game_name) \
                .replace('__template__', '__applied__')
    if not os.path.exists(os.path.dirname(new_file)):
        os.makedirs(os.path.dirname(new_file))
    shutil.copyfile(old_file, new_file)

    apply_template_to_file(new_file, game_name, game_abbr)

def apply_template_to_file(file, game_name, game_abbr):
    template = pyratemp.Template(filename=file)
    result = template(GAME_NAME=game_name, GAME_ABBR=game_abbr)
    with open(file, "wt") as out_file:
        out_file.write(result)

def append_prototype_to_cmake(folderName):
    line_to_add = 'add_subdirectory(' + folderName + ')'
    cmake_file = 'Test/Prototype/CMakeLists.txt'
    if line_to_add not in open(cmake_file).read():
        with open(cmake_file, 'a') as file:
            file.write('\n' + line_to_add)

def tear_down(game_name):
    append_prototype_to_cmake(game_name)
    project_path = 'Test/Prototype/' + game_name + '/'

    keep_going = True
    if os.path.exists(os.getcwd() + '/' + project_path):
        keep_going = sscript.input_yn('This prototype already exists, do you want to delete it and continue?')
        if keep_going:
            shutil.rmtree(project_path)
    if keep_going:
        shutil.copytree('__applied__', 'Test/Prototype/' + game_name)

    shutil.rmtree('__template__')
    shutil.rmtree('__applied__')

