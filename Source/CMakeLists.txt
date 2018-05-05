# 
# ToyEngine/Source
# 

## CMake Options

### Runtime Check
option(OPTION_TOY_ENGINE_MORE_RUNTIME_CHECK
    "Open more ToyEngine runtime checking" ON)
if(OPTION_TOY_ENGINE_MORE_RUNTIME_CHECK)
    set(TOY_ENGINE_MORE_RUNTIME_CHECK "1")
else()
    set(TOY_ENGINE_MORE_RUNTIME_CHECK "0")
endif()

## end of CMake Options


## Third Party Libs
#ADD_SUBDIRECTORY(ThirdParty)


## Configure file
CONFIGURE_FILE(
    "${TOY_ENGINE_SOURCE_DIR}/ToyEngineConfig.h.in"
    "${PROJECT_BINARY_DIR}/ToyEngineConfig.h"
    )

ADD_SUBDIRECTORY(TRL)
INCLUDE_DIRECTORIES(${TRL_INCLUDE_PATHS})

# Source files and their filters
INCLUDE(CMakeSources.cmake)


INCLUDE_DIRECTORIES(
    ${TOY_ENGINE_INCLUDE_DIR}
    ${PROJECT_BINARY_DIR}
)

ADD_LIBRARY(ToyEngine
    ${TOY_ENGINE_SRC}
    ToyEngineConfig.h.in
)
TARGET_LINK_LIBRARIES(ToyEngine
	${TRL_LIBRARIES}
)


# IDE specific
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS TRUE)
SET_PROPERTY(TARGET ToyEngine PROPERTY FOLDER Layers)

# For lib user
SET(TOY_ENGINE_INCLUDE_PATHS
	${TRL_INCLUDE_PATHS}
    ${TOY_ENGINE_INCLUDE_DIR}
    ${PROJECT_BINARY_DIR}
    CACHE INTERNAL "Toy Engine INCLUDE PATHS"
)

SET(TOY_ENGINE_LIBRARIES
	ToyEngine
	${TRL_LIBRARIES}
    CACHE INTERNAL "Toy Engine Librarys"
)