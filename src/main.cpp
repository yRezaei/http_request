#include <string>
#include <iostream>
#include "iex.hpp"

int main(int argc, char const *argv[])
{
    std::string symbol;
    std::string tocken;
    switch (argc)
    {
    case 3:
        symbol = argv[1];
        tocken = argv[2];
        break;

    default:
        std::cout << "Usage:\n" <<
            "\tpeackwork_challenge <symbol> <secret_token>" << std::endl;
            return 0;
            break;
    }


    auto com = iex::stocks::get_company(symbol, tocken);
    std::cout << "Company name: " << com.company_name << std::endl;

    auto logo = iex::stocks::get_company_logo(symbol, tocken);
    std::cout << "Company logo: " << logo.logo_url << std::endl;

    auto price = iex::stocks::get_price(symbol, "pk_2223eab4b940493eb33d2fe4d6375e25");
    std::cout << "Company price: " << price.latest_price << std::endl;

    return 0;
}
