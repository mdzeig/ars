#ifndef __ARS_STATE_H__
#define __ARS_STATE_H__

#include <list>
#include <set>
#include "lines.h"

typedef std::set<tangent_line> tangent_set;

/* Estimating distribution used for ARS. */
class estimating_distribution {
public:
		
	estimating_distribution(const tangent_set& inits);
		
	// insert a value into the state.
	void insert_point (double x, double fx, double dfx);

	// calculate the upper hull [u_k in Gilks & Wild]
	double upper_hull (double y) const;
	
	// calculate the lower hull [l_k in Gilks & Wild]
	double lower_hull (double y) const;
	
	// calculate the quantile of the piecewise hull for 0 < u < 1.
	double quantile (double u) const;
	
	// print out current state (for debugging purposes)
	void print_state () const;
   
private:
	tangent_set tangents;
	std::set<piece_boundary> bnds;
	std::list<double> piece_integrals;
};

#endif






