#!/usr/bin/python3

# mtl_common by Michael Trikergiotis
# 24/10/2020
#
# Common functionality shared between Python scripts in utilities folder.

import os
import sys
import glob
from pathlib import Path


def check_cwd():
    '''
    Checks we are run from the utilities folder and if not prints an error and
    exits.
    '''

    util = 'utilities'
    len_util = len(util)
    # get the current working directory
    cwd = os.getcwd()
    # check that the current working directory is utilities
    if len(cwd) <= (len_util) or cwd[-len_util:] != util:
        print('Error. The script is not run from the correct folder.')
        print('The script should be in the utilities folder for it to', end='')
        print(' correctly find the mtl library folders it needs.')
        sys.exit()


def get_headers():
    '''
    Returns a list of all the header files that end with .hpp in the mtl
    folder.
    '''
    # get the parent directory of the utilities folder
    one_dir_up = str(Path(os.getcwd()).parent)
    # add the mtl folder to the path
    mtl_folder = Path(one_dir_up + '/mtl')
    # get all the .hpp files from the mtl folder
    headers = [x for x in mtl_folder.glob('*.hpp')]

    # if no header files where found then it is an error report it and exit
    if len(headers) == 0:
        print("Error. Couldn't find any header files in the mtl directory.")
        print('You are either running the script from an incorrect', end='')
        print(' folder or the header files are missing.')
        sys.exit()

    return headers


def get_sources():
    '''
    Returns a list of all the source file that end with .cpp in the tests
    folder.
    '''
    # get the parent directory of the utilities folder
    one_dir_up = str(Path(os.getcwd()).parent)
    # add the tests folder to the path
    tests_folder = Path(one_dir_up + '/tests')
    # get all the .hpp files from the tests folder
    sources = [x for x in tests_folder.glob('*.cpp')]

    # if no source files where found then it is an error report it and exit
    if len(sources) == 0:
        print("Error. Couldn't find any source files in the tests directory.")
        print('You are either running the script from an incorrect', end='')
        print(' folder or the source files are missing.')
        sys.exit()

    return sources
