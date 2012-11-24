########################################################################
# install include files
########################################################################
install(FILES
    Config.hpp
    PMC.hpp
    PMC.i
    Containers.hpp
    DESTINATION include/PMC
    COMPONENT ${PMC_COMP_DEVEL}
)

install(FILES
    Detail/PMCImpl.hpp
    DESTINATION include/PMC/Detail
    COMPONENT ${PMC_COMP_DEVEL}
)
