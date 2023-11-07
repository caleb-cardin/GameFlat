#pragma once

#include "stb_image.h"
#include <string>

namespace gfui {

	class User {
	public:
		User() = default;
		User(const std::string& username);
		User(std::string&& username);
		~User() = default;


		inline stbi_uc* get_Profile_Image() { return m_Img; }
		inline std::string get_Username() { return m_Username; }
		inline void set_Username(std::string&& s) { m_Username = s; }


		inline void safe_exit() { stbi_image_free(m_Img); }

	private:
		std::string m_Username = "Guest";
		
		stbi_uc* m_Img = nullptr;
		
	};

}