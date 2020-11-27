#!/usr/bin/env python3

# fmt-tidy by Michael Trikergiotis
# 24/09/2020
#
# The script's current capabilities :
# 1.) Report lines beyond a certain length.
# 2.) Report lines with comments that are not formatted properly.


from common import check_cwd, get_headers, get_sources


def check_line_length(file_list, length):
    '''
    Given a list of files returns a list of tuples. Each tuple contains the
    filename and the lines that are above the desired length. If a file doesn't
    have lines beyond the desired length it will not be included in the list.
    '''
    longer_files = []
    for file in file_list:
        lines = []
        with open(file, 'r', encoding='utf-8') as f:
            lines = f.readlines()

        longer_lines = []
        for idx in range(0, len(lines)):
            # count tabs as 4 characters to be more consistent with how lines
            # are displayed in code editors, this makes it so lines with tabs
            # don't appear to go past vertical rulers set to 100 characters
            num_chars = len(lines[idx]) + (lines[idx].count('\t') * 3)
            if num_chars > length:
                longer_lines.append(idx + 1)

        if len(longer_lines) > 0:
            longer_files.append((str(file), longer_lines))

    return longer_files


def bad_comment(comment):
    '''
    Check if the line contain comments, if it doesn't it always returns false.
    If it does contain multiline comments (/* or */) or one line comments
    (//) that do not start with a space return true.
    '''
    if '/*' in comment or '*/' in comment:
        return True
    elif '//' in comment:
        if '// ' in comment:
            return False
        else:
            return True
    return False


def check_comments_space(file_list):
    '''
    Given a list of files returns a list of tuples. Each tuple contains the
    filename and the lines that contain comments that don't start with a 
    space character. If a file contains only comments that start with a space
    character it will not be included in the list.
    '''
    bad_comments_filelist = []
    for file in file_list:
        lines = []
        with open(file, 'r', encoding='utf-8') as f:
            lines = f.readlines()

        bad_comments_file = []
        for idx in range(0, len(lines)):
            if bad_comment(lines[idx]):
                bad_comments_file.append(idx + 1)

        if len(bad_comments_file) > 0:
            bad_comments_filelist.append((str(file), bad_comments_file))

    return bad_comments_filelist


# =============================================================================


def main_function():
    '''
    The main function for the script.
    '''
    # the desired line length
    line_length = 100

    # check we are in the correct folder and complain and exit if we are not
    check_cwd()

    # get a list of header files
    headers = get_headers()
    # get a list of source files
    sources = get_sources()

    # get all the header files beyond the desired line length
    longer_headers = check_line_length(headers, line_length)
    # get all the source files beyond the desired line length
    longer_sources = check_line_length(sources, line_length)

    # get all header files that have improperly formatted comments
    bad_comment_headers = check_comments_space(headers)
    # get all source files that have improperly formatted comments
    bad_comment_sources = check_comments_space(sources)

    if len(longer_headers) > 0 or len(longer_sources) > 0:
        if len(longer_headers) > 0:
            # print the number of header files containing lines beyond the
            # desired length
            print('\n----------------------------------------------', end='')
            print('-------------------------')
            print('There are ', end='')
            print('{} header files (.hpp) with'.format(
                len(longer_headers)), end='')
            print(' lines longer than {} characters :'.format(line_length))
            print('------------------------------------------------', end='')
            print('-----------------------')

            for filename, lines in longer_headers:
                print('In {} lines '.format(filename), end='')
                for line in lines:
                    print('{}, '.format(line), end='')
                print('\b\b. ')

        if len(longer_sources) > 0:
            # print the number of source files containing lines beyond the
            # desired length
            print('\n----------------------------------------------', end='')
            print('-------------------------')
            print('There are ', end='')
            print('{} source files (.cpp) with'.format(
                len(longer_sources)), end='')
            print(' lines longer than {} characters :'.format(line_length))
            print('--------------------------------------------------', end='')
            print('---------------------')

            for filename, lines in longer_sources:
                print('In {} lines '.format(filename), end='')
                for line in lines:
                    print('{}, '.format(line), end='')
                print('\b\b.')

        if len(bad_comment_headers) > 0 or len(bad_comment_sources) > 0:
            # divider between the printing files with lines beyond desired
            # length and printing files with improperly formatted comments
            print('\n\n')
            print('=================================================', end='')
            print('======================\n\n')

    # --------
    if len(bad_comment_headers) > 0 or len(bad_comment_sources) > 0:
        if len(bad_comment_headers) > 0:
            # print the number of header files containing improperly formatted
            # comments
            print('\n-----------------------------------------------', end='')
            print('---------------------')
            print('There are ', end='')
            print('{} header files (.hpp) '.format(
                len(bad_comment_headers)), end='')
            print('with improperly formatted comments :')
            print('--------------------------------------------', end='')
            print('------------------------')

            for filename, lines in bad_comment_headers:
                print('In {} lines '.format(filename), end='')
                for line in lines:
                    print('{}, '.format(line), end='')
                print('\b\b. ')

        if len(bad_comment_sources) > 0:
            # print the number of source files containing improperly formatted
            # comments
            print('\n----------------------------------------------', end='')
            print('----------------------')
            print('There are ', end='')
            print('{} source files (.cpp) '.format(
                len(bad_comment_sources)), end='')
            print('with improperly formatted comments :')
            print('--------------------------------------------', end='')
            print('------------------------')

            for filename, lines in bad_comment_sources:
                print('In {} lines '.format(filename), end='')
                for line in lines:
                    print('{}, '.format(line), end='')
                print('\b\b. ')

    # if there is nothing to report then print a message that everything
    # is fine
    if len(longer_headers) == 0 and len(longer_sources) == 0:
        if len(bad_comment_headers) == 0 and len(bad_comment_sources) == 0:
            print('No files contain lines ', end='')
            print('with length beyond {}.'.format(line_length))
            print('No files contain lines with ', end='')
            print('improperly formatted comments.')


if __name__ == "__main__":
    main_function()
