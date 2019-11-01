//
// Created by vaitovych on 01.11.19.
//

#ifndef MYLS_PRINT_H
#define MYLS_PRINT_H

#include "config.h"

size_t filesize(std::string path);

void recursivePrint(flags_t &flags, std::vector<tuple> &regulars, std::vector<tuple> &dirs, std::vector<tuple> &special, std::string &currentPath);


#endif //MYLS_PRINT_H
