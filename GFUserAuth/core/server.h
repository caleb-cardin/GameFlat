#pragma once

#include <iostream>
#include <memory>
#include <cstdlib>

#include <restbed>


namespace gfuser {

	class GFUserServer {
	public:
		GFUserServer() {}
		~GFUserServer() = default;

		void init();
		void run();
		void shutdown();

	private:
		bool isRunning = true;
		
	};

} // namespace gfuser