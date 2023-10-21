# CMakeList.txt : CMake project for GameFlat, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GameFlatUI "GameFlatUI.cpp" 
				"GameFlatUI.h" 
				"core/window.cpp" 
				"core/window.h" 
				"lib/glad/src/gl.c"
)

target_link_libraries(GameFlatUI PRIVATE cpr::cpr OpenGL::GL "glfw" "imgui" )
target_include_directories(GameFlatUI PUBLIC "./lib/imgui" "./lib/glad/include/")


set(IMGUI_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/imgui)
file(GLOB IMGUI_GLOB
    ${IMGUI_PATH}/imgui.h
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imconfig.h
    ${IMGUI_PATH}/imgui_demo.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_internal.h
    ${IMGUI_PATH}/imstb_rectpack.h
    ${IMGUI_PATH}/imstb_textedit.h
    ${IMGUI_PATH}/imstb_truetype.h
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp

    # specific bindings...
    ${IMGUI_PATH}/backends/imgui_impl_glfw.h
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
    ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)
add_library("imgui" STATIC ${IMGUI_GLOB})
target_include_directories("imgui" PUBLIC ${IMGUI_PATH})
target_link_libraries("imgui" PRIVATE glfw)

target_link_libraries(GameFlatUI PUBLIC "imgui")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameFlatUI PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
