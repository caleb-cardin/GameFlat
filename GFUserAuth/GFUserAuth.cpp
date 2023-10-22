// GFUserAuth.cpp : Source file for your target.
//

#include "GFUserAuth.h"

void post_method_handler(const std::shared_ptr< restbed::Session > session)
{
    const auto request = session->get_request();

    int content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length, [](const std::shared_ptr< restbed::Session > session, const restbed::Bytes& body)
        {
            fprintf(stdout, "%.*s\n", (int)body.size(), body.data());
            session->close(restbed::OK, "Hello, World!", { { "Content-Length", "13" } });
        });
}

int main()
{

    auto resource = std::make_shared< restbed::Resource >();
    resource->set_path("/resource");
    resource->set_method_handler("POST", post_method_handler);

    auto settings = std::make_shared< restbed::Settings >();
    settings->set_port(1984);
    settings->set_default_header("Connection", "close");

    restbed::Service service;
    service.publish(resource);
    service.start(settings);

    return EXIT_SUCCESS;

    gfuser::GFUserServer test{};
    test.init();
    test.run();
    test.shutdown();
}
