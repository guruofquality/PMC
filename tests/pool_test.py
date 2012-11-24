# Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

import unittest
from PMC import *

class TestPool(unittest.TestCase):

    def test_make_pool(self):
        pool = PMCPool()
        self.assertEqual(len(pool), 0)
        pool.append(Py2PMC(1))
        self.assertEqual(len(pool), 1)

    def test_get_pool(self):
        pool = PMCPool()
        pool.append(Py2PMC(1))
        p0 = pool.get()
        p1 = pool.get()
        self.assertTrue(p0)
        self.assertFalse(p1)
        p0 = None
        p2 = pool.get()
        self.assertTrue(p2)

if __name__ == '__main__':
    unittest.main()
