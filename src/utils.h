/*
 * utils.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <assert.h>

#include <stack>
#include <set>
#include <list>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

#include <fst/fstlib.h>

#include <fstream>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

#include "TimeLapse.h"

#define DEBUGLOG 1
#define REMOVINGLOG 1
#define PRINTTEST_UNDERAPPROX 1
#define NUM_THREADS	16
#define FLATMAX 100;
#define PMAX 50 // size of a flat
#define QMAX 2 // number of flats
#define QCONSTMAX 2 // number of flats for const

#define Z3_PATH "z3 "
#define S3_PATH "fat/run.py "

#define TMPDIR "/tmp/fat_str_convert/"

#ifdef DEBUGLOG
  #define __debugPrint(_fp, _format, ...) { fprintf( (_fp), (_format), ##__VA_ARGS__); fflush( (_fp) ); }
	#define __debugPrintAxiom(_fp, _format, ...) { fprintf( (_fp), (_format), ##__VA_ARGS__); fflush( (_fp) ); }
  #define printZ3Node(t, n) {__printNode( (t), (n));}
	#define printZ3NodeAxiom(t, n) {__printNodeAxiom( (t), (n));}
#else
  #define __debugPrint(_fp, _format, ...) {}
  #define printZ3Node(t, n) {}
#endif

extern FILE * logFile;
extern FILE * logAxiom;

int lcd(int x, int y);

std::vector<std::string> parse_string_language(std::string s, std::string delimiters);

std::string parse_regex_content(std::string str);

std::string getFileNameFromFileDir(std::string fileDir);

void displayListString(std::vector<std::string> l, std::string msg);

void displayListString(std::set<std::string> l, std::string msg);

void displayListString(std::map<std::string, int> l, std::string msg);

void displayListNumber(std::set<int> l, std::string msg);

void displayListNumber(std::vector<int> l, std::string msg);
#endif /* UTILS_H_ */
