#include "http_request.hpp"
#include <vector>

HTTPRequest::HTTPRequest() : curl_ptr_(nullptr),
                             headers_(nullptr)
{
    curl_ptr_ = curl_easy_init();

    curl_easy_setopt(curl_ptr_, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl_ptr_, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl_ptr_, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_ptr_, CURLOPT_SSL_VERIFYPEER, 0L);
    //curl_easy_setopt(curl_ptr_, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl_ptr_, CURLOPT_WRITEFUNCTION, HTTPRequest::curl_write_callback);

    receive_callback_ = [](const std::string &received_data) {
        std::cout << "Received data: " << received_data << std::endl;
    };

    error_callback_ = [](const std::string &error_message) {
        std::cout << "Error: " << error_message << std::endl;
    };
}

HTTPRequest::~HTTPRequest()
{
    clean_up();
}

void HTTPRequest::set_receive_callback(std::function<void(const std::string &)> receive_callback)
{
    receive_callback_ = receive_callback;
}

void HTTPRequest::set_error_callback(std::function<void(const std::string &)> error_callback)
{
    error_callback_ = error_callback;
}

void HTTPRequest::set_timeout(std::uint16_t seconds)
{
    if (curl_ptr_)
        curl_easy_setopt(curl_ptr_, CURLOPT_TIMEOUT, seconds);
}

void HTTPRequest::set_ssl_verification(bool value)
{
    if (value)
        if (curl_ptr_)
            curl_easy_setopt(curl_ptr_, CURLOPT_SSL_VERIFYPEER, 1L);
        else if (curl_ptr_)
            curl_easy_setopt(curl_ptr_, CURLOPT_SSL_VERIFYPEER, 0L);
}

void HTTPRequest::clean_up()
{
    if (curl_ptr_)
        curl_easy_cleanup(curl_ptr_);

    if (headers_)
        curl_slist_free_all(headers_);
}

void HTTPRequest::set_http_header(std::initializer_list<std::string> header_parameters)
{
    if (headers_)
        curl_slist_free_all(headers_);

    std::vector<std::string> list(header_parameters);

    for (auto &item : list)
        if (!item.empty())
            headers_ = curl_slist_append(headers_, item.c_str());

    curl_easy_setopt(curl_ptr_, CURLOPT_HTTPHEADER, headers_);
}

std::size_t HTTPRequest::curl_write_callback(const char *in, std::size_t size, std::size_t num, std::string *out)
{
    const auto total_bytes{size * num};
    if (total_bytes != 0)
        out->append(in, total_bytes);
    return total_bytes;
}

std::string HTTPRequest::method_to_string(HTTPRequest::Method method)
{
    if (method == HTTPRequest::METHOD_PUT)
        return "PUT";
    else if (method == HTTPRequest::METHOD_POST)
        return "POST";
    else if (method == HTTPRequest::METHOD_GET)
        return "GET";
    else if (method == HTTPRequest::METHOD_DELETE)
        return "DELETE";
}

bool HTTPRequest::execute(HTTPRequest::Method method, const std::string &url, const std::string &message)
{
    if (curl_ptr_)
    {
        std::string response_data;

        curl_easy_setopt(curl_ptr_, CURLOPT_CUSTOMREQUEST, method_to_string(method).c_str());
        curl_easy_setopt(curl_ptr_, CURLOPT_URL, url.c_str());

        if (method == HTTPRequest::METHOD_PUT)
        {
            if (message.empty())
                return false;
            curl_easy_setopt(curl_ptr_, CURLOPT_POSTFIELDS, message.c_str());
        }

        curl_easy_setopt(curl_ptr_, CURLOPT_WRITEDATA, &response_data);
        if (auto result = curl_easy_perform(curl_ptr_); result != CURLE_OK)
        {
            error_callback_(curl_easy_strerror(result));
            return false;
        }

        if (!response_data.empty())
            receive_callback_(response_data);

        return true;
    }
    return false;
}