#ifndef IEX_HPP_
#define IEX_HPP_

#include <json/json.h>
#include <curl/curl.h>
#include <iostream>

#define IEX_ENDPOINT "https://cloud.iexapis.com/beta/stock/"

namespace iex::stocks
{
struct CompanyData
{
    std::string called_endpoint;
    std::string stock_symbol;
    std::string company_name;
    std::string exchange;
    std::string industry;
    std::string website;
    std::string description;
    std::string CEO;
    std::string issue_type;
    std::string sector;
    std::vector<std::string> tags;
};

struct CompanyLogoData
{
    std::string called_endpoint;
    std::string stock_symbol;
    std::string logo_url;
};

struct PriceData
{
    std::string called_endpoint;
    std::string stock_symbol;
    double latest_price;
};

namespace internal_commands
{

static std::size_t curl_callback(const char *in, std::size_t size, std::size_t num, std::string *out)
{
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

static void send_get_request(Json::Value &jason_data, const std::string url)
{
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    long int httpCode(0);

    std::unique_ptr<std::string> httpData(new std::string);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpData && httpData.get())
    {
        std::stringstream ss;
        ss.str(*httpData);
        if (!(ss >> jason_data))
            std::cerr << "Error in 'iex::stocks::sendGetRequest' -> Received data can not be written into Jason file 'Json::Value'." << std::endl;
    }
    else
    {
        std::cerr << "Error in 'iex::stocks::sendGetRequest' -> Received data is emptay." << std::endl;
    }
}
} // namespace internal_commands

static CompanyData get_company(const std::string stock_symbol, const std::string &secret_token)
{
    std::string url = IEX_ENDPOINT;
    url += std::string(stock_symbol) + "/company/5y?token=" + secret_token;

    Json::Value jason_data;
    internal_commands::send_get_request(jason_data, url);

    CompanyData comp_data;

    comp_data.called_endpoint = url;
    comp_data.stock_symbol = stock_symbol;
    comp_data.company_name = jason_data["companyName"].asString();
    comp_data.exchange = jason_data["exchange"].asString();
    comp_data.industry = jason_data["industry"].asString();
    comp_data.website = jason_data["website"].asString();
    comp_data.description = jason_data["description"].asString();
    comp_data.CEO = jason_data["CEO"].asString();
    comp_data.issue_type = jason_data["issue_type"].asString();
    comp_data.sector = jason_data["sector"].asString();

    // Iterate over all tags and add to vector
    auto tag_list = jason_data["tags"];
    comp_data.tags.resize(tag_list.size());
    for (auto i = 0u; i < tag_list.size(); i++)
    {
        comp_data.tags[i] = tag_list[i].asString();
    }

    return comp_data;
}

static CompanyLogoData get_company_logo(const std::string &stock_symbol, const std::string &secret_token)
{
    std::string url = IEX_ENDPOINT;
    url += stock_symbol + "/logo/5y?token=" + secret_token;

    Json::Value json_data;
    internal_commands::send_get_request(json_data, url);

    CompanyLogoData logo_data;
    logo_data.called_endpoint = url;
    logo_data.stock_symbol = stock_symbol;
    logo_data.logo_url = json_data["url"].asString();

    return logo_data;
}

static PriceData get_price(const std::string stock_symbol, const std::string &secret_token)
{
    std::string url = IEX_ENDPOINT;
    url += std::string(stock_symbol) + "/price/5y?token=" + secret_token;

    Json::Value jason_data;
    internal_commands::send_get_request(jason_data, url);

    PriceData price_data;
    price_data.called_endpoint = url;
    price_data.stock_symbol = stock_symbol;
    price_data.latest_price = jason_data.asDouble();

    return price_data;
}

} // namespace iex::stocks

#endif // !IEX_HPP_
