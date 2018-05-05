# Example/Empty

INCLUDE_DIRECTORIES(
    ${TOY_ENGINE_INCLUDE_PATHS}
)
add_executable(ToyEngine_Example_Empty
	"Main.cpp"
)
TARGET_LINK_LIBRARIES(ToyEngine_Example_Empty
	${TOY_ENGINE_LIBRARIES}
)

# IDE specific
set_property(TARGET ToyEngine_Example_Empty PROPERTY FOLDER Example)