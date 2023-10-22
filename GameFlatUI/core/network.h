#pragma once

#include <iostream>
#include "cpr/cpr.h"


namespace gfui {

	std::string signupRequest(std::string username, std::string password);
	std::string loginRequest(std::string username, std::string password);

} // namespace gfui 