#include "processor.h"

//Main
int main(int argc, char* argv[]){

    WYLJUS002::VolImage processor; //Object of the VolImage class
    //Args handler
    //std::cout << "There are " << argc << " arguments\n";

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

    if(argc == 2){ //Load, memory usage details, cleanup
        args.image_set = argv[1];
        processor.readImages(args.image_set);    

        processor.print_stats(); //Check these results!
    }else if (argc == 6 || argc == 5){
        args.image_set = argv[1];
        if(argv[2][1] == 'd'){ //TODO make this case insensitive
            if(argc != 6){
                std::cout << "Invalid number of arguments detected\n";
                exit(0);
            }else{ // Perform the diffmap operation   
            std::cout << "Diffmap\n";       
                args.d = true;
                args.i = argv[3][0] - '0';
                args.j = argv[4][0] - '0';
                args.outf_name = argv[5];

                processor.readImages(args.image_set);
                processor.diffmap(args.i, args.j, args.outf_name);
            }
        }else if(argv[2][1] == 'x'){
            if(argc != 5){
                std::cout << "Invalid number of arguments detected\n";
                exit(0);
            }else{ //Perform the extract operation         
                args.x = true;
                args.i = argv[3][0] - '0';
                args.outf_name = argv[4];

                processor.readImages(args.image_set);
                processor.extract(args.i, args.outf_name);

            }
        }else{
            std::cout << "Unknown action specifier!\n";
        }        
    }else{
        std::cout << "You must specify a valid number of arguments!\n";
        exit(0);
    }

}