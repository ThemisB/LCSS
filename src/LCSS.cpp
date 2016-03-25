#include "LCSS.h"
#include <math.h>

using namespace std;

/* Php Parameters available are epsilon and the optional delta. */

LCSS::LCSS() {}
LCSS::~LCSS() {}

void LCSS::__construct(Php::Parameters &params) {
	if (params.size() < 1) {
		throw Php::Exception("You should declare epsilon ");
	}

	if (params[0] < 0 || params[0] > 1) {
		throw Php::Exception("Epsilon should be between 0 and 1");
	}

	_epsilon = params[0];

	if (params.size() > 1 && params[1] > 0) {
		_delta = params[1];
	} else {
		_delta = 0.0;
	}
}


Php::Value LCSS::findSimilarity(Php::Parameters &params) {
	if (params.size() != 4) {
		throw Php::Exception("Invalid number of parameters given");
	}

	else if ( (params[0].size() != params[1].size()) || (params[2].size() != params[3].size()) ) {
		throw Php::Exception("Latitude/Longtitude number are different");
	}

	vector<double> trajectory1Lat = params[0];
	vector<double> trajectory1Lng = params[1];
	vector<double> trajectory2Lat = params[2];
	vector<double> trajectory2Lng = params[3];

	/*initialize lengths array*/
	int n =  trajectory1Lat.size();
	int m =  trajectory2Lat.size();

	vector< vector<int> > lengths(n+1,vector<int>(m+1));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			if (abs(i-j) > _delta) {
				if (lengths[i+1][j] > lengths[i][j+1]) {
					lengths[i+1][j+1] = lengths[i+1][j];
				} else {
					lengths[i+1][j+1] = lengths[i][j+1];
				}
				continue;
			} 

			double lat1,lat2,lng1,lng2;
			lat1 = trajectory1Lat[i];
			lat2 = trajectory2Lat[j];
			lng1 = trajectory1Lng[i];
			lng2 = trajectory2Lng[j];
			if (distance(lat1,lat2,lng1,lng2)) {
				lengths[i+1][j+1] = lengths[i][j] + 1;
			} else {
				if (lengths[i+1][j] > lengths[i][j+1]) {
					lengths[i+1][j+1] = lengths[i+1][j];
				} else {
					lengths[i+1][j+1] = lengths[i][j+1];
				}
			}
		}
	}

	vector<int> lcss_vector;
	int x = n, y = m;

	while (x != 0 && y !=0) {
		if (lengths[x][y] == lengths[x-1][y]) {
			x--;
		} else if (lengths[x][y] == lengths[x][y-1]) {
			y--;
		} else {
			lcss_vector.push_back(lengths[x][y]);
			x--;
			y--;
		}
	}
	if (lcss_vector.size()) {
		return (double)*max_element(lcss_vector.begin(),lcss_vector.end())/(double)min(n,m);
	}
	return 0;
}

double LCSS::distance(double x1, double x2, double y1, double y2) {
	double R = 6371.0; // km
	double dLat = (x2-x1)*((double)(M_PI/180.0));
	double dLon = (y1-y2)*((double)(M_PI/180.0));
	double a = sin((double)(dLat/2)) * sin((double)(dLat/2)) +
	       cos(x1*((double)(M_PI/180.0))) * cos(x2*((double)(M_PI/180.0))) *
	       sin((double)(dLon/2)) * sin((double)(dLon/2));
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	return R * c < _epsilon;

	// return ( sqrt ( (x1 - x2) * ( x1 - x2 ) + (y1 - y2) * (y1 - y2) ) < _epsilon );
}

