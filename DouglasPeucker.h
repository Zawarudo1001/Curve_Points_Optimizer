#pragma once

#include <vector>
#include <deque>
#include <map>
#include <iterator>
#include <algorithm>
#include "2dOperations.h"

using namespace std;

void opt_curve(vector<vector<Point2d>> &pointList, double epsilon, map<Point2d, uint8_t> &Point_count);

vector<Point2d> RamerDouglasPeucker(vector<Point2d> &pointList, double epsilon);
