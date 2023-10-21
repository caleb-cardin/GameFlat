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

	void GFWindow::init()
	{
		// Window setup
		glfwSetErrorCallback(gfui::glfw_error_callback);
		if (!glfwInit())
		{
			// error
		}

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

		//glfwSetKeyCallback(mainWindow, key_callback);



		const char* glsl_version = "#version 330";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

		while (!glfwWindowShouldClose(mainWindow))
		{
			glfwPollEvents();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::ShowDemoWindow(&show_demo_window);

			// float ratio;
			// 
			// ratio = width / (float)height;
			// 
			// double time = glfwGetTime();



		



			ImGui::Render();

			int width, height;
			glfwGetFramebufferSize(mainWindow, &width, &height);
			glViewport(0, 0, width, height);
			glClearColor(1, 0, 0, 1);

			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(mainWindow);
		}

	}














} //namespace gfui