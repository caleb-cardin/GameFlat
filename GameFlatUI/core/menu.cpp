#include "menu.h"

namespace gfui {

	std::string g_CurrentUserName{"Rancid"};

	void gfui_FavoritesMenu(bool* show, int fav_height)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("FavoritesMenu", ImVec2(0, fav_height), true, window_flags);

		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Favorites"))
			{

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void gfui_SettingsMenu(bool* show, int sett_height)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("SettingsMenu", ImVec2(0, sett_height), true, window_flags);

		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Settings"))
			{

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void gfui_AccountMenu(bool* show, int acct_height)
	{

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("AccountMenu", ImVec2(0, acct_height), true, window_flags);
		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Account"))
			{
				
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();

			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.f);
			
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(150, 10));

			const char* name = gfui::g_CurrentUserName.c_str();
			ImGui::Text("Logged in as : %s ", name);

			if (g_CurrentUserName == "Guest")
			{
				if (ImGui::Button("Sign Up"))
					ImGui::OpenPopup("Sign Up");

				if (ImGui::BeginPopupModal("Sign Up", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{

					static char name_buffer[256] = "";
					static char pass_buffer[256] = "";

					ImGui::InputText("Username", name_buffer, IM_ARRAYSIZE(name_buffer));

					ImGui::InputText("Password", pass_buffer, IM_ARRAYSIZE(pass_buffer), ImGuiInputTextFlags_Password);
					bool signup_success = false;
					if (ImGui::Button("Sign Up", ImVec2(120, 0)))
					{

						ImGui::OpenPopup("Signup Status");
						// Make request to sever
						std::string response = signupRequest(std::string(name_buffer), std::string(pass_buffer));

						if (response == "SUCCESS")
						{
							ImGui::BeginPopupModal("Signup Status");
							ImGui::Text("Signup successful!");
							if (ImGui::Button("OK", ImVec2(120, 0)))
							{
								signup_success = true;

								ImGui::CloseCurrentPopup();
							}
							gfui::g_CurrentUserName = name_buffer;
						}
						else
						{
							ImGui::BeginPopupModal("Signup Status");
							ImGui::Text("Signup successful!");
							if (ImGui::Button("OK", ImVec2(120, 0)))
							{
								ImGui::CloseCurrentPopup();
							}

						}
						ImGui::EndPopup();
					}

					ImGui::SetItemDefaultFocus();
					ImGui::SameLine();

					if (ImGui::Button("Cancel", ImVec2(120, 0)) || signup_success)
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("Login"))
					ImGui::OpenPopup("Login Screen");

				if (ImGui::BeginPopupModal("Login Screen", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					static char name_buffer[256] = "";
					static char pass_buffer[256] = "";

					ImGui::InputText("Username", name_buffer, IM_ARRAYSIZE(name_buffer));

					ImGui::InputText("Password", pass_buffer, IM_ARRAYSIZE(pass_buffer), ImGuiInputTextFlags_Password);
					bool login_success = false;
					if (ImGui::Button("Login", ImVec2(120, 0)))
					{

						ImGui::OpenPopup("Login Status");
						// Make request to sever
						std::string response = loginRequest(std::string(name_buffer), std::string(pass_buffer));

						if (response == "SUCCESS")
						{
							ImGui::BeginPopupModal("Login Status");
							ImGui::Text("Login successful!");
							if (ImGui::Button("OK", ImVec2(120, 0)))
							{
								login_success = true;

								ImGui::CloseCurrentPopup();
							}
							gfui::g_CurrentUserName = name_buffer;
						}
						else
						{
							ImGui::BeginPopupModal("Login Status");
							ImGui::Text("Login failed!");
							if (ImGui::Button("Back", ImVec2(120, 0)))
							{
								ImGui::CloseCurrentPopup();
							}
							

						}
						ImGui::EndPopup();
					}
					ImGui::SetItemDefaultFocus();
					ImGui::SameLine();

					if (ImGui::Button("Cancel", ImVec2(120, 0)) || login_success)
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}
			else
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
				const char* bio = "Software Developer";

				// Display user picture to the left
				ImGui::Image(nullptr, ImVec2(60, 60));
				ImGui::SameLine();
				ImGui::BeginChild("Profile");
				ImGui::Text("Username: %s", gfui::g_CurrentUserName.c_str());
				ImGui::Text("Bio: %s", bio);
				

				if (ImGui::Button("Logout"))
					ImGui::OpenPopup("Logout");
				
				bool open_logout = true;
				if (ImGui::BeginPopupModal("Logout", &open_logout, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Are you sure you want to log out?");
					if (ImGui::Button("Yes", ImVec2(120, 0)))
					{
						g_CurrentUserName = "Guest";
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0)))
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				ImGui::EndChild();
				ImGui::PopStyleVar();
				
			}

			ImGui::PopStyleVar();

			ImGui::PopStyleVar();
		}
		ImGui::EndChild();

		ImGui::PopStyleVar();
	}

	void gfui_MainMenu(int width, int height)
	{
		bool main_open = true;

		int main_width = width / 4;
		const int minimum_main_width = 200;
		if (main_width < minimum_main_width)
			main_width = minimum_main_width;

		int account_height = height / 6;
		int fav_height = height / 2;
		int sett_height = height - account_height - fav_height - 25;


		ImGui::BeginGroup();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(main_width, height));
		ImGui::Begin("Main Menu", &main_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		static bool disable_menu = false;

		gfui_AccountMenu(&disable_menu, account_height);
		gfui_FavoritesMenu(&disable_menu, fav_height);
		gfui_SettingsMenu(&disable_menu, sett_height);
		

		ImGui::End();

		ImGui::EndGroup();
	}



} //namespace gfui