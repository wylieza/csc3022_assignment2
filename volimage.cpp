#include "processor.h"

//Main
int main(int argc, char* argv[]){

    WYLJUS002::VolImage processor; //Object of the VolImage class

    //Args handler
    struct arg_params{
            std::string image_set;
            bool d = false;
            bool x = false;
            int i;
            int j;
            std::string outf_name;
    };

    struct arg_params args;

    if(argc == 2){ //Load imagebase, display memory usage, cleanup
        args.image_set = argv[1];
        processor.readImages(args.image_set);    
        processor.print_stats();

    }else if (argc == 6 || argc == 5){
        args.image_set = argv[1];
        if(tolower(argv[2][1]) == 'd'){
            if(argc != 6){
                std::cout << "Invalid number of arguments detected\n";
                exit(0);
            }else{ // Perform the diffmap operation      
                args.d = true;
                args.i = argv[3][0] - '0';
                args.j = argv[4][0] - '0';
                args.outf_name = argv[5];

                processor.readImages(args.image_set);
                processor.diffmap(args.i, args.j, args.outf_name);
            }
        }else if(tolower(argv[2][1]) == 'x'){
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