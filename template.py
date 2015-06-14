#!/usr/bin/python

gameName = "TestDuck"

import os, shutil, errno, string

if os.path.exists('.applied'):
    shutil.rmtree('.applied')
shutil.copytree('.template', '.applied')

for root, dirs, files in os.walk(".applied"):
    path = root.split('/')
    print (len(path) - 1) * '---', os.path.basename(root)
    for file in files:
        if "$!GAME_NAME!$" in file:
            print len(path) * '---', file
    if "$!GAME_NAME!$" in os.path.basename(root):
        newRoot = string.replace(root, '$!GAME_NAME!$', gameName)
        os.rename(root, newRoot)
        root = newRoot
