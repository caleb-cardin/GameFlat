#pragma once

#include <iostream>
#include "cpr/cpr.h"
#include "sha256.h"

namespace gfui {

	std::string debugRequest(std::string message);
	std::string signupRequest(std::string username, std::string password);
	std::string loginRequest(std::string username, std::string password);
	std::string notificationRequest();

} // namespace gfui 