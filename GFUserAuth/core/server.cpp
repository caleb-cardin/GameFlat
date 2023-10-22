#include "server.h"


namespace gfuser {

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

	void GFUserServer::post_req_handler(const std::shared_ptr< restbed::Session > session)
	{
		const auto request = session->get_request();

		int content_length = request->get_header("Content-Length", 0);

		session->fetch(content_length, [](const std::shared_ptr< restbed::Session > session, const restbed::Bytes& body)
			{
				std::string urlEncodedData(body.begin(), body.end());
				std::map<std::string, std::string> formData = parseUrlEncoded(urlEncodedData);

				GFUserServer::username = formData["username"];
				GFUserServer::password = formData["password"];
				fprintf(stdout, "%s, %s", username.c_str(), password.c_str());

				// fprintf(stdout, "%.*s\n", (int)body.size(), body.data());

				session->close(restbed::OK, "SUCCESS", { {"Content-Length", "20"} });
			
			}
		);
	}

	void GFUserServer::init()
	{
		g_ClientReciever.reset( new restbed::Resource );
		g_ClientReciever->set_path("/signup");
		g_ClientReciever->set_method_handler("POST", post_req_handler);

		g_Settings.reset(new restbed::Settings);
		g_Settings->set_port(1984);
		g_Settings->set_default_header("Connection", "close");

		g_Service.publish(g_ClientReciever);

		g_Service.set_logger(std::make_shared< CustomLogger >());
		g_Service.start(g_Settings);
	}



	void GFUserServer::shutdown()
	{

	}

	

} // namespace gfuser