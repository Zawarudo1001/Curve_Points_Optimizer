#pragma once

#include <vector>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include "2dOperations.h"
#include "2dTypes.h"

#define LAST true
#define FIRST false
#define PARSE_ERR -1


typedef unsigned long ulong;
using namespace std;


struct File {
	FILE* mainfile;
	int fopenerror;
	ulong fsize = 0;

	int openfile(const char* name, const char* mode);

	ulong getfilesize(FILE* file);

	ulong parse_file(ulong start, const char* pattern, int size, bool last);

	void parse_flt_data(vector<vector<Point2d>> &points, map<Point2d, uint8_t> &Point_count);
	
};
