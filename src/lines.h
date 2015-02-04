#ifndef __LINES_H__
#define __LINES_H__

/* tangent line.  x is tangent point, fx is function value at tangent
	point and dfx is derivative value at tangent point */
class tangent_line {
public:
	tangent_line (double x, double fx, double dfx);
	
	// height of tangent line @ y.
	double height(double y) const;
	
	double get_x() const;
	double get_fx() const;
	double get_dfx() const;
	
private:
	double x, fx, dfx;
};

// order tangent lines based on their tangent point, x.
bool operator< (const tangent_line& t1, const tangent_line& t2);

/* boundary between pieces of piecewise estimating distribution.
	loc is the location of the boundary, upper_exp is the value of 
	exponential of the tangent line for which loc is the upper boundary
	and lower_exp is the same for the tangent line for which loc is the
	lower boundary */
struct piece_boundary {
public:
	piece_boundary(const tangent_line& lower, const tangent_line& upper);
	
	double get_loc() const;
	double get_exp_height() const;
	
private:
	double loc, exp_height;
	
};

bool operator< (const piece_boundary& b1, const piece_boundary& b2);

#endif