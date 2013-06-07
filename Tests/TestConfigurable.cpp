/*
 * =====================================================================================
 *
 *       Filename:  TestConfigurable.cpp
 *
 *    Description:  Test of GetNextToken function
 *
 *        Created:  07/06/2013 18:37:45
 *       Compiler:  gcc
 *
 *
 * =====================================================================================
 */

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <limits>

template <class T> T ToType(std::string const& Buffer)
{
    std::istringstream iss(Buffer);

    T t;

    iss >> t;

    return t;
}

template <class T> void GetNextToken(std::ifstream& Config, T& Data)
{
    if (!Config)
        throw std::runtime_error("Config stream is not open !");

    std::string buffer;
    while (Config.peek() == '#')
    Config.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::getline(Config, buffer, ' ');
    std::cout << "[DEBUG] : " << buffer << std::endl;
    Data = ToType<T>(buffer);
}

int main(int argc, char** argv)
{
    std::ifstream f(argv[1]);
    
    unsigned char t;
    GetNextToken<unsigned char>(f, t);

    std::cout << t << std::endl;

    return 0;
}
