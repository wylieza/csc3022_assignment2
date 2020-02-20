#include "volimage.h"


namespace WYLJUS002{
    //Functions




}


//Main
int main(int argc, char* argv[]){

    //Args handler
    std::cout << "There are " << argc << " arguments\nArgs: ";

    std::vector<std::string> args;
    for (int i = 1; i < argc; i ++){
        args.push_back(std::string(argv[i]));
        std::cout << args[i-1] << " ";
    }


}