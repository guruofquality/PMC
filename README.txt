########################################################################
## Polymorphic container for C++ with optional python bindings
########################################################################

PMC is just another simple polymorphic container class for C++.
The goal is that any C++ object can be held inside of a PMC.
Then, the polymorphic container can be passed around as type PMC.
And finally, the object can be casted out of the PMC container.

* See BUILDING.txt for dependencies and compilation instructions

------------------------------------------------------------------------
-- Some notable attributes
------------------------------------------------------------------------

* PMCs are reference counted objects:
Which makes copying a PMC a light-weight operation.
Only the reference count for the PMC is incremented,
but there is only one copy of the contained object.

* PMCs allow for object modification:
Once created, the internal object can be accessed and modified.
A non-const reference to the internal object can be obtained.
Use this reference to read/write/modify the internal object.

* PMCC offers const-correctness:
To ensure read-only access of the object, pass the container as a PMCC.
The PMC container can be implicitly casted to a PMCC through assignment.
Only const references to the object can be retrieved from the PMCC.

* PMC overloaded equality operator:
Any two PMCs can be compared for equality without
the user knowing anything about the contained objects.

------------------------------------------------------------------------
-- Quick c++ code snippet
------------------------------------------------------------------------

#include <PMC/PMC.hpp>

//make a container with an empty FooBar
PMC p = PMC::make(FooBar());

//get a reference to foo bar
FooBar &fb = p.cast<FooBar>();
fb.foo = 12345; //modify object

//read-only conatiner holding object
PMCC p_const = p;

//get a const-reference to foo bar
const FooBar &fb = p_const.cast<FooBar>();
std::cout << fb.foo << std::endl; //read object

//create another FooBar, init first
FooBar fb2;
fb2.foo = 12345;
PMC p2 = PMC::make(fb2); //p2 now has a copy of fb2

//compare two PMCs:
std::cout << "should be true: " << (p == p2) << std::endl;

------------------------------------------------------------------------
-- Python support
------------------------------------------------------------------------
The PMC type can be converted into native python types and vice-versa.
The PMC python module comes with a extendable type registry system.
This registry is pre-loaded for most if not all built-in python data types.
In addition, new types can easily be added to extend the type registry.
See tests/custom_type_test.py as an example of registering a custom type.

------------------------------------------------------------------------
-- Python support documentation
------------------------------------------------------------------------
#This import brings in the following routines, documented below:
from PMC import *

def RegisterPy2PMC(is_py, py2pmc):
    """
    Register a conversion from a python type to a PMC type.
    \param is_py a function that checks for a python type match
    \param py2pmc a function to convert a python type to a PMC
    """

def RegisterPMC2Py(is_pmc, pmc2py):
    """
    Register a conversion from a PMC type to a python type.
    \param is_pmc a function that checks for a PMC type match
    \param pmc2py a function to convert a PMC to a python type
    """

def Py2PMC(p):
    """
    Convert a python type to a PMC type.
    Look for a match in the registery.
    If the registered is_py returns true,
    call the registered py2pmc function.
    """

def PMC2Py(p):
    """
    Convert a PMC type to a python type.
    Look for a match in the registery.
    If the registered is_pmc returns true,
    call the registered pmc2py function.
    """

------------------------------------------------------------------------
-- Python support of numeric types
------------------------------------------------------------------------
Built-in python types do not support all variations of fixed-width numbers.
Basically python only supports int, long, double, and complex double.
Fortunately, numpy gives python support for all fixed-width numeric types.
When numpy is available, the PMC module supports the following:

* conversions for fixed width integer types (8, 16, 32, int/uint)
* conversions for floating point types (32 and 64)
* conversions for floating point complex types (64 and 128)

In addition, all std::vector of these numeric types convert to numpy arrays.
The numpy arrays will actually reference the memory held in the std::vector.

------------------------------------------------------------------------
-- Python container support
------------------------------------------------------------------------
To support built-in python container types: set, tuple, list, dict.
These types have typedef'd C++ equivalents in <PMC/Containers.hpp>.
The PMC module comes with conversions for all these container types.
These types are recommended for C++ users interfacing with python.
