# Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

import unittest
from PMC import *

class TestBasicTypes(unittest.TestCase):

    def loopback(self, x):
        y = PMC2Py(Py2PMC(x))
        print type(x), type(y)
        #ctypes are not as smart as numpy,
        #give the assert equal some help
        if hasattr(x, 'value'): x = x.value
        if hasattr(y, 'value'): y = y.value
        self.assertEqual(x, y)

    def test_none(self):
        self.loopback(None)

    def test_nonzero(self):
        self.assertTrue(Py2PMC(1))
        self.assertFalse(Py2PMC(None))

    def test_py2pmc_already_pmc(self):
        p0 = Py2PMC(123)
        p1 = Py2PMC(p0)
        self.assertEqual(p0, p1)

    def test_bool(self):
        self.loopback(True)
        self.loopback(False)

        import ctypes
        self.loopback(ctypes.c_bool(True))
        self.loopback(ctypes.c_bool(False))

    def test_ints(self):
        self.loopback(int(-420000))
        self.loopback(long(-420000))
        import ctypes
        self.loopback(ctypes.c_uint8(42))
        self.loopback(ctypes.c_int8(-42))
        self.loopback(ctypes.c_uint16(4200))
        self.loopback(ctypes.c_int16(-4200))
        try: import numpy
        except ImportError: return
        self.loopback(numpy.uint16(4200))
        self.loopback(numpy.int16(-4200))

    def test_floats(self):
        self.loopback(4.2)
        import ctypes
        self.loopback(ctypes.c_float(4.2))
        self.loopback(ctypes.c_double(4.2))
        try: import numpy
        except ImportError: return
        self.loopback(numpy.float32(4.2))
        self.loopback(numpy.float64(4.2))

    def test_complex(self):
        self.loopback(4+2j)
        try: import numpy
        except ImportError: return
        self.loopback(numpy.complex64(4-2j))
        self.loopback(numpy.complex128(4-1j))

    def test_string(self):
        self.loopback("hello world")

    def test_serialize(self):
        target_object = [42, "hello world"]
        data = PMC.serialize(PMC_M(target_object), "TEXT")
        print target_object, "->", data
        result_object = PMC.deserialize(data, "TEXT")()
        self.assertEqual(target_object, result_object)

    def test_isinstance(self):
        foo = PMCC()
        self.assertTrue(isinstance(foo, PMCC))
        self.assertFalse(isinstance(foo, PMC))
        bar = PMC()
        self.assertTrue(isinstance(bar, PMCC))
        self.assertTrue(isinstance(bar, PMC))

if __name__ == '__main__':
    unittest.main()
