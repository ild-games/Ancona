#include <iostream>

#include <Ancona/Framework/Config/Config.cpp>

int main(int argc, char ** argv)
{
    std::cout << "Reading Config File" << std::endl;
    Config::Load("ConfigTest.txt");
    std::cout << "test1: " <<  Config::GetOption("test1") << std::endl;
    std::cout << "test2: " <<  Config::GetOption("test2") << std::endl;
    std::cout << "test3: " <<  Config::GetOption("test3") << std::endl;
    std::cout << "test4: " <<  Config::GetOption("test4") << std::endl;
    std::cout << "test5: " <<  Config::GetOption("test5") << std::endl;
    return 0;
}
