#import pmc_swig
from PMC import *

#print dir(pmc_swig)
#print pmc_swig.registry

#print dir(pmc_swig.PMCDict())

#d = pmc_swig.PMCDict()
#d[pmc_swig.PMC()] = pmc_swig.PMC()

#print pmc_swig.from_dict({'foo': 'bar'})

#x_none = Py2PMC(None)

#y_none = PMC2Py(x_none)

#print x_none
#print pmc_is_none(x_none)
#print y_none

d = {None:None}
print Py2PMC(d)
print PMC2Py(Py2PMC(d))
