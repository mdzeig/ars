#include <cmath>
#include "lines.h"

// tangent_line
tangent_line::tangent_line (double x, double fx, double dfx) : 
	x(x), fx(fx), dfx(dfx) {}

double tangent_line::height(double y) const { 
	return fx + (y - x) * dfx; 
}

double tangent_line::get_x() const { return x; }
double tangent_line::get_fx() const { return fx; }
double tangent_line::get_dfx() const { return dfx; }

bool operator< (const tangent_line& t1, const tangent_line& t2) { 
	return t1.get_x() < t2.get_x(); 
}

// piece_boundary
piece_boundary::piece_boundary(const tangent_line& lower, 
								const tangent_line& upper) {
	
	loc = ( upper.get_fx() - lower.get_fx() - upper.get_x() * upper.get_dfx() 
		+ lower.get_x() * lower.get_dfx() ) / (lower.get_dfx() - upper.get_dfx());
	exp_height = std::exp( upper.height(loc) );
}

double piece_boundary::get_loc() const { return loc; }
double piece_boundary::get_upper_exp() const { return upper_exp; }
double piece_boundary::get_lower_exp() const { return lower_exp; }

// functions for piece_boundary
bool operator< (const piece_boundary& b1, const piece_boundary& b2) {
	return b1.get_loc() < b2.get_loc();
}