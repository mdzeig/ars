#ifndef __ESTIMATING_DISTRIBUTION_H__
#define __ESTIMATING_DISTRIBUTION_H__

#include <list>
#include <set>

// tangent line data container
struct tangent_line {
	double x, fx, dfx;
	double height(double y) const;
};

// compare tangent lines on their x location.
bool operator<(const tangent_line& t1, const tangent_line& t2);
typedef std::set<tangent_line> tangent_set;

// boundary between hull pieces
struct piece_boundary {
	double loc, exp_hgt;
	piece_boundary(const tangent_line& lower, const tangent_line& upper);
};

/* Estimating distribution used for ARS. */
class estimating_distribution {
public:
	
	estimating_distribution(const tangent_set& inits);
	
	// calculate the quantile of the estimating distribution for 0 < u < 1.
	double quantile (double u) const;
	
	// print out current state (for debugging purposes)
	void print_state () const;
	
private:
	tangent_set tangents;
	std::list<piece_boundary> bnds;
};

#endif