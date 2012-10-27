import unittest
import numpy
from PMC import *

class TestNumericArrayTypes(unittest.TestCase):

    def loopback(self, x):
        y = PMC2Py(Py2PMC(x))
        print type(x), type(y)
        self.assertTrue((x == y).all())

    def test_something(self):
        a0 = numpy.array([], numpy.uint8)
        self.loopback(a0)
        a3 = numpy.array([1, 2, 3], numpy.uint8)
        self.loopback(a3)

if __name__ == '__main__':
    unittest.main()
