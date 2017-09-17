#!/usr/bin/env python3
''' Unit tests '''

import unittest
import os
import glob
import subprocess

# Constants

BUILD_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))
TEST_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../test'))

# Tokenizer

def tokenize(file_name):
    ''' Runs the tokenizer on a file and returns the output '''
    # Read source file
    file = open(file_name)
    source_code = file.read().encode('utf-8')
    file.close()

    # Run the tokenizer binary on the file's content
    process = subprocess.Popen(
        BUILD_DIR + '/tokenizer',
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        shell=True
    )
    process.stdin.write(source_code)
    stdout = process.communicate()

    # Returns the output
    return str(stdout[0], 'utf-8')

def test_tokenizer():
    ''' It should correctly tokenize monga source code '''
    for file_name in glob.glob(TEST_DIR + '/tokenizer/**/*.in.monga'):
        # Tokenize input file
        received = tokenize(file_name)

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

# Parser

def parse(file_name):
    ''' Runs the parser on a .monga file and returns the output '''
    # Read source file
    file = open(file_name)
    source_code = file.read().encode('utf-8')
    file.close()

    # Run the parse binary on the file's content
    process = subprocess.Popen(
        BUILD_DIR + '/parser',
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        shell=True
    )
    process.stdin.write(source_code)
    stdout = process.communicate()

    # Return the output
    return str(stdout[0], 'utf-8')

def test_parser_pass():
    ''' It should parse valid monga syntax '''
    for file_name in glob.glob(TEST_DIR + '/parser/pass/*.monga'):
        # Parse the input file
        output = parse(file_name)

        # Generate test name based on file name
        file_name_short = file_name.split('/')[-1]
        test_name = '[pass] ' + file_name_short.split('.')[0]

        # Yield a dynamic test case the file
        expected = ''
        message = 'It should parse valid monga syntax'
        params = [output, expected, message]
        yield test_name, equality_test, params

def test_parser_fail():
    ''' It should throw an error when parsing invalid monga syntax '''
    for file_name in glob.glob(TEST_DIR + '/parser/fail/*.monga'):
        # Parse the input file
        output = parse(file_name)

        # Generate test name based on file name
        file_name_short = file_name.split('/')[-1]
        test_name = '[expected fail] ' + file_name_short.split('.')[0]

        # Yield a dynamic test case the file
        not_expected = ''
        message = 'It should throw an error when parsing invalid monga syntax'
        params = [output, not_expected, message]
        yield test_name, inequality_test, params

# Dynamic test runner

def equality_test(self, received, expected, message=None):
    ''' Equality test function to yield '''
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


TestCase = add_tests(
    test_tokenizer,
    test_parser_pass,
    test_parser_fail
)(TestCase)

if __name__ == '__main__':
    unittest.main()
