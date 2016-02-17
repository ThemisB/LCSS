#include "LCSS.h"

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
			double lat1,lat2,lng1,lng2;
			lat1 = trajectory1Lat[i];
			lat2 = trajectory2Lat[j];

			int retval = compareCoordinates(lat1, lat2);
			bool equalsLatitude = true;
			if (retval == 1) {
				equalsLatitude = compareCoordinates(lat1, lat2 + _epsilon) <= 0;
			} else if (retval == -1) {
				equalsLatitude = compareCoordinates(lat2, lat1 + _epsilon) <= 0;
			}

			if (!equalsLatitude) {
				if (lengths[i+1][j] > lengths[i][j+1]) {
					lengths[i+1][j+1] = lengths[i+1][j];
				} else {
					lengths[i+1][j+1] = lengths[i][j+1];
				}
				continue;
			}

			lng1 = trajectory1Lng[i];
			lng2 = trajectory2Lng[j];

			retval = compareCoordinates(lng1, lng2);
			bool equalsLongitude = true;
			if (retval == 1) {
				equalsLongitude = compareCoordinates(lng1, lng2 + _epsilon) <= 0;
			} else if (retval == -1) {
				equalsLongitude = compareCoordinates(lng2, lng1 + _epsilon) <= 0;
			}

			if ((equalsLongitude && _delta == 0) || (equalsLongitude && abs(n-i-(m-j)) <= _delta)){
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

	std::vector<int> lcss_vector;
	int x = n,y = m;

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

int LCSS::compareCoordinates(double x, double y) {
	if (x > y)
		return 1;
	else if (x < y)
		return -1;
	return 0;
}

