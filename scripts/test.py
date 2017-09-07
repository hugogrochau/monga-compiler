#!/usr/bin/env python3
''' Unit tests '''

import unittest
import os
import glob
from subprocess import Popen, PIPE

build_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build'))
test_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '../test'))

def tokenize(filename):
    ''' Runs the tokenizer on a file and returns the output '''
    file = open(filename)
    source_code = file.read().encode('utf-8')
    process = Popen(build_dir + '/tokenizer', stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
    process.stdin.write(source_code)
    stdout = process.communicate()
    file.close()
    return str(stdout[0], 'utf-8')

class Tests(unittest.TestCase):
    ''' Unit tests '''

    def test_tokenizer(self):
        '''should correctly tokenize monga source files'''
        for filename in glob.glob(test_dir + '/**/*.in.monga'):
            file = open(filename.replace(".in.monga", ".out.tokens"))
            output = tokenize(filename)
            expected = file.read()
            self.assertEqual(output, expected)
            file.close()

if __name__ == '__main__':
    unittest.main()
