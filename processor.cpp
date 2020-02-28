#include "processor.h"

namespace WYLJUS002{

    //Functions
    VolImage::VolImage(){ //Default constructor

    }
    VolImage::~VolImage(){ //Default destructor
        std::cout << "Memory Cleanup\n";
        for (int i = 0; i < num_images; i++){
            for(int h = 0; h < height; h++){
                delete[] (slices[i][h]);
            }
            delete[] (slices[i]);
            slices[i] = nullptr;
        }
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
                    if(slice != nullptr){
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


    void VolImage::diffmap(int scliceI, int sliceJ, std::string output_prefix){
        /*
        difference map:
        computes the difference map between “slices” i and j. 
        Every outputpixel at coordinate (r,c) is computed as follows:
        (unsigned char)(abs( (float)volume[i][r][c] - (float)volume[j][r][c]) /2)
        */
       std::cout << "Prepare memory resources\n";
       unsigned char** slicei = slices[scliceI];
       unsigned char** slicej = slices[sliceJ];
       unsigned char** slicer;
       slicer = new unsigned char*[height];
       for (int i = 0; i < height; i++){
           slicer[i] = new unsigned char[width];
       }

       std::cout << "Begin diffmapping\n";
       for (int h = 0; h < height; h++){
           for (int w = 0; w < width; w++){
               slicer[h][w] = (unsigned char) (abs((float)slicei[h][w] - (float)slicej[h][w])/2);
           }
       }

       //Save diffmap
       //Write image slice
        write_image(output_prefix, slicer); //Doc says the slice should be called output

        //Write data file
        std::ofstream outfile(output_prefix);

        if(outfile){
            outfile << width << " " << height << " " << "1";
            outfile.close();
            std::cout << "Data file write success\n";
        }else{
            std::cout << "Error occured while trying to writer to file\n";
        }

        //Memory cleanup
        std::cout << "Cleanup memory from diffmap operations\n";
        for (int i = 0; i < height; i++){
            delete[] slicer[i];
        }
        delete[] slicer;
    }

    void VolImage::extract(int sliceId, std::string output_prefix){ //What is output_prefix for?
        //Write image slice
        write_image(output_prefix, sliceId); //Doc says the slice should be called output
        //Write data file
        std::ofstream outfile(output_prefix);

        if(outfile){
            outfile << width << " " << height << " " << "1";
            outfile.close();
            std::cout << "Data file write success\n";
        }else{
            std::cout << "Error occured while trying to writer to file\n";
        }
    }


    int VolImage::volImageSize(void){
        return width * height * num_images * sizeof(unsigned char) + num_images * (height * sizeof(unsigned char*) + 1);
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
        write_image(of_name, slices[index]);
    }

    void VolImage::write_image(std::string of_name, unsigned char** image_slice){
        std::stringstream strs;
        strs << of_name << ".raw";
        std::ofstream outfile(strs.str(), std::ios::binary);

        if(outfile){
            char* buffer;
            for(int h = 0; h < height; h++){
                buffer = (char*) image_slice[h];
                outfile.write(buffer, width);
            }
            outfile.close();

            std::cout << "Raw file write success\n";

        }else{
            std::cout << "Error occured while trying to writer to file\n";
        }
    }

    void VolImage::print_stats(){
        std::cout << "Number of images:  " << num_images << std::endl;
        std::cout << "Number of bytes required:  " << num_images*width*height*sizeof(unsigned char)<< std::endl;
    }



}