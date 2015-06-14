#!/usr/bin/env python3

import os, shutil, errno, string, pyratemp

def start_template(gameName, gameAbbr):
    gameName = ''.join(gameName.split(' '))
    prep_work()
    for root, dirs, files in os.walk(".template"):
        #exclude . directories and files
        dirs[:] = [d for d in dirs if not d.split('/')[-1].startswith('.')]
        files[:] = [f for f in files if not f.startswith('.')]

        newRoot = root.replace('.template', '.applied') 

        #copy files
        for file in files:
            oldPath = root + '/' + file
            newPath = newRoot + '/' + file
            newPath = newPath.replace('$!GAME_ABBR!$', gameAbbr)
            newPath = newPath.replace('$!GAME_NAME!$', gameName)
            if not os.path.exists(os.path.dirname(newPath)):
                os.makedirs(os.path.dirname(newPath))
            shutil.copyfile(oldPath, newPath)
            template = pyratemp.Template(filename=newPath)
            result = template(GAME_NAME=gameName, GAME_ABBR=gameAbbr)
            with open(newPath, "wt") as out_file:
                out_file.write(result)
    print_directory_tree()
    shutil.move('.applied', 'Test/Prototype/' + gameName)
    shutil.rmtree('.template')

def prep_work():
    if os.path.exists('.applied'):
        shutil.rmtree('.applied')
    if os.path.exists('.template'):
        shutil.rmtree('.template')
    os.makedirs('.applied')
    os.system("git clone git@bitbucket.org:ilikeducks/ancona-template-game.git .template")


def print_directory_tree():
    for root, dirs, files in os.walk(".applied"):
        path = root.split('/')
        print((len(path) - 1) * '---', os.path.basename(root))
        for file in files:
            print(len(path) * '---', file)
