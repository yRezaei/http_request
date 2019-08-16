#include <string>
#include <iostream>
#include <iomanip>
#include "http_request.hpp"

int main(int argc, char const *argv[])
{
    HTTPRequest http_req;

	http_req.execute(HTTPRequest::Method::METHOD_PUT, "https://postman-echo.com/put", "tttttttttttttttttttttttttttttttttttttttttt");
	http_req.execute(HTTPRequest::Method::METHOD_GET, "https://postman-echo.com/get?foo1=bar1&foo2=bar2");

    return 0;
}
