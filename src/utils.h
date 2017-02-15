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

std::vector<std::string> parse_string_language(std::string s, std::string delimiters);
std::string getFileNameFromFileDir(std::string fileDir);
#endif /* UTILS_H_ */
