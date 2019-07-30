#include <string>
#include <iostream>
#include "iex.hpp"


int main(int argc, char const *argv[])
{
  auto com = iex::stocks::get_company("aapl", "pk_2223eab4b940493eb33d2fe4d6375e25");
  std::cout << "Company name: " << com.company_name << std::endl;

  auto logo = iex::stocks::get_company_logo("aapl", "pk_2223eab4b940493eb33d2fe4d6375e25");
  std::cout << "Company logo: " << logo.logo_url << std::endl;

  auto price = iex::stocks::get_price("aapl", "pk_2223eab4b940493eb33d2fe4d6375e25");
  std::cout << "Company price: " << price.latest_price << std::endl;

  return 0;
}
