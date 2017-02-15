/*
 * MakeDir.h
 *
 *  Created on: Jan 30, 2017
 *      Author: diepbp
 */

#ifndef MAKEDIR_H_
#define MAKEDIR_H_

#include <iostream>
#include <string>
#include <sys/stat.h> // stat
#include <errno.h>    // errno, ENOENT, EEXIST
#if defined(_WIN32)
#include <direct.h>   // _mkdir
#endif

bool isDirExist(const std::string& path);

bool makePath(const std::string& path);

#endif /* MAKEDIR_H_ */
