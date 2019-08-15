#include <string>
#include <iostream>
#include <iomanip>
#include "web_request.hpp"

int main(int argc, char const *argv[])
{
    WebRequest web_req;

	web_req.execute(http::Method::METHOD_PUT, "https://postman-echo.com/put", "tttttttttttttttttttttttttttttttttttttttttt");
	web_req.execute(http::Method::METHOD_GET, "https://postman-echo.com/get?foo1=bar1&foo2=bar2");

    return 0;
}
