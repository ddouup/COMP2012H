#include "fast.h"
#include <algorithm>
using namespace std;

fast::fast() {}
fast::fast(const vector<point> p):points(p) {}
fast::~fast() {}

vector<vector<point> > fast::searchColinearPoints() {
	vector<point> line;
	vector<vector<point> > lines;
	vector<point> slopes;

	int n = points.size();
	bool judge = true;
	int i, j, p;
	for (i = 0; i < n; i++) {
		slopes.clear();
		for (j = 0; j < n; j++) {
			if (j != i)
			slopes.push_back(points[j]);
		}

		Slope origin(points[i]);
		sort(slopes.begin(), slopes.end(), origin);
		
		int cur = 0; 
		int count = 1;
		while (cur < n - 1) {
			while (cur + count < n && 
			  slopes[cur + count].getSlope(points[i]) == slopes[cur].getSlope(points[i])) {
				count++;
			}
			
			line.clear();
			if (count >= 3) {
				line.push_back(points[i]);
				for (p = cur; p < cur + count; p++) {
					line.push_back(slopes[p]);
				}
				sort(line.begin(), line.end());
				
				for (int a = 0; a < lines.size(); a++) {
					if (lines[a] == line)
						judge = false;
				}

				if(judge) 
					lines.push_back(line);
			}
			cur += count;
			count = 1;
			judge = true;
		}
	}
	print(lines);
	return lines;
}

void fast::print(vector<vector<point> > p) {
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