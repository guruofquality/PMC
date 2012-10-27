########################################################################
## Polymorphic container for C++ with optional python bindings
########################################################################

PMC is just another simple polymorphic container class for C++.
The goal is that any C++ object can be held inside of a PMC.
Then, the polymorphic container can be passed around as type PMC.
And finally, the object can be casted out of the PMC container.

-------------------------------
-- Some notable attributes
-------------------------------

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

-------------------------------
-- Quick c++ code snippet
-------------------------------

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
