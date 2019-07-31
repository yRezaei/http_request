#include <string>
#include <iostream>
#include <iomanip>
#include "iex.hpp"

int main(int argc, char const *argv[])
{
    std::string symbol;
    std::string token;
    switch (argc)
    {
    case 3:
        symbol = argv[1];
        token = argv[2];
        break;

    default:
        std::cout << "Usage:\n" <<
            "\tpeackwork_challenge <symbol> <secret_token>" << std::endl;
            return 0;
            break;
    }

    auto com = iex::stocks::get_company(symbol, token);
    auto logo = iex::stocks::get_company_logo(symbol, token);
    auto price = iex::stocks::get_price(symbol, token);

    std::cout << "Company:\n" << std::left
        << '\t' << std::setw(15) << "Name: " << com.company_name << '\n'
        << '\t' << std::setw(15) << "logo URL: " << logo.logo_url << '\n'
        << '\t' << std::setw(15) << "Price: " << price.latest_price << std::endl;

    return 0;
}
