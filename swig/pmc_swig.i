%module pmc_swig

%{

//#include <boost/intrusive_ptr.hpp>
#include <PMC/PMC.hpp>

%}

struct PMC// : boost::intrusive_ptr<void>
{

};

struct PMCC : PMC
{

};

%pythoncode %{

registry = list()

%}

//registering a PMC to Python
// - c++ is the PMC type <x>
// - python is the python type <x>
// - convert PMC to some type
// - convert type to a PMC

%define DECL_PMC_TYPE(type, name)
%inline %{

bool is_ ## name(const PMCC &p)
{
    return p.is_type<type>();
}

type to_ ## name(const PMCC &p)
{
    return p.cast<type>();
}

PMC from_ ## name(const type &p)
{
    return PMC::make(p);
}

%}

%pythoncode %{

registry.append((name, is_ ## name, to_ ## name, from_ ## name))

%}

%enddef

%include "std_map.i"

%inline %{
typedef std::map<PMCC, PMCC> PMCDict;
%}

%template (PMCDict) std::map<PMCC, PMCC>;

DECL_PMC_TYPE(PMCDict, dict)
