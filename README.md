# LCSS - An implementation of LCSS Algorithm written in php-cpp 

This is a simple implementation of the [LCSS Algorithm](http://www.cs.bu.edu/groups/dblab/pub_pdfs/icde02.pdf), written in [php-cpp](php-cpp.com), in order to 
get better performance compared with a pure PHP implementation.

## Installation

1. Edit Makefile and set `INI_DIR` to the directory that holds your `.ini` files.
2. `make && sudo make install`

## Usage (PHP side)

```PHP
LCSS( double epsilon [, double delta ] )
```
*  The constant epsilon is the matching threshold (value between 0 and 1)

* The constant delta controls how far in time we can go in order to
match a given point from one trajectory to a point in another
trajectory.

```PHP
double LCSS::findSimilarity( array trajectory1Lat, array trajectory1Lng, array trajectory2Lat, array trajectory2Lng )
```
* Currently Similarity Measures/ Similarity Function 1 is used.
