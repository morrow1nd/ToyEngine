# Example/Empty

INCLUDE_DIRECTORIES(
    ${TOY_ENGINE_INCLUDE_PATHS}
)
add_executable(ToyEngine_Example_Rendering
	"Main.cpp"
)
TARGET_LINK_LIBRARIES(ToyEngine_Example_Rendering
	${TOY_ENGINE_LIBRARIES}
)

# IDE specific
set_property(TARGET ToyEngine_Example_Rendering PROPERTY FOLDER Example)