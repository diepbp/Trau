/*
 * MakeDir.h
 *
 *  Created on: Jan 30, 2017
 *      Author: diepbp
 */

#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <iostream>
#include <string.h>
#include <sys/stat.h> // stat
#include <errno.h>    // errno, ENOENT, EEXIST
#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32)
#include <direct.h>   // _mkdir
#endif

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define LOGFILE ".trauLog"
#define LOGAXIOMFILE ".z3Log"
#define TMPDIR "/tmp/fat_str_convert"
#define NONGRM "_trau_nogrm_"
#define OUTPUT "_trau_output_"
#define WITHLENGH "_trau_w_l_"
#define CONVERTED "_trau_converted_"

bool isDirExist(const std::string& path);

bool makePath(const std::string& path);

void removeFiles(const std::string& fileName);

void rmTree(const char path[]);

void removeLog();

void cleanOldLog();

#endif /* FILEUTILS_H_ */
