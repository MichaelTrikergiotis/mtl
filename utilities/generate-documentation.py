#!/usr/bin/env python3

# generate-documentation by Michael Trikergiotis
# 24/10/2020
#
# Generates markdown documentation that contains a list of all for classes and
# functions for mtl.
#
# Copyright (c) Michael Trikergiotis. All Rights Reserved.
# Licensed under the MIT license. See LICENSE in the project root for
# license information.
# See ThirdPartyNotices.txt in the project root for third party licenses
# information.

import re
import os
import zlib
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
    filename only.
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
        # with adding spaces in the front and back we make sure the name isn't just a substring
        # of another string
        if (' ' + formatted_name + ' ') in line:
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

    # a list of possible matches
    match_list = []
    match_list.append((' ' + item_name + ','))
    match_list.append((' ' + item_name + ' '))
    match_list.append((' ' + item_name + '\n'))
    match_list.append((' ' + item_name + '\r\n'))

    count = 1
    cmnt = '// -------------------------------------------------------'
    for idx in range(0, len(lines)):
        # if any of the elements exists in the current line
        if any(match in lines[idx] for match in match_list):
            # check the line above to be the comment format we want
            if cmnt in lines[idx-1]:
                # check the line below to be the comment format we want
                if cmnt in lines[idx+1]:
                    return count
        count = count + 1

    # if we are here nothing was found raise an error
    raise Exception(
        'Could not find the item {0} in {1}'.format(item_name, filename))


def generate_navigation(sources):
    '''
    Given a list of header files returns a string that is properly formatted
    Markdown to create a navigation menu.
    '''

    # keep only the name of each file for the headers
    names = []
    for header in sources:
        names.append(convert_header(extract_filename(header)))

    menu = []
    for name in names:
        menu.append(' |')
        menu.append(' ')
        menu.append('[')
        menu.append(name)
        menu.append('](')
        menu.append('#')
        # remove dots from markdown link to fix navigation problems
        menu.append(name.replace('.', ''))
        menu.append(')')
    menu.append(' |\n')
    return ''.join(menu)


def crc32(file_path):
    '''
    Given the path to a file returns the CRC32 hash for the entire file.
    '''
    # read the entire file as binary
    binary_file = None
    with open(file_path, 'rb') as bf:
        binary_file = bf.read()
    # caclulate and return the CRC32 hash of a file using zlib
    return '%08X' % (zlib.crc32(binary_file, 0) & 0xFFFFFFFF)


def generate_documentation(sources):
    '''
    Given a list of paths to test souce files, extracts class and function
    names and generates documentation.
    '''
    lines = ['# List of classes and functions', '']
    # counts the number of non-member functions, this are free functions not
    # belowing to a class
    count = 0
    # counts the number of classes
    class_count = 0
    # counts the number of class member functions
    class_function_count = 0
    for source in sources:
        comments = get_comments(source)
        names = generate_names(comments)
        count = count + len(names)
        header_filename = '../mtl/' + convert_header(extract_filename(source))
        source_filename = '../tests/' + extract_filename(source)
        head_name = '## {0}\n'.format(convert_header(extract_filename(source)))
        lines.append(head_name)

        # keep track of he last class found to match functions that belong to
        # that class
        last_class = ''
        for name in names:
            # check if the current element is a class
            is_class = False
            # if it contains [@class] it is a class and not a function
            if '[@class]' in name:
                # remove the [@class] part
                name = name.replace('[@class]', '')
                # remove spaces
                name = name.strip(' ')
                # keep the name of the class
                last_class = name

                is_class = True
                # do not count as a function but count as a class
                count = count - 1
                class_count = class_count + 1

            # check track if the current element is a class member function
            is_class_function = False
            if is_class == False:
                if last_class != '':
                    # if it contains mtl::class_name:: then it is a class
                    # member function
                    if (last_class + '::') in name:
                        is_class_function = True
                        # do not count as a function but count as a class
                        # member function
                        count = count - 1
                        class_function_count = class_function_count + 1

            # add the line number for item in the header as Markdown requires
            header_line_number = find_line_header(header_filename, name)
            header_location = header_filename + "#L" + str(header_line_number)

            # add the line number for item in the source as Markdown requires
            source_line_number = find_line_source(source_filename, name)
            source_location = source_filename + "#L" + str(source_line_number)

            # this stores how the markdown text will be formatted
            text = ''

            # if this is a class change markdown for a class
            if is_class == True:
                text = '- [**CLASS**] ' + text

            # if this is a class function change markdown to make it a nested
            # list
            if is_class_function == True:
                text = '  - ' + text

            # if this isn't a class or a class function change markdown for
            # functions
            if is_class == False and is_class_function == False:
                text = '- ' + text

            text = text + '`{0}` [(Documentation)]({1}) [(Examples)]({2})'
            lines.append(text.format(name, header_location, source_location))
        lines.append('\n---------------------------------------------------\n')

    # add the statistics to the markdown
    statistics = []
    statistics.append('## Statistics\n')
    statistics.append('There are {} headers.\n'.format(len(sources)))
    statistics.append('There are {} classes.\n'.format(class_count))
    cfc = class_function_count
    statistics.append('There are {} class member functions.\n'.format(cfc))
    statistics.append('There are {} non-member functions.\n'.format(count))
    # insert the statistics after the second line in the list
    lines = lines[:2] + statistics + lines[2:]

    # add the navigation header after the second line in the list so it is
    # above statistcs
    lines.insert(2, generate_navigation(sources))

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

    # keep a crc32 hash from the file before modification
    crc32_before = crc32(output_filename)

    # write the generated documentation
    with open(output_filename, 'w', encoding='utf-8') as f:
        for line in documentation:
            f.write((line + '\n'))

    # keep a crc32 hash from the file after modification
    crc32_after = crc32(output_filename)

    # if the file changed
    if crc32_before != crc32_after:
        print('Finished generating documentation. The ', end='')
        print('output is stored in {}.'.format(output_filename[3:]))
    # if the file didn't change
    else:
        print('No changes to the documentation file.')


if __name__ == "__main__":
    main_function()
