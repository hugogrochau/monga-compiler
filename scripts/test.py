#!/usr/bin/env python3
''' Unit tests '''

import unittest
import os
import glob
from subprocess import Popen, PIPE

build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))
test_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../test'))

def tokenize(file_name):
    ''' Runs the tokenizer on a file and returns the output '''
    file = open(file_name)
    source_code = file.read().encode('utf-8')
    process = Popen(build_dir + '/tokenizer', stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
    process.stdin.write(source_code)
    stdout = process.communicate()
    file.close()
    return str(stdout[0], 'utf-8')

def add_tests(generator):
    def class_decorator(cls):
        for func, file_name, expected in generator():
            test = lambda self, i=file_name, o=expected, f=func: f(self, i, o)
            file_name_short = file_name.split('/')[-1]
            test_name = file_name_short.split('.')[0]
            test.__name__ = "test %s" % (test_name)
            setattr(cls, test.__name__, test)
        return cls
    return class_decorator

def test_tokenizer():
    def t(self, file_name, expected):
        self.assertEqual(tokenize(file_name), expected)

    '''should correctly tokenize monga source files'''
    for file_name in glob.glob(test_dir + '/tokenizer/**/*.in.monga'):
        file = open(file_name.replace('.in.monga', '.out.tokens'))
        expected = file.read()
        yield t, file_name, expected
        file.close()

class TestCase(unittest.TestCase):
    pass
TestCase = add_tests(test_tokenizer)(TestCase)

if __name__ == '__main__':
    unittest.main()
