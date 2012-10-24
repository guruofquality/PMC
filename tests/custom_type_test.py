import unittest
from PMC import *
from foo_bar import *

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, FooBar),
    py2pmc = swig_foo_bar_to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_swig_foo_bar,
    pmc2py = pmc_to_swig_foo_bar,
)

class TestBasicTypes(unittest.TestCase):

    def test_make_a_foo_bar(self):
        fb = FooBar()
        fb._foo = 4
        fb._bar = 2

    def test_loopback_fb(self):
        fb = FooBar()
        fb._foo = 4
        fb._bar = 2

        as_a_pmc = Py2PMC(fb)
        fb_lb = PMC2Py(as_a_pmc)

        print fb_lb.foo()
        print fb_lb.bar()

        self.assertEqual(fb.foo(), fb_lb.foo())
        self.assertEqual(fb.bar(), fb_lb.bar())

if __name__ == '__main__':
    unittest.main()
