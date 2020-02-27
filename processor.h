#ifndef PROCESSOR
#define PROCESSOR

#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

namespace WYLJUS002{

    class VolImage{
        private:
            int width, height; //Image stack's width and height
            int num_images;
            std::vector<unsigned char**> slices; //Vector to hold the volimage's slices

            std::string file_name;

        public:
            VolImage(); //Default constructor
            ~VolImage(); //Default destructor

            bool readImages(std::string baseName);

            void diffmap(int scaleI, int sliceJ, std::string output_prefix);

            void extract(int sliceId, std::string output_prefix);

            int volImageSize(void);

            unsigned char** extract_image(std::string base_name, int image_index); //Extract a file given known width and height
            
            void write_image(std::string of_name, int index); //Write image slice to file

            void print_stats();

    };

}
#endif