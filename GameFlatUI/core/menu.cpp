#include "menu.h"

namespace gfui {


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


			ImGui::Text("Logged in as : Guest");

			if (ImGui::Button("Sign Up"))
				ImGui::OpenPopup("Sign Up");

			if (ImGui::BeginPopupModal("Sign Up", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				
				char buffer[30] = { "\0" };
				ImGui::InputTextWithHint("Username", "Enter Username", buffer, 30);

				if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
				ImGui::SetItemDefaultFocus();
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
				ImGui::EndPopup();
			}

			ImGui::SameLine();

			ImGui::Button("Login");

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
		const int minimum_account_height = 150;
		if (account_height < minimum_account_height)
			account_height = minimum_account_height;

		ImGui::BeginGroup();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(main_width, height));
		ImGui::Begin("Main Menu", &main_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		static bool disable_menu = false;

		gfui_AccountMenu(&disable_menu, account_height);


		ImGui::End();

		ImGui::EndGroup();
	}

	

	void gfui_FavoritesMenu()
	{

	}

	void gfui_SettingsMenu()
	{

	}

} //namespace gfui