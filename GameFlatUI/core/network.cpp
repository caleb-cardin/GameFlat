#include "network.h"

namespace gfui {

	std::string debugRequest(std::string message)
	{
		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1984/debug" }, cpr::Payload({ { "DEBUG_FROM_CLIENT:", message } }));
		return r.text;
	}

	std::string signupRequest(std::string username, std::string password)
	{
		SHA256 hasher {};
		hasher(password);
		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1984/signup" }, cpr::Payload({ { "username", username }, { "password", hasher.getHash() }}));
		return r.text;
	}

	std::string loginRequest(std::string username, std::string password)
	{
		SHA256 hasher{};
		hasher(password);
		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1984/login" }, cpr::Payload({ { "username", username }, { "password", hasher.getHash() } }));
		return r.text;
	}

	std::string notificationRequest()
	{
		auto currentTime = std::chrono::system_clock::now();
		auto timeString = std::chrono::system_clock::to_time_t(currentTime);

		std::stringstream ss;
		ss << std::put_time(gmtime(&timeString), "%Y-%m-%d %H:%M:%S");
		std::string formattedTime = ss.str();

		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1985/notifications" }, cpr::Payload({ { "user_last_check_time", formattedTime } }));
		return r.text;
	}

// // Use this function in another library to parse the above data >---------------------------------------------------------^^^^^^^^^^^^^^^^^^
// 
//		std::chrono::system_clock::time_point parseTime(const std::string& timeString)
//		{
//			std::tm tm = {};
//			std::istringstream ss(timeString);
//			ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
//
//			return std::chrono::system_clock::from_time_t(std::mktime(&tm));
//		}
//		

} // namespace gfui 