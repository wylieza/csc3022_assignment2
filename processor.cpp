#include "processor.h"

namespace WYLJUS002{

    //Functions
    VolImage::VolImage(){ //Default constructor

    }
    VolImage::~VolImage(){ //Default destructor

    }

    bool VolImage::readImages(std::string baseName){
        return false;
    }


    void VolImage::diffmap(int scaleI, int sliceJ, std::string output_prefix){

    }

    void VolImage::extract(int sliceId, std::string output_prefix){

    }


    int VolImage::volImageSize(void){

    }

    int * VolImage::extract_dimensions(std::string image_set){
        int *dim = new int[3];
        std::ifstream infile("./brain_mri_raws/" + image_set + ".data");

        std::string line;
        std::stringstream ss;
        if(infile.is_open()){
            if(getline(infile, line)){
                ss.str(line);
                for(int i = 0; i < 3; i++){
                    ss >> *(dim+i);
                }
            }else{
                std::cout << "Error, file containing image set dimensions empty!\n";
            }
        }else{
            std::cout << "Error opening file containing image set dimensions\n";
        }
        width = *dim;
        height = *(dim+1);
        return dim; //TODO: Add a value to specify error in reading data
    }

    u_char** VolImage::extract_image(std::string base_name, int image_index, int *set_details){
        std::cout << "File name: " << base_name << "\n";
        std::cout << "Image index: " << image_index << "\n";
        std::cout << "width: " << *set_details << " height: " << *(set_details+1) << " num images: " << *(set_details+2) << "\n";
    
        u_char ** slice;
        slice = new u_char*[*(set_details+1)];
        for (int i = 0; i < *(set_details+1); i++){
            slice[i] = new u_char[*set_details];
        }

        std::stringstream strs;
        strs << "./brain_mri_raws/" << base_name << image_index << ".raw";
        std::ifstream infile(strs.str(), std::ios::binary);

        if(infile){
            int length;

            //Determine length of file
            infile.seekg(0, infile.end);
            length = infile.tellg();
            infile.seekg(0, infile.beg);

            //Determine if dimensions match specs and READ
            char* row_buffer = new char[*set_details]; //Tempory reading buffer
            if(*set_details**(set_details+1) == length){
                for (int h = 0; h < *(set_details+1); h++){
                    infile.read(row_buffer, *set_details);
                    slice[h] = (u_char*) row_buffer;
                }
                delete(row_buffer); //memory cleanup
                infile.close();
            
            std::cout << "Image slice stored" << std::endl;
            return slice;
            
            }else{
                std::cout << "Error: The image dimensions do not match those spcified in data file";
            }

        }else{
            std::cout << "An error has occured during reading the file!";
        }  
    }

    void VolImage::write_image(std::string of_name, u_char ** slice){
        std::stringstream strs;
        strs << of_name << ".raw";
        std::ofstream outfile(strs.str(), std::ios::binary);

        if(outfile){
            char* buffer;
            for(int h = 0; h < height; h++){
                buffer = (char*) slice[h];
                for (int w = 0; w < width; w++){ //No improvement :(
                    outfile.write(&buffer[w], 1);
                }
            }
            outfile.close();

            std::cout << "File write success\n";

        }else{
            std::cout << "Error occured while trying to writer to file\n";
        }
    }



}