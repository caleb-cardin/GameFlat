# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("GameFlat")



find_package(cpr REQUIRED)

find_package(unofficial-restbed CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Include sub-projects.

add_subdirectory ("GameFlatUI/lib/glfw")

add_subdirectory ("GameFlatUI")

add_subdirectory("GFUserAuth")
