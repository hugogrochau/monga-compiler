#!/usr/bin/env python3
''' Unit tests '''

import unittest
import os
import glob
from subprocess import Popen, PIPE

BUILD_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))
TEST_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../test'))

def tokenize(file_name):
    ''' Runs the tokenizer on a file and returns the output '''
    file = open(file_name)
    source_code = file.read().encode('utf-8')
    process = Popen(BUILD_DIR + '/tokenizer', stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
    process.stdin.write(source_code)
    stdout = process.communicate()
    file.close()
    return str(stdout[0], 'utf-8')

def add_tests(generator):
    ''' function to dynamically add tests '''
    def class_decorator(cls):
        ''' TestCase decorator '''
        for test_function, received, expected, test_name in generator():
            test = lambda self, r=received, e=expected, f=test_function: f(self, r, e)
            test.__name__ = "test %s" % (test_name)
            setattr(cls, test.__name__, test)
        return cls
    return class_decorator

def test_tokenizer():
    ''' should correctly tokenize monga source files '''
    def test(self, received, expected):
        ''' function to yield '''
        self.assertEqual(received, expected)

    for file_name in glob.glob(TEST_DIR + '/tokenizer/**/*.in.monga'):
        received = tokenize(file_name)
        expected_file = open(file_name.replace('.in.monga', '.out.tokens'))
        expected = expected_file.read()

        file_name_short = file_name.split('/')[-1]
        test_name = file_name_short.split('.')[0]
        yield test, received, expected, test_name
        expected_file.close()

class TestCase(unittest.TestCase):
    ''' mock test case '''
    pass
TestCase = add_tests(test_tokenizer)(TestCase)

if __name__ == '__main__':
    unittest.main()
