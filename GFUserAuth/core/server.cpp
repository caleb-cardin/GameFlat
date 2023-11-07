#include "server.h"


namespace gfuser {

	std::map<std::string, std::string> GFUserServer::g_Users{};

	std::string urlDecode(const std::string& value) 
	{
		std::ostringstream decoded;
		for (size_t i = 0; i < value.length(); ++i) {
			if (value[i] == '%') {
				if (i + 2 < value.length()) {
					int hex;
					std::istringstream in(value.substr(i + 1, 2));
					in >> std::hex >> hex;
					decoded << static_cast<char>(hex);
					i += 2;
				}
			}
			else if (value[i] == '+') {
				decoded << ' ';
			}
			else {
				decoded << value[i];
			}
		}
		return decoded.str();
	}

	std::map<std::string, std::string> parseUrlEncoded(const std::string& data) 
	{
		std::map<std::string, std::string> result;

		std::istringstream iss(data);
		std::string pair;
		while (std::getline(iss, pair, '&')) {
			size_t equalsPos = pair.find('=');
			if (equalsPos != std::string::npos) {
				std::string key = pair.substr(0, equalsPos);
				std::string value = pair.substr(equalsPos + 1);
				result[urlDecode(key)] = urlDecode(value);
			}
		}

		return result;
	}

	void GFUserServer::post_signup_handler(const std::shared_ptr< restbed::Session > session)
	{
		const auto request = session->get_request();

		int content_length = request->get_header("Content-Length", 0);

		session->fetch(content_length, [](const std::shared_ptr< restbed::Session > session, const restbed::Bytes& body)
			{
				std::string urlEncodedData(body.begin(), body.end());
				std::map<std::string, std::string> formData = parseUrlEncoded(urlEncodedData);

				auto incoming_username = formData["username"];
				auto incoming_password = formData["password"];
				if (g_Users.find(incoming_username) == g_Users.end())
				{
					GFUserServer::g_Users[incoming_username] = incoming_password;
					session->close(restbed::OK, "SUCCESS", { {"Content-Length", "8"} });
				}
				else
				{
					session->close(restbed::OK, "ERROR: Username Exists!", { {"Content-Length", "24"} });
				}
			
			}
		);
	}

	void GFUserServer::post_login_handler(const std::shared_ptr< restbed::Session > session)
	{
		const auto request = session->get_request();

		int content_length = request->get_header("Content-Length", 0);

		session->fetch(content_length, [](const std::shared_ptr< restbed::Session > session, const restbed::Bytes& body)
			{
				std::string urlEncodedData(body.begin(), body.end());
				std::map<std::string, std::string> formData = parseUrlEncoded(urlEncodedData);

				auto incoming_username = formData["username"];
				auto incoming_password = formData["password"];
				
				if (GFUserServer::g_Users.at(incoming_username) == incoming_password)
				{
					session->close(restbed::OK, "SUCCESS", { {"Content-Length", "8"} });
				}
				else
				{
					session->close(restbed::BAD_REQUEST, "ERROR: Wrong username and/or passcode!", { {"Content-Length", "39"} });
				}
			}
		);
	}

	void GFUserServer::post_debug_message_handler(const std::shared_ptr< restbed::Session > session)
	{
		const auto request = session->get_request();

		int content_length = request->get_header("Content-Length", 0);

		session->fetch(content_length, [](const std::shared_ptr< restbed::Session > session, const restbed::Bytes& body)
			{
				std::string urlEncodedData(body.begin(), body.end());
				std::map<std::string, std::string> formData = parseUrlEncoded(urlEncodedData);

				fprintf(stdout, "RECIEVED : BODY= %s", formData.at("DEBUG_FROM_CLIENT:").c_str());

				session->close(restbed::OK, "SUCCESS", { {"Content-Length", "8"} });

			}
		);
	}

	void GFUserServer::init()
	{
		g_DebugReciever.reset(new restbed::Resource);
		g_DebugReciever->set_path("/debug");
		g_DebugReciever->set_method_handler("POST", &post_debug_message_handler);

		g_SignupReciever.reset(new restbed::Resource);
		g_SignupReciever->set_path("/signup");
		g_SignupReciever->set_method_handler("POST", &post_signup_handler);

		g_LoginReciever.reset(new restbed::Resource);
		g_LoginReciever->set_path("/login");
		g_LoginReciever->set_method_handler("POST", &post_login_handler);

		g_Settings.reset(new restbed::Settings);
		g_Settings->set_port(1984);
		g_Settings->set_default_header("Connection", "close");

		g_Service.publish(g_DebugReciever);
		g_Service.publish(g_SignupReciever);
		g_Service.publish(g_LoginReciever);

		g_Service.set_logger(std::make_shared< CustomLogger >());
		g_Service.start(g_Settings);
	}



	void GFUserServer::shutdown()
	{

	}

	

} // namespace gfuser