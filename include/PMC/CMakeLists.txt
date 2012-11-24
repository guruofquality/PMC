########################################################################
# install include files
########################################################################
install(FILES
    Config.hpp
    PMC.hpp
    PMC.i
    Containers.hpp
    Pool.hpp
    DESTINATION include/PMC
    COMPONENT ${PMC_COMP_DEVEL}
)

install(FILES
    Detail/PMCImpl.hpp
    Detail/PoolImpl.hpp
    DESTINATION include/PMC/Detail
    COMPONENT ${PMC_COMP_DEVEL}
)
