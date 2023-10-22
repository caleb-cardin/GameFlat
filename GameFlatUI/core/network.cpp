#include "network.h"

namespace gfui {


	void GFNetworkPipe::init()
	{
		cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:1984/resource" }, cpr::Payload({ { "username", "password" } }));
		std::cout << r.text << std::endl;
	}

	void GFNetworkPipe::run()
	{

	}


} // namespace gfui 