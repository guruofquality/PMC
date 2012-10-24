
import unittest
from PMC import *

class TestContainerTypes(unittest.TestCase):

    def loopback(self, x):
        y = PMC2Py(Py2PMC(x))
        print type(x), type(y)
        self.assertEqual(x, y)

    def test_tuple_container(self):
        t0 = (1, 2, 3, 4)
        self.loopback(t0)

    def test_list_container(self):
        l0 = [1, 2, 3, 4]
        self.loopback(l0)

    def test_set_container(self):
        s0 = set([1, 2, 3, 4])
        self.loopback(s0)

if __name__ == '__main__':
    unittest.main()
