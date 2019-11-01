//
// Created by vaitovych on 28.10.19.
//

#ifndef MYLS_CONFIG_H
#define MYLS_CONFIG_H

#include <string>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <boost/filesystem.hpp>

typedef struct {

    bool l = false;
    bool D = false;
    bool s = false;
    char sort = 'N';
    std::vector<std::tuple<std::string, size_t ,boost::posix_time::ptime>> files;
    std::vector<std::string> special;
    std::vector<std::string> dirs;
    bool r;
    bool F;
    bool R;

} flags_t;

typedef std::tuple<std::string, size_t, boost::posix_time::ptime> tuple;
typedef boost::filesystem::path BPath;


#endif //MYLS_CONFIG_H
