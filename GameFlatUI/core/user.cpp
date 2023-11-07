#include "user.h"

namespace gfui {

	User::User(const std::string& username) : m_Username(username)
	{
		int x, y, n;
		m_Img = stbi_load("C:/Users/cabo_/Pictures/Camera Roll/1666905512295.jpeg", &x, &y, &n, 0);
	}

	User::User(std::string&& username) : m_Username(std::move(username))
	{
		int x, y, n;
		m_Img = stbi_load("C:/Users/cabo_/Pictures/Camera Roll/1666905512295.jpeg", &x, &y, &n, 0);
	}

}