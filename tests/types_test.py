
import unittest
from PMC import *

class TestTypes(unittest.TestCase):

    def loopback(self, x):
        y = PMC2Py(Py2PMC(x))
        self.assertEqual(x, y)

    def test_none(self):
        self.loopback(None)

    def test_bool(self):
        self.loopback(True)
        self.loopback(False)

if __name__ == '__main__':
    unittest.main()
