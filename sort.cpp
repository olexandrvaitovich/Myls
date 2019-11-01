//
// Created by vaitovych on 01.11.19.
//

#include "sort.h"
#include "print.h"
#include <filesystem>


bool sortByName(tuple first, tuple second){return (std::get<0>(first).compare(std::get<0>(second)))<0;}



bool sortBySize(tuple first, tuple second){return (std::get<1>(first)==std::get<1>(second))? sortByName(first, second):std::get<1>(first)<std::get<1>(second);}



bool sortByTime(tuple first, tuple second){return (std::get<2>(first).operator==(std::get<2>(second)))? sortByName(first, second):std::get<2>(first).operator<(std::get<2>(second));}



bool sortByExtension(tuple first, tuple second){
    auto ext1 = std::get<0>(first).substr(std::get<0>(first).find_last_of(".") + 1);
    auto ext2 = std::get<0>(second).substr(std::get<0>(second).find_last_of(".") + 1);
    return (ext1.compare(ext2))?ext1.compare(ext2)<0:sortByName(first, second);
}



std::vector<std::vector<tuple>> sort(flags_t &flags, std::vector<tuple> &files, std::string currentPath, bool ret){
    //currentPath just to pass it to the recursivePrint
    //ret for return value(used when -R==true) or not(used when -R=false)
    std::vector<tuple> regulars;
    std::vector<tuple> dirs;
    std::vector<tuple> special;

    if(flags.sort=='N'){
        std::sort(files.begin(), files.end(), sortByName);
    }
    else if(flags.sort=='t'){
        std::sort(files.begin(), files.end(), sortByTime);
    }
    else if(flags.sort=='X'){
        std::sort(files.begin(), files.end(), sortByExtension);
    }
    else if(flags.sort=='S'){
        std::sort(files.begin(), files.end(), sortBySize);
    }


    for(auto &f:files){

        if(flags.D && boost::filesystem::is_directory(BPath(std::get<0>(f)))) dirs.emplace_back(f);

        else if(flags.F || flags.s){
            //symlink
            if(boost::filesystem::is_symlink(BPath(std::get<0>(f)))){if(flags.F) std::get<0>(f)+="@";}
            //fifo
            else if(std::filesystem::is_fifo(std::filesystem::path(std::get<0>(f)))) std::get<0>(f)+="|";
            //socket
            else if(std::filesystem::is_socket(std::filesystem::path(std::get<0>(f)))) std::get<0>(f)+="=";
                //executable
            else if(!access(std::get<0>(f).c_str(), X_OK) && !boost::filesystem::is_directory(BPath(std::get<0>(f)))){if(flags.F) std::get<0>(f)+="*";}
                //other
            else if(boost::filesystem::is_other(BPath(std::get<0>(f)))){if(flags.F) std::get<0>(f)+="?";}

            else{
                //if no one
                regulars.emplace_back(f);
                continue;
            }
            if(flags.s) special.emplace_back(f);

            else regulars.emplace_back(f);
        }
        else regulars.emplace_back(f);
    }


    if(flags.r){
        std::reverse(regulars.begin(), regulars.end());
        std::reverse(dirs.begin(), dirs.end());
        std::reverse(special.begin(), special.end());
    }
    //only for -R==false
    std::vector<std::vector<tuple>> sorted;
    if(ret){
        sorted={std::move(dirs), std::move(regulars), std::move(special)};
        return std::ref(sorted);
    }
    recursivePrint(std::ref(flags), std::ref(regulars), std::ref(dirs), std::ref(special), std::ref(currentPath));
    return sorted;

}