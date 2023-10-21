#pragma once



#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <cstdio>
namespace gfui {

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void glfw_error_callback(int error, const char* description);

	class GFWindow {
	public:
		GFWindow() {}
		~GFWindow() = default;

		void init();
		void shutdown();

		void run();

		

	private:
		GLFWwindow* mainWindow = nullptr;

		int width = 640;
		int height = 480;
		bool show_demo_window = true;
	};

	

} //namespace gfui