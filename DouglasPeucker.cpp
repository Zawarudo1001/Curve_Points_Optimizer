#pragma once

#include "DouglasPeucker.h"

void opt_curve(vector<vector<Point2d>> &pointList, double epsilon, map<Point2d, uint8_t> &Point_count) {
	for (auto &plist : pointList) {
		
		vector<Point2d> filt_sub;
		filt_sub.push_back(plist[0]);
		size_t s = plist.size();
		deque<vector<Point2d>> dq;

		unsigned int startIndex = 0;
		for (unsigned int index = startIndex; index < s; index++) {
			if (Point_count[plist[index]] > 1 && index != startIndex) {		//нашли точку, в которой будут разделяться подпоследовательности, 
				vector<Point2d> vect(plist.begin() + startIndex, plist.begin() + index + 1);
				dq.emplace_back(vect);
				startIndex = index;
			}
		}
		while (!dq.empty()) {
			auto temp = dq.front();
			auto reduced = RamerDouglasPeucker(temp, epsilon);
			copy(reduced.begin() + 1, reduced.end(), back_inserter(filt_sub));
			dq.pop_front();
		}
		plist = filt_sub;
	}
};


vector<Point2d> RamerDouglasPeucker(vector<Point2d> &pointList, double epsilon)
{
	vector<Point2d> out;
	float dmax = 0.0;
	size_t index = 0;
	size_t end = pointList.size() - 1;
	for (size_t i = 1; i < end; i++)
	{
		float d = length(FindPerp(pointList[0], pointList[end], pointList[i]));
		if (d > dmax)
		{
			index = i;
			dmax = d;
		}
	}
	if (dmax > epsilon)
	{
		// Recursive call
		vector<Point2d> firstLine(pointList.begin(), pointList.begin() + index + 1);
		vector<Point2d> lastLine(pointList.begin() + index, pointList.end());

		vector<Point2d> recResults1 = RamerDouglasPeucker(firstLine, epsilon);
		vector<Point2d> recResults2 = RamerDouglasPeucker(lastLine, epsilon);

		// Build the result list
		out.assign(recResults1.begin(), recResults1.end() - 1);
		out.insert(out.end(), recResults2.begin(), recResults2.end());
	}
	else
	{
		out.clear();
		out.push_back(pointList[0]);
		out.push_back(pointList[end]);
	}
	return out;
}