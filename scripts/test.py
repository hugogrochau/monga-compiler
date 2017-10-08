#!/usr/bin/env python3
''' Unit tests '''

import unittest
import os
import glob
import subprocess

# Constants

BUILD_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))
TEST_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../test'))

def runner(executable, file_name):
    ''' Runs the executable on a file and returns the output '''
    # Read source file
    file = open(file_name)
    source_code = file.read().encode('utf-8')
    file.close()

    # Run the tokenizer binary on the file's content
    process = subprocess.Popen(
        os.path.join(BUILD_DIR, executable),
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        shell=True
    )
    process.stdin.write(source_code)
    stdout = process.communicate()

    # Returns the output
    return str(stdout[0], 'utf-8')

# t1

def test_t1():
    ''' It should correctly tokenize monga source code '''
    glob_string = os.path.join(TEST_DIR, 't1/**/*.in.monga')
    for file_name in glob.glob(glob_string):
        # Tokenize input file
        received = runner('t1', file_name)

        # Load output file
        expected_file = open(file_name.replace('.in.monga', '.out.tokens'))
        expected = expected_file.read()
        expected_file.close()

        # Generate test name based on file name
        file_name_short = file_name.split('/')[-1]
        test_name = file_name_short.split('.')[0]

        # Yield a dynamic test case for the file
        params = [received, expected]
        yield test_name, equality_test, params

# t2

def test_t2_pass():
    ''' It should parse valid monga syntax '''
    glob_string = os.path.join(TEST_DIR, 't2/pass/*.monga')
    for file_name in glob.glob(glob_string):
        # Parse the input file
        output = runner('t2', file_name)

        # Generate test name based on file name
        file_name_short = file_name.split('/')[-1]
        test_name = '[pass] ' + file_name_short.split('.')[0]

        # Yield a dynamic test case the file
        expected = ''
        message = 'It should parse valid monga syntax'
        params = [output, expected, message]
        yield test_name, equality_test, params

def test_t2_fail():
    ''' It should throw an error when parsing invalid monga syntax '''
    glob_string = os.path.join(TEST_DIR, 't2/fail/*.monga')
    for file_name in glob.glob(glob_string):
        # Parse the input file
        output = runner('t2', file_name)

        # Generate test name based on file name
        file_name_short = file_name.split('/')[-1]
        test_name = '[expected fail] ' + file_name_short.split('.')[0]

        # Yield a dynamic test case the file
        not_expected = ''
        message = 'It should throw an error when parsing invalid monga syntax'
        params = [output, not_expected, message]
        yield test_name, inequality_test, params

# t3

def test_t3():
    ''' It should correctly generate a AST for monga source code '''
    glob_string = os.path.join(TEST_DIR, 't3/**/*.in.monga')
    for file_name in glob.glob(glob_string):
        # Generate AST for input file
        received = runner('t3', file_name)

        # Load output file
        expected_file = open(file_name.replace('.in.monga', '.out.tree'))
        expected = expected_file.read()
        expected_file.close()

        # Generate test name based on file name
        file_name_short = file_name.split('/')[-1]
        test_name = file_name_short.split('.')[0]

        # Yield a dynamic test case for the file
        params = [received, expected]
        yield test_name, equality_test, params

# Dynamic test runner

def equality_test(self, received, expected, message=None):
    ''' Equality test function to yield '''
    self.maxDiff = None
    self.assertEqual(received, expected, message)

def inequality_test(self, received, not_expected, message=None):
    ''' Inequality test function to yield '''
    self.assertNotEqual(received, not_expected, message)

def add_tests(*generators):
    ''' Function to dynamically add tests '''
    def class_decorator(cls):
        ''' TestCase decorator '''
        for generator in generators:
            for test_name, test_function, params in generator():
                test = lambda self, p=params, f=test_function: f(self, *p)
                test.__name__ = "test %s" % (test_name)
                setattr(cls, test.__name__, test)
        return cls
    return class_decorator

class TestCase(unittest.TestCase):
    ''' Mock test case '''
    pass

# init

TestCase = add_tests(
    test_t1,
    test_t2_pass,
    test_t2_fail,
    test_t3
)(TestCase)

if __name__ == '__main__':
    unittest.main()
