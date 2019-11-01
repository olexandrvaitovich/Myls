#include "config.h"
#include "sort.h"
#include "print.h"



int main(int argc, char* argv[]) {

    flags_t flags;
    std::vector<tuple> files;

    bool f = false;
    bool sortOk = true;

    std::string sorts = "UStXN";
    std::string secondarySorts = "Ds";

    std::stringstream stream;

    for(int i=1;i<argc;i++){
        if(*argv[i]=='-' && !f){

            if(strcmp(argv[i],"--help")==0 || strcmp(argv[i],"-h")==0){
                std::cout<<"Usage:\n"
                           "./myls [path|mask] [-l] [-R] [-r] [-F] [--] <files|dirs>\n"
                           "-l - details\n"
                           "-R recursivly iterate through dirs and print all the files\n"
                           "-r reverse sorting\n"
                           "-F types\n"
                           "-- after this all args considered to be files|dirs\n"<<std::endl;
                return 0;
            }
            else if(strcmp(argv[i],"-l")==0) flags.l=true;
            else if(strcmp(argv[i],"-R")==0) flags.R=true;
            else if(strcmp(argv[i],"-r")==0) flags.r=true;
            else if(strcmp(argv[i],"-F")==0) flags.F=true;
            else if(strcmp(argv[i],"--")==0) f=true;
            //processing sort
            else if(strstr(argv[i],"-sort")!= nullptr){
                std::vector<char> sort;
                char *ptr = strstr(argv[i],"=")+1;
                while(*ptr!= '\0'){
                    if(sorts.find(*ptr)!=std::string::npos && sortOk) {
                        flags.sort = *ptr;
                        ptr++;
                        sortOk = false;
                    }
                    else if(*ptr=='D'){
                        flags.D = true;
                        ptr++;
                    }
                    else if(*ptr=='s'){
                        flags.s = true;
                        ptr++;
                    }
                    else{
                        std::cerr<<"Invalid sorting criteria"<<std::endl;
                        return -3;
                    }
                }
                if(sort.size()>3){
                    std::cerr<<"Invalid sorting criteria"<<std::endl;
                    return -3;
                }
                sortOk = true;
            }
            else{
                std::cerr<<"Incorrect option"<<std::endl;
                return -1;
            }
        }
        //files
        else if(boost::filesystem::exists(BPath(std::string(argv[i])))){
            time_t sys_time{ boost::filesystem::last_write_time(BPath(argv[i])) };
            boost::posix_time::ptime p_time{ boost::posix_time::from_time_t(sys_time) };
            files.emplace_back(tuple(argv[i], filesize(argv[i]), p_time));
        }
        else{
            std::cerr<<argv[i]<<" file don`t exist"<<std::endl;
        }
    }
    if(files.empty()){
        auto currentPath = ".."+boost::filesystem::current_path().string().substr(boost::filesystem::current_path().string().find_last_of("/"));
        time_t sys_time{ boost::filesystem::last_write_time(BPath(currentPath)) };
        boost::posix_time::ptime p_time{ boost::posix_time::from_time_t(sys_time) };
        files.emplace_back(tuple(currentPath, filesize(currentPath), p_time));
    }

    sort(std::ref(flags), std::ref(files), "", false);

    return 0;
}
