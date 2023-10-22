

add_executable(GFUserAuth 
				"GFUserAuth.cpp" 
				"GFUserAuth.h" 
				"core/server.cpp" 
				"core/server.h")

target_link_libraries(GFUserAuth PRIVATE unofficial::restbed::restbed)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GFUserAuth PROPERTY CXX_STANDARD 20)
endif()

