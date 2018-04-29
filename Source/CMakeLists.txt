# 
# ToyEngine/Source
# 

## CMake Options

# ### RenderAPI to use
# set(TRL_DX11         "(1 << 0)")
# set(TRL_OPENGL       "(1 << 1)")
# set(TRL_OPENGLES     "(1 << 2)")

# set(OPTION_TRL_RENDER_API "OpenGL" CACHE STRING "Render API to use.")
# set_property(CACHE OPTION_TRL_RENDER_API PROPERTY STRINGS "OpenGL" "DirectX 11" "OpenGL ES")

# if(OPTION_TRL_RENDER_API MATCHES "DirectX 11")
#     set(TRL_USING_DX11 TRUE)
#     set(TRL_RENDER_API ${TRL_DX11})
# elseif(OPTION_TRL_RENDER_API MATCHES "OpenGL")
#     set(TRL_USING_OPENGL TRUE)
#     set(TRL_RENDER_API ${TRL_OPENGL})
# else()
#     set(TRL_USING_OPENGLES TRUE)
#     set(TRL_RENDER_API ${TRL_OPENGLES})
# endif()

# ## end of CMake Options

## Third Party Libs
# ADD_SUBDIRECTORY(ThirdParty)


## Configure file
CONFIGURE_FILE(
    "${TOY_ENGINE_SOURCE_DIR}/ToyEngineConfig.h.in"
    "${PROJECT_BINARY_DIR}/ToyEngineConfig.h"
    )

ADD_SUBDIRECTORY(TRL)
INCLUDE_DIRECTORIES(${TRL_INCLUDE_PATHS})

# # Source files and their filters
# INCLUDE(CMakeSources.cmake)


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