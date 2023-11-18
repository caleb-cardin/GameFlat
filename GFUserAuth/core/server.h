#pragma once

// #include <cstdarg>
// #include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstdio>
#include <restbed>




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

		static void post_signup_handler(const std::shared_ptr< restbed::Session > session);
		static void post_login_handler(const std::shared_ptr< restbed::Session > session);
        static void post_debug_message_handler(const std::shared_ptr< restbed::Session > session);

        static std::map<std::string, std::string> g_Users;
	private:

		restbed::Service g_Service;
		std::shared_ptr<restbed::Resource> g_DebugReciever;
		std::shared_ptr<restbed::Resource> g_SignupReciever;
		std::shared_ptr<restbed::Resource> g_LoginReciever;
		std::shared_ptr<restbed::Settings> g_Settings;

	};
} // namespace gfuser