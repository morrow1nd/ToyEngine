SET(TOY_ENGINE_INC_SCENE
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/ComponentBase.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/ComponentManagerHelper.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/IComponent.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/IComponentManager.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Scene.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/SceneManager.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/SceneObject.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/SceneObjectManager.h"
)
set(TOY_ENGINE_INC_SCENE_COMPONENTS
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Components/CBlocks.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Components/CBlocksRender.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Components/CCamera.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Components/CLight.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Components/CMeshFilter.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Components/CMeshRenderer.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Scene/Components/CTransform.h"
)

set(TOY_ENGINE_SRC_SCENE
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/SceneManager.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/ComponentManagerHelper.cpp"
)
set(TOY_ENGINE_SRC_SCENE_COMPONENTS
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/Components/CBlocks.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/Components/CBlocksRender.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/Components/CTransform.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/Components/CMeshFilter.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/Components/CMeshRenderer.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Scene/Components/CCamera.cpp"
)

SET(TOY_ENGINE_INC_GRAPHICS
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Graphics/Material.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Graphics/Shader.h"
	"${TOY_ENGINE_INCLUDE_DIR}/ToyEngine/Graphics/Texture2D.h"
)

set(TOY_ENGINE_SRC_GRAPHICS
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Graphics/Material.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Graphics/Shader.cpp"
	"${TOY_ENGINE_SOURCE_DIR}/ToyEngine/Graphics/Texture2D.cpp"
)


# if(MSVC)
#   list(APPEND BS_BANSHEECORE_INC_PLATFORM VSVisualizations.natvis)
# endif()

# if(WIN32)
#   list(APPEND BS_BANSHEECORE_INC_PLATFORM ${BS_BANSHEECORE_INC_PLATFORM_WIN32})
#   list(APPEND BS_BANSHEECORE_SRC_PLATFORM ${BS_BANSHEECORE_SRC_PLATFORM_WIN32})
# elseif(LINUX)
#   list(APPEND BS_BANSHEECORE_INC_PLATFORM ${BS_BANSHEECORE_INC_PLATFORM_LINUX})
#   list(APPEND BS_BANSHEECORE_SRC_PLATFORM ${BS_BANSHEECORE_SRC_PLATFORM_LINUX})
# elseif(APPLE)
#   list(APPEND BS_BANSHEECORE_INC_PLATFORM ${BS_BANSHEECORE_INC_PLATFORM_MACOS})
#   list(APPEND BS_BANSHEECORE_SRC_PLATFORM ${BS_BANSHEECORE_SRC_PLATFORM_MACOS})
# endif()

source_group("CMake"									FILES "${TOY_ENGINE_SOURCE_DIR}/../CMakeLists.txt")
source_group("CMake\\Example"							FILES "${TOY_ENGINE_SOURCE_DIR}/../Example/CMakeLists.txt")
source_group("CMake\\Source"                            FILES "CMakeSources.cmake" "CMakeLists.txt")
source_group("CMake\\Source\\ThirdParty"				FILES "${TOY_ENGINE_SOURCE_DIR}/ThirdParty/CMakeLists.txt")

source_group("Header Files\\Scene"						FILES ${TOY_ENGINE_INC_SCENE})
source_group("Source Files\\Scene"						FILES ${TOY_ENGINE_SRC_SCENE})
source_group("Header Files\\Scene\\Components"			FILES ${TOY_ENGINE_INC_SCENE_COMPONENTS})
source_group("Source Files\\Scene\\Components"			FILES ${TOY_ENGINE_SRC_SCENE_COMPONENTS})
source_group("Header Files\\Graphics"					FILES ${TOY_ENGINE_INC_GRAPHICS})
source_group("Source Files\\Graphics"					FILES ${TOY_ENGINE_SRC_GRAPHICS})


set(TOY_ENGINE_SRC
	"${TOY_ENGINE_SOURCE_DIR}/../CMakeLists.txt"
	"${TOY_ENGINE_SOURCE_DIR}/../Example/CMakeLists.txt"
    "CMakeSources.cmake" "CMakeLists.txt"
	"${TOY_ENGINE_SOURCE_DIR}/ThirdParty/CMakeLists.txt"
	${TOY_ENGINE_INC_SCENE}
	${TOY_ENGINE_SRC_SCENE}
	${TOY_ENGINE_INC_SCENE_COMPONENTS}
	${TOY_ENGINE_SRC_SCENE_COMPONENTS}
	${TOY_ENGINE_INC_GRAPHICS}
	${TOY_ENGINE_SRC_GRAPHICS}
)
