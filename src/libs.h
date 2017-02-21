/*
 * libs.h
 *
 *  Created on: Dec 8, 2016
 *      Author: diepbp
 */

#ifndef LIBS_H_
#define LIBS_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <pthread.h>
#include <sys/types.h>
#include <algorithm>
#include <time.h>

#include "TimeLapse.h"

//#define DEBUGLOG 1
#define REMOVINGLOG 1
//#define PRINTTEST_UNDERAPPROX 1
#define NUM_THREADS	16
#define FLATMAX 100;
#define PMAX 50 // size of a flat
#define QMAX 2 // number of flats
#define QCONSTMAX 2 // number of flats for const

#define Z3_PATH "z3 "
#define S3_PATH "fat/run.py "


#endif /* LIBS_H_ */
