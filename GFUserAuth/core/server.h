#pragma once

#include <string>
#include <memory>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <sstream>
#include <iomanip>
#include <restbed>
#include <openssl/sha.h>


namespace gfuser {

    class CustomLogger : public restbed::Logger
    {
    public:
        void stop(void)
        {
            return;
        }

        void start(const std::shared_ptr< const restbed::Settings >&)
        {
            return;
        }

        void log(const Level, const char* format, ...)
        {
            va_list arguments;
            va_start(arguments, format);

            vfprintf(stderr, format, arguments);
            fprintf(stderr, "\n");

            va_end(arguments);
        }

        void log_if(bool expression, const Level level, const char* format, ...)
        {
            if (expression)
            {
                va_list arguments;
                va_start(arguments, format);
                log(level, format, arguments);
                va_end(arguments);
            }
        }
    };

	class GFUserServer {
	public:
		GFUserServer() {}
		~GFUserServer() = default;

		void init();
		void shutdown();

		static void post_req_handler(const std::shared_ptr< restbed::Session > session);
	private:

		restbed::Service g_Service;
		std::shared_ptr<restbed::Resource> g_ClientReciever;
		std::shared_ptr<restbed::Settings> g_Settings;

        static std::string username;
        static std::string password;
		std::vector<std::string> g_Users;
	};
} // namespace gfuser