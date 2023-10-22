#include "server.h"


namespace gfuser {

	void GFUserServer::post_signup_handler(const std::shared_ptr< restbed::Session > session)
	{
		const auto request = session->get_request();

		int content_length = request->get_header("Content-Length", 0);

		session->fetch(content_length, [](const std::shared_ptr< restbed::Session > session, const restbed::Bytes& body)
			{
				
				fprintf(stdout, "%.*s\n", (int)body.size(), body.data());

				session->close(restbed::OK, "Hello, World!", { { "Content-Length", "13" } });
			});
	}

	void GFUserServer::init()
	{
		g_ClientReciever.reset( new restbed::Resource );
		g_ClientReciever->set_path("/signup");
		g_ClientReciever->set_method_handler("POST", post_signup_handler);

		g_Settings.reset(new restbed::Settings);
		g_Settings->set_port(1984);
		g_Settings->set_default_header("Connection", "close");

		g_Service.publish(g_ClientReciever);

		g_Service.set_logger(std::make_shared< CustomLogger >());
		g_Service.start(g_Settings);
	}

	void GFUserServer::run()
	{
		
		while (!isRunning)
		{
			




		}

	}

	void GFUserServer::shutdown()
	{

	}

	

} // namespace gfuser