#include "window.h"



namespace gfui {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	}

	void resize_callback(GLFWwindow* window, int x, int y)
	{
		fprintf(stdout, "Winodw resized %d, %d\n", x, y);
	}

	void GFWindow::init()
	{
		// Window setup
		glfwSetErrorCallback(gfui::glfw_error_callback);
		if (!glfwInit())
		{
			// error
		}
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

		mainWindow = glfwCreateWindow(width, height, "GameFlatUI", NULL, NULL);
		if (!mainWindow)
		{
			// Window or OpenGL context creation failed
		}

		// Make Gl current context
		glfwMakeContextCurrent(mainWindow);
		int version = gladLoadGL(glfwGetProcAddress);
		if (version == 0) {
			printf("Failed to initialize OpenGL context\n");
		}
		glfwSwapInterval(1);

		glfwSetKeyCallback(mainWindow, key_callback);

		const char* glsl_version = "#version 460";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		// UI setup

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init(glsl_version);


	}

	void GFWindow::shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(mainWindow);

		glfwTerminate();
	}

	void GFWindow::run()
	{
		GFColor4f bgColor = { 0.3f, 0.3f, 0.3f, 1.0 };

		while (!glfwWindowShouldClose(mainWindow))
		{
			glfwGetWindowSize(mainWindow, &width, &height);

			// float ratio;
			// 
			// ratio = width / (float)height;
			// 
			// double time = glfwGetTime();
			

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			
			
			// Main Menu

			gfui_MainMenu(width, height);

			ImGui::Render();

			int width, height;
			glfwGetFramebufferSize(mainWindow, &width, &height);
			glViewport(0, 0, width, height);
			glClearColor(bgColor.x, bgColor.y, bgColor.z, bgColor.w);

			glClear(GL_COLOR_BUFFER_BIT);


			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(mainWindow);
			glfwPollEvents();
		}

	}














} //namespace gfui