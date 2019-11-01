//
// Created by vaitovych on 01.11.19.
//

#include "print.h"
#include "sort.h"

size_t filesize(std::string path){

    if(boost::filesystem::is_regular(BPath(path))) return boost::filesystem::file_size(BPath(path));

    else if(boost::filesystem::is_directory(BPath(path))){

        size_t size=0;

        for(boost::filesystem::recursive_directory_iterator it(path);
            it!=boost::filesystem::recursive_directory_iterator();
            ++it)
        {
            if(!boost::filesystem::is_directory(*it))
                try {
                    size+=boost::filesystem::file_size(*it);
                }
                catch(...){}

        }
        return size;
    }
    else return 0;
}

void recursivePrint(flags_t &flags, std::vector<tuple> &regulars, std::vector<tuple> &dirs, std::vector<tuple> &special, std::string &currentPath){

    std::vector<tuple> newFiles;
    //Output for current dir
    if(flags.D) for(auto &d:dirs){
            std::cout<<"/"<<std::get<0>(d).substr(std::get<0>(d).find_last_of("/") + 1);
            if(flags.l) std::cout<<" "<<std::get<1>(d)<<" "<<std::get<2>(d);
            std::cout<<std::endl;
        }

    for(auto &r:regulars){
        if(boost::filesystem::is_directory(BPath(std::get<0>(r)))){
            std::cout<<"/";
            dirs.emplace_back(r);
        }
        std::cout<<std::get<0>(r).substr(std::get<0>(r).find_last_of("/") + 1);
        if(flags.l) std::cout<<" "<<std::get<1>(r)<<" "<<std::get<2>(r);
        std::cout<<std::endl;
    }

    if(flags.s) for(auto &s:special){
            std::cout<<"["<<std::get<0>(s).substr(std::get<0>(s).find_last_of("/") + 1)<<"]";
            if(flags.l) std::cout<<" "<<std::get<1>(s)<<" "<<std::get<2>(s);
            std::cout<<std::endl;
        }


    //Output for every directory
    for(auto &d:dirs){

        std::cout<<"\n\n\n"<<"/"<<std::get<0>(d)<<":\n"<<std::endl;

        newFiles.clear();
        //Storing directory entries
        for (const auto & entry : boost::filesystem::directory_iterator(std::get<0>(d))){
            time_t sys_time{ boost::filesystem::last_write_time(BPath(entry.path().string())) };
            boost::posix_time::ptime p_time{ boost::posix_time::from_time_t(sys_time) };
            newFiles.emplace_back(tuple(entry.path().string(), filesize(entry.path().string()), p_time));
        }
        //Recursive
        if(flags.R){
            sort(std::ref(flags), std::ref(newFiles), currentPath+std::get<0>(d).substr(std::get<0>(d).find_last_of("/") + 1), false);
        }
        else{

            std::vector<std::vector<tuple>> sorted{std::move(sort(std::ref(flags), std::ref(newFiles), "", true))};

            if(flags.D) for(auto &d:sorted[0]){
                    std::cout<<"/"<<std::get<0>(d).substr(std::get<0>(d).find_last_of("/") + 1);
                    if(flags.l) std::cout<<" "<<std::get<1>(d)<<" "<<std::get<2>(d);
                    std::cout<<std::endl;
                }
            for(auto &r:sorted[1]){
                if(boost::filesystem::is_directory(BPath(std::get<0>(r)))) std::cout<<"/";
                std::cout<<std::get<0>(r).substr(std::get<0>(r).find_last_of("/") + 1);
                if(flags.l) std::cout<<" "<<std::get<1>(r)<<" "<<std::get<2>(r);
                std::cout<<std::endl;
            }
            if(flags.s) for(auto &s:sorted[2]){
                    std::cout<<"["<<std::get<0>(s).substr(std::get<0>(s).find_last_of("/") + 1)<<"]";
                    if(flags.l) std::cout<<" "<<std::get<1>(s)<<" "<<std::get<2>(s);
                    std::cout<<std::endl;
                }
        }
    }
}