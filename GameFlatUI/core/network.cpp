#include "network.h"

namespace gfui {


	void GFNetworkPipe::init()
	{
		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1984/signup" }, cpr::Payload({ { "username", "password" }, { "other", "nice" } }));
		std::cout << r.text << std::endl;
	}

	void GFNetworkPipe::run()
	{

	}


} // namespace gfui 