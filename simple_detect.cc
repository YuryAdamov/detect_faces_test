#include <iostream>
#include <stdlib.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/join.hpp>
#include "detector.h"

namespace bfs = boost::filesystem;

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
       exit(1);
   }
   bfs::path dirpath(argv[1]);

   if(!bfs::is_directory(dirpath))
   {
       usage();
       exit(2);
   }

   std::vector<std::string> json_items;
   
   try
   {
       for ( 
               bfs::recursive_directory_iterator end, dir(dirpath);
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

       bfs::path out_path = dirpath/"result.json"; 
       std::ofstream resultJson(out_path.string());

       resultJson<<"["<<boost::join(json_items,",\n")<<"\n]\n";
   }
   catch(const bfs::filesystem_error& ex)
   {
       std::cerr<<ex.what()<<std::endl;
   }

}

