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
            std::vector<unsigned char**> slices; //Vector to hold the volimage's slices

            std::string file_name;

        public:
            VolImage(); //Default constructor
            ~VolImage(); //Default destructor

            bool readImages(std::string baseName);

            void diffmap(int scaleI, int sliceJ, std::string output_prefix);

            void extract(int sliceId, std::string output_prefix);

            int volImageSize(void);

            int * extract_dimensions(std::string image_set);

            void extract_image(std::string base_name, int image_index, int * set_details); //Extract a file given known width and height
            

    };

}
#endif