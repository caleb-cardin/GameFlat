#include "network.h"

namespace gfui {


	std::string signupRequest(std::string username, std::string password)
	{
		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1984/signup" }, cpr::Payload({ { "username", username }, { "password", password } }));
		return r.text;
	}

	std::string loginRequest(std::string username, std::string password)
	{
		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1984/login" }, cpr::Payload({ { "username", username }, { "password", password } }));
		return r.text;
	}


} // namespace gfui 