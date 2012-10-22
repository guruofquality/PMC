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

RegisterType(
    is_py = lambda x: x is None,
    is_pmc = pmc_is_none,
    pmc2py = lambda x: None,
    py2pmc = lambda x: pmc_make_none(),
)

%}
