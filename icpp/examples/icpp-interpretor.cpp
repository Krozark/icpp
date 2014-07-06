#include <icpp/parser/Driver.hpp>
#include <fstream>

int main(int argc,char* argv[])
{
    std::ifstream file(argv[1],std::ifstream::in);
    if(file.good())
    {
        icpp::Driver driver(file);
        driver.parse();
        file.close();
    }
}
