#include <iostream>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/join.hpp>
#include "detector.h"

void usage(void)
{
    std::cerr<<"Usage: simple_detect <path_to_files>"<<std::endl;
}

int main(int argc, char *argv[])
{
   DetectorResult faces;
   if(argc != 2)
   {
       usage();
       exit(0);
   }
   std::vector<std::string> json_items;
   
   for ( 
           boost::filesystem::recursive_directory_iterator end, dir(argv[1]);
    dir != end; ++dir 
    ) 
   {
    // std::cout << *dir << "\n";  // full path
    std::cout << dir->path() << std::endl; 
    faces = detect_faces(dir->path().string());

    json_items.push_back(faces.toJson());


    if(faces.errorCode==DETECT_FACE_ERR_NONE){
        for(auto &face: faces.faces){
            std::cout<<face<<std::endl;
        }
    }
    //std::cout<<faces<<std::endl;
   }

   std::cout<<"["<<boost::join(json_items,",\n")<<"\n]\n";

}

