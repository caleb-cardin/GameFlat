#pragma once



#include "menu.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <cstdio>
#include <cmath>

namespace gfui {

	struct GFColor4f {
		float x, y, z, w;
	};

	inline void gfui_normalize_color(GFColor4f& color) {
		color.x /= color.w;
		color.y /= color.w;
		color.z /= color.w;
		color.w /= color.w;
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void resize_callback(GLFWwindow* window, int x, int y);

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

		int width = 1600;
		int height = 900;

		
	};

	

} //namespace gfui