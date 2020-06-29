#include <iostream>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include "detector.h"

void usage(void)
{
    std::cerr<<"Usage: simple_detect <path_to_files>"<<std::endl;
}

int main(int argc, char *argv[])
{
   std::pair<DetectError,std::vector<cv::Rect>> faces;
   if(argc != 2)
   {
       usage();
       exit(0);
   }
   
   for ( 
           boost::filesystem::recursive_directory_iterator end, dir(argv[1]);
    dir != end; ++dir 
    ) 
   {
    // std::cout << *dir << "\n";  // full path
    std::cout << dir->path() << std::endl; 
    faces = detect_faces(dir->path().string());
    if(faces.first==DETECT_FACE_ERR_NONE){
        for(auto &face: faces.second){
            std::cout<<face<<std::endl;
        }
    }
    //std::cout<<faces<<std::endl;
   }

}

