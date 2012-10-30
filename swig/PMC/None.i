/***********************************************************************
 * Support for the Python None / null PMC type
 **********************************************************************/

%include <PMC/PMC.i>

%inline %{
 
bool pmc_is_none(const PMCC &p)
{
    return not p;
}

static PMCC pmc_make_none(void)
{
    return PMCC();
};

%}
 
%pythoncode %{

RegisterPy2PMC(
    is_py = lambda x: x is None,
    py2pmc = lambda x: pmc_make_none(),
)

RegisterPMC2Py(
    is_pmc = pmc_is_none,
    pmc2py = lambda x: None,
)

%}
