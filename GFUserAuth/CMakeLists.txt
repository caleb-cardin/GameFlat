

add_executable(GFUserAuth "GFUserAuth.cpp" "GFUserAuth.h")

target_link_libraries(GFUserAuth PRIVATE cpr::cpr)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameFlatUI PROPERTY CXX_STANDARD 20)
endif()

