#include "FileParser.h"
#include "DouglasPeucker.h"


using namespace std;

void print_map(map<Point2d, uint8_t> const &m)
{
	for (auto const &pair : m) {
		printf("{%.12f %.12f} -> %d\n", pair.first.x, pair.first.y, pair.second);
	}
	printf("\n\n");
}

void print_vect2(vector<vector<Point2d>> vect) {
	for (auto const &i : vect) {
		for (auto const &k : i) {
			printf("%.12f %.12f\n", k.x, k.y);
		}
		printf("\n");
	}
}


int main()
{
	File file;
	file.openfile("temp.txt", "r+");

	vector<vector<Point2d>> points;
	map<Point2d, uint8_t> Point_count;

	file.parse_flt_data(points, Point_count);

 	fclose(file.mainfile);

	print_map(Point_count);

	opt_curve(points, 0.5, Point_count);

	print_vect2(points);

	return 0;
}
