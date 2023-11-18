#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <algorithm>
#include <chrono>
#include <string>
#include <iostream>

#include "network.h"
#include "user.h"

namespace gfui {

	void gfui_AccountMenu(bool* show, int height);
	void gfui_MainMenu(int width, int height);
	void gfui_FavoritesMenu(bool* show, int height);
	void gfui_SettingsMenu(bool* show, int height);
	void gfui_GamesMenu(bool* show, int height);
	void gfui_FriendsMenu(bool* show, int height);
	void _splitAndStoreNotifs(const std::string& inputString);
	void gfui_NotifsMenu(bool* show, int height);

} //namespace gfui