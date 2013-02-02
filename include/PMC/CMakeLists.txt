########################################################################
# install include files
########################################################################
install(FILES
    Config.hpp
    PMC.hpp
    PMC.i
    Registry.i
    Containers.hpp
    Pool.hpp
    Serialize.hpp
    SerializeTypes.hpp
    DESTINATION include/PMC
    COMPONENT ${PMC_COMP_DEVEL}
)

install(FILES
    Detail/PMCImpl.hpp
    Detail/PoolImpl.hpp
    Detail/Serialize.hpp
    DESTINATION include/PMC/Detail
    COMPONENT ${PMC_COMP_DEVEL}
)
