import unittest
import numpy
from PMC import *

class TestNumericArrayTypes(unittest.TestCase):

    def loopback(self, x):
        y = PMC2Py(Py2PMC(x))
        print x.dtype, y.dtype
        all_equal = (x == y).all()
        if not all_equal:
            print 'x != y'
            print '='*10
            print x
            print '='*10
            print y
            print '\n\n'
        self.assertTrue(all_equal)

    def test_ints_loopback(self):
        for dtype in (numpy.int8, numpy.int16, numpy.int32):
            for nums in (0, 10, 100):
                bits = numpy.dtype(dtype).itemsize*8
                if bits == 32: bits = 31 #avoid OverflowError: Python int too large to convert to C long
                cap = (1 << bits)-1
                print '='*10, 'Test dtype %s, num bits %u, nitems %u'%(dtype, bits, nums)
                a0 = numpy.array(numpy.random.randint(-cap/2, +cap/2, nums), dtype)
                self.loopback(a0)

    def test_uints_loopback(self):
        for dtype in (numpy.uint8, numpy.uint16, numpy.uint32):
            for nums in (0, 10, 100):
                bits = numpy.dtype(dtype).itemsize*8
                if bits == 32: bits = 31 #avoid OverflowError: Python int too large to convert to C long
                cap = (1 << bits)-1
                print '='*10, 'Test dtype %s, num bits %u, nitems %u'%(dtype, bits, nums)
                a0 = numpy.array(numpy.random.randint(0, cap, nums), dtype)
                self.loopback(a0)

    def test_floats_loopback(self):
        for dtype in (numpy.float32, numpy.float64):
            for nums in (0, 10, 100):
                a0 = numpy.array(numpy.random.random_sample(nums), dtype)
                self.loopback(a0)

    def test_complex_loopback(self):
        for dtype in (numpy.complex64, numpy.complex128):
            for nums in (0, 10, 100):
                r = numpy.random.random_sample(nums)
                i = numpy.random.random_sample(nums)
                a0 = numpy.array(r+i*1j, dtype)
                self.loopback(a0)

if __name__ == '__main__':
    unittest.main()
