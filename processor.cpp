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
        return dim; //TODO: Add a value to specify error in reading data
    }

    void VolImage::extract_image(std::string file_name, int image_index, int *set_details){
        std::cout << "File name: " << file_name << "\n";
        std::cout << "Image index: " << image_index << "\n";
        std::cout << "width: " << *set_details << " height: " << *(set_details+1) << " num images: " << *(set_details+2) << "\n";
    }



}