#pragma once


#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <string>
#include <iostream>

#include "network.h"

namespace gfui {

	void gfui_AccountMenu(bool* show, int acct_height);
	void gfui_MainMenu(int width, int height);
	void gfui_FavoritesMenu(bool* show, int fav_height);
	void gfui_SettingsMenu(bool* show, int sett_height);

} //namespace gfui