
import unittest
from PMC import *

class TestTypes(unittest.TestCase):

    def loopback(self, x):
        y = PMC2Py(Py2PMC(x))
        print type(x), type(y)
        self.assertEqual(x, y)

    def test_none(self):
        self.loopback(None)

    def test_bool(self):
        self.loopback(True)
        self.loopback(False)

    def test_ints(self):
        self.loopback(int(-420000))
        self.loopback(long(-420000))
        import ctypes
        self.loopback(ctypes.c_uint8(42))
        self.loopback(ctypes.c_int8(-42))
        self.loopback(ctypes.c_uint16(4200))
        self.loopback(ctypes.c_int16(-4200))
        try:
            import numpy
            self.loopback(numpy.uint16(4200))
            self.loopback(numpy.int16(-4200))
        except ImportError: pass

if __name__ == '__main__':
    unittest.main()
