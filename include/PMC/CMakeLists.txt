########################################################################
# install include files
########################################################################
install(FILES
    Config.hpp
    PMC.hpp
    DESTINATION include/PMC
    COMPONENT ${PMC_COMP_DEVEL}
)

install(FILES
    Detail/PMCImpl.hpp
    DESTINATION include/PMC/Detail
    COMPONENT ${PMC_COMP_DEVEL}
)
