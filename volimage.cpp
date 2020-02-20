

class VolImage{
    private:
        int width, height; //Image stack's width and height
        std::vector<unsigned char**> slices; //Vector to hold the volimage's slices

    public:
        VolImage(); //Default constructor
        ~VolImage(); //Default destructor

        bool readImages(std::string baseName);


        void diffmap(int scaleI, int sliceJ, std::string output_prefix);

        void extract(int sliceId, std::string output_prefix);


        int volImageSize(void);

};