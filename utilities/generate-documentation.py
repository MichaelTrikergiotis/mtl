#!/usr/bin/python3

# generate-documentation by Michael Trikergiotis
# 24/10/2020
#
# Generates markdown documentation that contains a list of all for classes and
# functions for mtl.

import re
import os
from common import check_cwd, get_headers, get_sources


def keep_tests(sources):
    '''
    Given a list of sources keep only files that contain "tests_filename.cpp".
    '''
    keep = []
    for source in sources:
        # use regular expression to search if a file contains tests_ and ends
        # with the .cpp extension
        found = re.search("tests_.*cpp", str(source))
        if found:
            keep.append(source)

    # if the list is empty there is an error
    if len(keep) == 0:
        raise Exception("Error. Could not match any files with tests_.cpp.")

    return keep


def extract_filename(source_path):
    '''
    Given the path to a souce file, in the form tests_filename.cpp, retruns the
    filename only the filename.
    '''

    # get filename only
    filename = os.path.basename(source_path)

    # if filename is empty here there is an error
    if filename == "" or filename == None:
        raise Exception("Could not extract filename from path.")

    return filename


def convert_header(filename):
    '''
    Given a souce file, in the form tests_filename.cpp, retruns the header
    with the same name.
    '''
    # if filename is empty here there is an error
    if filename == "" or filename == None:
        raise Exception("Could not extract filename from path.")

    # remove tests_ from the start and .cpp from the end
    if filename.startswith('tests_') and filename.endswith('.cpp'):
        # remove tests_ from the start
        filename = filename[6:]
        # remove .cpp from the end
        filename = filename[:-4]
    else:
        print(filename)
        # if the filename doesn't match throw an error
        raise Exception("Filename doesn't seem to be correct.")

    # add .hpp at the end
    filename = filename + ".hpp"
    return filename


def get_comments(source_path):
    '''
    Given the path to a souce file, in the form tests_filename.cpp, retruns the
    comments containing the list of names to be tested.
    '''
    header_name = convert_header(extract_filename(source_path))
    lines = []
    with open(source_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    # find where we start
    start_index = 1
    for line in lines:
        if header_name in line:
            break
        start_index = start_index + 1

    # find we stop
    end_index = 0
    for end_index in range(start_index, len(lines)):
        if lines[end_index].startswith('// '):
            end_index = end_index + 1
        else:
            break

    # grab the comments containing the names
    names = lines[start_index: end_index]
    return names


def generate_names(comments):
    '''
    Given specially formatted comments generates a list of names for mtl
    functions and classes.
    '''
    # join all to a string
    combined = ""
    combined = combined.join(comments)
    # remove '//  '
    combined = combined.replace('// ', '')
    # remove '\n'
    combined = combined.replace('\n', '')
    # split all on ','
    names = combined.split(',')
    # remove spaces from start and end
    formatted_names = []

    # remove whitespace from both sides
    for name in names:
        formatted_names.append(name.strip(' '))

    return formatted_names


def remove_namespaces(item_name):
    '''
    Given an item name in the format mtl::string::join returns the name without
    any of the namespaces. If there is not namespace returns the original name.
    '''
    # we conver the item name to uppercase because the point we want to find in
    # the header file has the name of the item with capital letters
    item_name = item_name.upper()
    start_index = item_name.rfind('::')
    formatted_name = ""
    if start_index == -1:
        formatted_name = item_name
    else:
        # move the index beyond the last ::
        start_index = start_index + 2
        formatted_name = item_name[start_index:]
    return formatted_name


def find_line_header(filename, item_name):
    '''
    Given a filename and a class or function name finds the line where the it
    is located in the header.
    '''
    lines = []
    with open(filename, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    count = 1
    formatted_name = remove_namespaces(item_name)
    for line in lines:
        if formatted_name in line:
            return count
        count = count + 1

    # if we are here nothing was found so there is an error
    raise Exception(
        'Could not find the item {0} in {1}'.format(formatted_name, filename))


def find_line_source(filename, item_name):
    '''
    Given a filename and a class or function name finds the line where the it
    is located in the source file. 
    '''
    lines = []
    with open(filename, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    count = 1
    for idx in range(0, len(lines)):
        if item_name in lines[idx]:
            cmnt = '// -------------------------------------------------------'
            # check the line above to be the comment format we want
            if cmnt in lines[idx-1]:
                # check the line below to be the comment format we want
                if cmnt in lines[idx+1]:
                    return count
        count = count + 1

    # if we are here nothing was found raise an error
    raise Exception(
        'Could not find the item {0} in {1}'.format(item_name, filename))


def generate_documentation(sources):
    '''
    Given a list of paths to test souce files, extracts class and function
    names and generates documentation.
    '''
    lines = ['# List of classes and functions', '']
    count = 0
    for source in sources:
        comments = get_comments(source)
        names = generate_names(comments)
        count = count + len(names)
        header_filename = '../mtl/' + convert_header(extract_filename(source))
        source_filename = '../tests/' + extract_filename(source)
        lines.append('## {0} with {1} items\n'.format(
            convert_header(extract_filename(source)), len(names)))
        for name in names:
            # add the line number for item in the header as Markdown requires
            header_line_number = find_line_header(header_filename, name)
            header_location = header_filename + "#L" + str(header_line_number)

            # add the line number for item in the source as Markdown requires
            source_line_number = find_line_source(source_filename, name)
            source_location = source_filename + "#L" + str(source_line_number)

            text = '- {0} [(Documentation)]({1}) [(Examples)]({2})'
            lines.append(text.format(name, header_location, source_location))
        lines.append('\n---------------------------------------------------\n')

    # insert the third line to be the total of all classes and functions
    lines.insert(2, 'There are {} items in total.\n'.format(count))

    # remove the last line to generate a more standards compliant Markdown
    lines = lines[:-1]
    return lines


def main_function():
    # check we are in the correct folder and complain and exit if we are not
    check_cwd()

    # get a list of header files
    headers = get_headers()
    # get a list of source files
    sources = get_sources()

    # keep only pathname with tests_filename.cpp in them
    sources = keep_tests(sources)

    # extract names for mtl classes and functions from the test files
    documentation = generate_documentation(sources)

    output_filename = '../docs/listing.md'
    # write the generated documentation
    with open(output_filename, 'w', encoding='utf-8') as f:
        for line in documentation:
            f.write((line + '\n'))

    print('Finished generating documentation. The output is stored ', end='')
    print('in {}.'.format(output_filename[3:]))


if __name__ == "__main__":
    main_function()
