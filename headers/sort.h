//
// Created by vaitovych on 01.11.19.
//

#ifndef MYLS_SORT_H
#define MYLS_SORT_H

#include "config.h"

bool sortByName(tuple first, tuple second);

bool sortBySize(tuple first, tuple second);

bool sortByTime(tuple first, tuple second);

bool sortByExtension(tuple first, tuple second);

std::vector<std::vector<tuple>> sort(flags_t &flags, std::vector<tuple> &files, std::string currentPath, bool ret);

#endif //MYLS_SORT_H


