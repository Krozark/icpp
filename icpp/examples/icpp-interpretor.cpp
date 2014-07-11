#include <icpp/parser/Driver.hpp>
#include <icpp/defines.hpp>

#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdio>


int main(int argc,char* argv[])
{
    std::string history_name;
    {
        char* home = ::getenv("HOME");
        if(home != nullptr)
            history_name = std::string(home)+"/";
        else
            history_name = "./";
        history_name+= ".icpp_history";
    }
    utils::log::show_time = false;
    if(argc > 1)
    {
        std::ifstream file(argv[1],std::ifstream::in);
        if(file.good())
        {
            icpp::Driver driver(file);
            driver.parse();
            file.close();
        }
        else
            utils::log::error("Input","error with file \"",argv[1],"\"");
    }
    else //cin
    {
        std::cout<<"Icpp "<<MAJOR_VERSION<<"."<<MINOR_VERSION<<"."<<PATCH_VERSION<<std::endl;
        std::stringstream stream;
        icpp::Driver driver(stream);
        driver.interactive(true);

        utils::sys::file::touch(history_name);
        ::read_history(history_name.c_str());

        int line = 1;
        do
        {
            std::stringstream prompt;
                prompt<<utils::log::colors::blue
                <<"In ["
                <<utils::log::format::bold
                <<utils::log::colors::light_blue
                <<line++
                <<utils::log::format::reset_bold
                <<utils::log::colors::blue
                <<"]: "
                <<utils::log::colors::reset;

            char* line_read = ::readline(prompt.str().c_str());

            if (line_read != nullptr and line_read[0] != '\0')
            { 
                ::add_history(line_read);
                if(::append_history(1,history_name.c_str()) != 0)
                    ::write_history(history_name.c_str());
            }
            
            stream<<line_read<<std::endl;
            ::free(line_read);

            driver.parse();
        }while(not driver.finish());
        std::cout<<std::endl;
    }
}
