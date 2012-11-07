# Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

import unittest
from PMC import *

class TestOperatorOverloads(unittest.TestCase):

    def test_pmc_numbers_equal(self):
        self.assertEqual(Py2PMC(42), Py2PMC(42))
        self.assertEqual(Py2PMC(4.2), Py2PMC(4.2))
        self.assertNotEqual(Py2PMC(4.2), Py2PMC(2.4))

    def test_pmc_arrays_equal(self):
        try: import numpy
        except ImportError: return
        self.assertEqual(Py2PMC(numpy.array([], numpy.int16)), Py2PMC(numpy.array([], numpy.int16)))
        self.assertEqual(Py2PMC(numpy.array([1, 2, 3, 4], numpy.int16)), Py2PMC(numpy.array([1, 2, 3, 4], numpy.int16)))

if __name__ == '__main__':
    unittest.main()
