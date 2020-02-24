#include "volimage.h"


namespace WYLJUS002{
    
    //Functions
    int * extract_dimensions(std::string image_set){
        int *dim = new int[3];
        std::ifstream infile(image_set + ".data");

        std::string line;
        std::stringstream ss;
        if(infile.is_open()){
            if(getline(infile, line)){
                ss.str(line);
                for(int i = 0; i < 3; i++){
                    ss >> *(dim+i);
                }
            }else{
                std::cout << "Error, file containing image set dimensions empty!";
            }
        }else{
            std::cout << "Error opening file containing image set dimensions";
        }
        return dim; //TODO: Add a value to specify error in reading data
    }

    void extract_image(std::string file_name, int image_index, int *set_details){
        std::cout << "File name: " << file_name << "\n";
        std::cout << "Image index: " << image_index << "\n";
        std::cout << "width: " << *set_details << " height: " << *(set_details+1) << " num images: " << *(set_details+2) << "\n";
    }



}


//Main
int main(int argc, char* argv[]){

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
    if (argc > 1){
        args.image_set = argv[1];
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
        }else{
            std::cout << "No action specified...\n";
        }
        
    }else{
        std::cout << "You must specify arguments!\n";
        exit(0);
    }

    WYLJUS002::extract_image(args.image_set, args.i, WYLJUS002::extract_dimensions(args.image_set));


}