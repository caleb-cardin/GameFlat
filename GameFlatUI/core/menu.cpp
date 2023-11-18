#include "menu.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gfui {

	User g_CurrentUser{};
	std::vector<std::string> globalNotificationStrings;

	void gfui_FavoritesMenu(bool* show, int height)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("FavoritesMenu", ImVec2(0, height), true, window_flags);

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

	void gfui_SettingsMenu(bool* show, int height)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("SettingsMenu", ImVec2(0, height), true, window_flags);

		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Settings"))
			{

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (ImGui::Button("Account Settings"))
		{
			ImGui::OpenPopup("WIP");
		}
		if (ImGui::Button("App Settings"))
		{
			ImGui::OpenPopup("WIP");
		}
		
		if (ImGui::BeginPopupModal("WIP", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("This feature is not yet implemented!");

			if (ImGui::Button("OK", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void gfui_AccountMenu(bool* show, int height)
	{

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("AccountMenu", ImVec2(0, height), true, window_flags);
		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Account"))
			{
				
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();

			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.f);
			
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(150, 10));

			ImGui::Text("Logged in as : %s ", gfui::g_CurrentUser.get_Username().c_str());

			
			bool login_from_signup = true;
			if (gfui::g_CurrentUser.get_Username() == "Guest")
			{
				if (ImGui::Button("Sign Up"))
					ImGui::OpenPopup("Sign Up");

				if (ImGui::BeginPopupModal("Sign Up", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					static char name_buffer[256] = "";
					static char pass_buffer[256] = "";
					static bool hide_pass = true;

					ImGui::InputText("Username", name_buffer, IM_ARRAYSIZE(name_buffer));
					ImGui::InputText("Password", pass_buffer, IM_ARRAYSIZE(pass_buffer), hide_pass ? ImGuiInputTextFlags_Password : ImGuiInputTextFlags_None);
					ImGui::SameLine();
					ImGui::Checkbox("Hide", &hide_pass);


					ImGui::Checkbox("Log in on success", &login_from_signup);

					static std::string signup_response{};

					bool signup_success = false;
					if (ImGui::Button("Sign Up", ImVec2(120, 0)))
					{
						signup_response = signupRequest(std::string(name_buffer), std::string(pass_buffer));
						ImGui::OpenPopup("Sign Up Status");
						if (signup_response == "SUCCESS")
						{
							signup_success = true;
							if (login_from_signup)
							{
								auto login_response = loginRequest(std::string(name_buffer), std::string(pass_buffer));
								// Make request to sever
								if (login_response == "SUCCESS")
								{
									gfui::g_CurrentUser.set_Username(std::string(name_buffer));
								}
							}
						}
						else
						{

						}
					}

					if (ImGui::BeginPopupModal("Sign Up Status", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(signup_response.c_str());

						if (ImGui::Button("OK", ImVec2(120, 0)))
						{
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndPopup();
					}

					ImGui::SetItemDefaultFocus();
					ImGui::SameLine();

					if (ImGui::Button("Cancel", ImVec2(120, 0)) || signup_success)
					{
						name_buffer;
						pass_buffer;
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
					
					static std::string login_response{};
					
					bool login_success = false;
					if (ImGui::Button("Login", ImVec2(120, 0)))
					{
						ImGui::OpenPopup("Login Status");
						login_response = loginRequest(std::string(name_buffer), std::string(pass_buffer));
						// Make request to sever
						if (login_response == "SUCCESS")
						{
							login_success = true;
							gfui::g_CurrentUser.set_Username(std::string(name_buffer));
						}
					}

					if (ImGui::BeginPopupModal("Login Status", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(login_response.c_str());

						if (ImGui::Button("OK", ImVec2(120, 0)))
						{
							ImGui::CloseCurrentPopup();
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
				ImGui::Image(g_CurrentUser.get_Profile_Image(), ImVec2(60, 60));
				ImGui::SameLine();
				ImGui::BeginChild("Profile");
				ImGui::Text("Username: %s", gfui::g_CurrentUser.get_Username().c_str());
				ImGui::Text("Bio: %s", bio);
				

				ImGui::PopStyleVar();

				if (ImGui::Button("Edit"))
					ImGui::OpenPopup("Edit");

				bool open_edit = true;
				bool open_edit_confirm = true;
				if (ImGui::BeginPopupModal("Edit", &open_edit, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Edit Profile: COMING SOON!");
					if (ImGui::Button("Cancel", ImVec2(120, 0)))
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button("Confirm", ImVec2(120, 0)))
					{
						ImGui::OpenPopup("Confirm Edit");
					}
					if (ImGui::BeginPopupModal("Confirm Edit", &open_edit_confirm, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text("Are you sure you want edit");
						if (ImGui::Button("Yes", ImVec2(120, 0)))
						{
							ImGui::CloseCurrentPopup();
							open_edit = false;
						}
						ImGui::SameLine();
						if (ImGui::Button("Cancel", ImVec2(120, 0)))
						{
							ImGui::CloseCurrentPopup();
						}

						ImGui::EndPopup();

					}


					ImGui::EndPopup();
				}

				if (ImGui::Button("Logout"))
					ImGui::OpenPopup("Logout");

				bool open_logout = true;
				if (ImGui::BeginPopupModal("Logout", &open_logout, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Are you sure you want to log out?");
					if (ImGui::Button("Yes", ImVec2(120, 0)))
					{
						gfui::g_CurrentUser.set_Username("Guest");
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
		
			}

			ImGui::PopStyleVar();

			ImGui::PopStyleVar();
		}
		ImGui::EndChild();

		ImGui::PopStyleVar();
	}

	void gfui_GamesMenu(bool* show, int height)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		
		ImGui::BeginChild("GamesMenu", ImVec2(0, height), true, window_flags);

		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Games"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		auto games_list = { "Game1", "Game2", "Game3", "Game4" };

		const int padding = 10;
		
		
		
		auto column_Counter = int(0);
		for (auto game : games_list)
		{
			if (column_Counter % 2 == 1)
			{
				ImGui::SameLine();
			}
			ImGui::BeginChild(game, ImVec2((height / 2) - padding, (height / 2) - padding), true, window_flags);

			if (show && ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu(game))
				{
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			// Game stuff here

			ImGui::EndChild();
			column_Counter++;
		}

		ImGui::EndChild();
		
	}

	void gfui_FriendsMenu(bool* show, int height)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("FriendsMenu", ImVec2(0, height), true, window_flags);

		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Friends"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::TextColored(ImVec4(.6f, .7f, .7f, 1), g_CurrentUser.get_Username() == "Guest" ? "Please log in to access friends list!" : "Friends list coming soon!");

		ImGui::EndChild();
		ImGui::PopStyleVar();
	}
	

	void _splitAndStoreNotifs(const std::string& inputString)
	{
		std::istringstream ss(inputString);
		std::string token;

		// Clear the existing contents of the global vector

		while (std::getline(ss, token, '%')) {
			// Skip empty tokens
			if (!token.empty()) {
				// Store non-empty tokens in the global vector
				globalNotificationStrings.push_back(token);
			}
		}
	}

	void gfui_NotifsMenu(bool* show, int height)
	{
		
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (show)
			window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::BeginChild("NotificationMenu", ImVec2(0, height), true, window_flags);

		if (show && ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Notifications"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		bool show_notifs = false;
		if (g_CurrentUser.get_Username() != "Guest")
			show_notifs = true;

		ImGui::TextColored(ImVec4(.6f, .7f, .7f, 1), show_notifs ? "Please log in to access notifications!" : "Notifications coming soon!");

		


		// INPUT NOTIFCATION LOGIC HERE
		if (show_notifs == true)
		{
			
		}
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

	void gfui_MainMenu(int width, int height)
	{
		bool main_open = true;

		int main_width = width / 5;


		int account_height = height / 5;
		int fav_height = 2 * height / 3;
		int sett_height = height - account_height - fav_height - 25;
		int fri_height = 2 * height / 5;
		int notif_height = height - fri_height - 25;

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

		ImGui::BeginGroup();
		ImGui::SetNextWindowPos(ImVec2(main_width, 0));
		ImGui::SetNextWindowSize(ImVec2(width - main_width * 2, height));
		ImGui::Begin("Game Menu", &main_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		gfui_GamesMenu(&disable_menu, height - 20);


		ImGui::End();

		ImGui::EndGroup();

		ImGui::BeginGroup();
		ImGui::SetNextWindowPos(ImVec2(width - main_width, 0));
		ImGui::SetNextWindowSize(ImVec2(main_width, height));
		ImGui::Begin("User Menu Left", &main_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		gfui_FriendsMenu(&disable_menu, fri_height);
		gfui_NotifsMenu(&disable_menu, notif_height);

		ImGui::End();

		ImGui::EndGroup();
	}



} //namespace gfui