# CMakeList.txt : CMake project for GameFlat, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GameFlatUI "GameFlatUI.cpp" 
				"GameFlatUI.h" 
                "core/menu.h" 
                "core/menu.cpp"
				"core/window.cpp" 
				"core/window.h" 
				"lib/glad/src/gl.c"
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib)
target_link_libraries(GameFlatUI PRIVATE cpr::cpr OpenGL::GL "glfw" "imgui" )
target_include_directories(GameFlatUI PUBLIC "./lib/imgui" "./lib/glad/include/")



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameFlatUI PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
