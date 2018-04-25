/*
 * MakeDir.h
 *
 *  Created on: Jan 30, 2017
 *      Author: diepbp
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <iostream>
#include <string>
#include <sys/stat.h> // stat
#include <errno.h>    // errno, ENOENT, EEXIST
#include <stdio.h>
#if defined(_WIN32)
#include <direct.h>   // _mkdir
#endif

#define LOGFILE ".trauLog"
#define LOGAXIOMFILE ".z3Log"

bool isDirExist(const std::string& path);

bool makePath(const std::string& path);

void removeFile(const std::string& fileName);

void removeLog();

#endif /* FILEUTILS_H_ */
