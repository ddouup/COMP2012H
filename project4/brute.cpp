#include "brute.h"
#include <algorithm>
using namespace std;

brute::brute(){}
brute::brute(const vector<point> p) :points(p) {}
brute::~brute(){}

vector<vector<point> > brute::searchColinearPoints() {
	vector<vector<point> > lines;
	vector<point> line;
	sort(points.begin(), points.end());

	int n = points.size();

	int i, j, p, q;
	for (i = 0; i < n - 3; i++) {
		for (j = i + 1; j < n - 2; j++) {
			for (p = j + 1; p < n - 1; p++) {
				for (q = p + 1; q < n; q++) {
					if (check(i, j, p, q)) {
						line.clear();
						line.push_back(points[i]);
						line.push_back(points[j]);
						line.push_back(points[p]);
						line.push_back(points[q]);

						lines.push_back(line);
					}
				}
			}
		}
	}
	print(lines);
	return lines;
}


bool brute::check(int i, int j, int p, int q) {
	double slope1 = points[j].getSlope(points[i]);
	double slope2 = points[p].getSlope(points[i]);
	double slope3 = points[q].getSlope(points[i]);
	if (slope1 == slope2 && slope1 == slope3) return true;
	else return false;
}

void brute::print(vector<vector<point> > p) {
	int i,j;
	for (i = 0; i < p.size(); i++){
		cout << p[i].size() << ":";
		for (j = 0; j < p[i].size(); j++){
			if (j != 0)
				cout << "->";
			cout << p[i][j];  
		}
		cout << endl;
	}
}