#ifndef LCSS_H
#define LCSS_H

#include <phpcpp.h>
#include <iostream>
#define LCSS_EXTNAME "LCSS"
#define LCSS_EXTVERSION "1.0"
#define ALLOCATION_ERROR(X) if (X == NULL) { \
							perror("allocation error"); \
							exit(EXIT_FAILURE);} \

class LCSS : public Php::Base{
private:
	double _epsilon;
 	double _delta;
	int compareCoordinates(double, double);
public:
	LCSS();
	virtual ~LCSS();
	void __construct(Php::Parameters &);
	Php::Value findSimilarity(Php::Parameters &);
};

// Php::Value lcss_similarity(Php::Parameters &);

#endif