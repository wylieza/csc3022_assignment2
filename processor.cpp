#include "processor.h"

namespace WYLJUS002{

    //Functions
    VolImage::VolImage(){ //Default constructor

    }
    VolImage::~VolImage(){ //Default destructor

    }

    bool VolImage::readImages(std::string baseName){
        std::ifstream infile("./brain_mri_raws/" + baseName + ".data");

        std::string line;
        std::stringstream ss;
        unsigned char ** slice;

        if(infile.is_open()){
            if(getline(infile, line)){
                ss.str(line);
                ss >> width >> height >> num_images;
                
                std::cout << "Data file read success, importing images\n";

                for (int i = 0; i < num_images; i++){
                    slice = extract_image(baseName, i);
                    if(slice != NULL){
                        slices.push_back(slice);
                    }else{
                        std::cout << "An error occured during slice read... Slice not appended!\n";
                    }
                }
                
            }else{
                std::cout << "Error, file containing image set dimensions empty!\n";
            }
        }else{
            std::cout << "Error opening file containing image set dimensions!\n";
        }
        return false;
    }


    void VolImage::diffmap(int scaleI, int sliceJ, std::string output_prefix){

    }

    void VolImage::extract(int sliceId, std::string output_prefix){

    }


    int VolImage::volImageSize(void){

    }

    unsigned char** VolImage::extract_image(std::string base_name, int image_index){
        //std::cout << "File name: " << base_name << "\n";
        //std::cout << "Image index: " << image_index << "\n";
        //std::cout << "width: " << width << " height: " << height << " num images: " << num_images << "\n";

        unsigned char ** slice;
        slice = new unsigned char*[height];
        for (int i = 0; i < height; i++){
            slice[i] = new unsigned char[width];
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
            if(width*height == length){
                for (int h = 0; h < height; h++){
                    char* row_buffer = new char[width]; //Allocate memory for a row
                    infile.read(row_buffer, width);
                    slice[h] = (unsigned char*) row_buffer; //Store pointer to allocated memory
                }
                
            infile.close();
            return slice;

            }else{
                std::cout << "Error: The image dimensions do not match those spcified in data file";
            }

        }else{
            std::cout << "An error has occured during reading the file!";
        }  
        return NULL;
    }

    void VolImage::write_image(std::string of_name, int index){
        std::stringstream strs;
        strs << of_name << ".raw";
        std::ofstream outfile(strs.str(), std::ios::binary);

        if(outfile){
            char* buffer;
            for(int h = 0; h < height; h++){
                buffer = (char*) slices[index][h];
                outfile.write(buffer, width);
            }
            outfile.close();

            std::cout << "File write success\n";

        }else{
            std::cout << "Error occured while trying to writer to file\n";
        }
    }

    void VolImage::print_stats(){
        std::cout << "Number of images:  " << num_images << std::endl;
        std::cout << "Number of bytes required:  " << num_images*width*height*sizeof(unsigned char)<< std::endl;
    }



}