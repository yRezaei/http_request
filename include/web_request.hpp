#ifndef WEB_REQUEST_HPP_
#define WEB_REQUEST_HPP_

#include <curl/curl.h>
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <initializer_list>

namespace http
{
enum Method : std::uint8_t
{
    METHOD_PUT,
    METHOD_POST,
    METHOD_GET,
    METHOD_DELETE
};

inline std::string method_to_string(http::Method method)
{
    if (method == http::METHOD_PUT)
        return "PUT";
    else if (method == http::METHOD_POST)
        return "POST";
    else if (method == http::METHOD_GET)
        return "GET";
    else if (method == http::METHOD_DELETE)
        return "DELETE";
}
} // namespace http

class WebRequest
{

private:
    CURL* curl_ptr_;
    curl_slist* headers_;
    std::function<void(const std::string &)> receive_callback_;
    std::function<void(const std::string &)> error_callback_;

public:
    WebRequest();
    ~WebRequest();
    void set_receive_callback(std::function<void(const std::string &)> receive_callback);
    void set_error_callback(std::function<void(const std::string &)> error_callback);

    bool execute(http::Method method, const std::string &url, const std::string &message = "");
    void set_timeout(std::uint16_t seconds);
    void set_ssl_verification(bool value);
    void set_http_header(std::initializer_list<std::string> header_parameters);

private:
    void clean_up();
	static std::size_t curl_write_callback(const char* in, std::size_t size, std::size_t num, std::string* out);
};

#endif // !WEB_REQUEST_HPP_
