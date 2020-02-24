#include "processor.h"

//Main
int main(int argc, char* argv[]){

    WYLJUS002::VolImage processor; //Object of the VolImage class
    //Args handler
    std::cout << "There are " << argc << " arguments\n";

    struct arg_params{
            std::string image_set;
            bool d = false;
            bool x = false;
            int i;
            int j;
            std::string outf_name;
    };

    struct arg_params args;

    //std::vector<std::string> args;
        //args.push_back(std::string(argv[i]));
        //std::cout << args[i-1] << " ";

    if(argc >= 2){
        std::cout << "No action specified...\n";
        args.image_set = argv[1];
    }else{
        std::cout << "You must specify arguments!\n";
        exit(0);
    }
    if (argc > 2){
        if(argv[2][1] == 'd'){ //TODO make this case insensitive
            if(argc != 6){
                std::cout << "Invalid number of arguments detected\n";
                exit(0);
            }else{            
                args.d = true;
                args.i = argv[3][0] - '0';
                args.j = argv[4][0] - '0';
                args.outf_name = argv[5];
            }
        }else if(argv[2][1] == 'x'){
            if(argc != 5){
                std::cout << "Invalid number of arguments detected\n";
                exit(0);
            }else{            
                args.x = true;
                args.i = argv[3][0] - '0';
                args.outf_name = argv[4];
            }
        }
        
    }

    processor.extract_image(args.image_set, args.i, processor.extract_dimensions(args.image_set));

}