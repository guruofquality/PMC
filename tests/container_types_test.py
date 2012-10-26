
import unittest
from PMC import *

class TestContainerTypes(unittest.TestCase):

    def loopback(self, x):
        y = PMC2Py(Py2PMC(x))
        print type(x), type(y)
        self.assertEqual(x, y)

    def test_tuple_container(self):
        for i in range(10):
            t0 = tuple(range(i))
            self.loopback(t0)

    def test_list_container(self):
        l0 = [1, 2, 3, 4]
        self.loopback(l0)

    def test_set_container(self):
        s0 = set([1, 2, 3, 4])
        self.loopback(s0)

    def test_dict_container(self):
        d0 = {'foo': 1, 'bar': 2}
        self.loopback(d0)

    def test_nested_container(self):
        x0 = {'foo': (1, 2, 3, 4), 'bar': [1, 2, 3, 4]}
        self.loopback(x0)

if __name__ == '__main__':
    unittest.main()
