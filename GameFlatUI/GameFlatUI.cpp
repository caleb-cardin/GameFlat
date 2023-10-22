// GameFlat.cpp : Defines the entry point for the application.
//

#include "GameFlatUI.h"




int main()
{
	gfui::GFNetworkPipe net{};
	net.init();

	gfui::GFWindow test{};
	test.init();
	test.run();
	test.shutdown();
}
