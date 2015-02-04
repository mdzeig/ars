#ifndef __ESTIMATING_DISTRIBUTION_H__
#define __ESTIMATING_DISTRIBUTION_H__

#include <initializer_list>
#include <map>
#include <memory>

// move to a different header file.
// partition.h perhaps.
#include <exception>

class interval {
public:
	virtual bool has_low_bnd() const = 0;
	virtual bool has_upp_bnd() const = 0;
	virtual double get_low_bnd() const = 0;
	virtual double get_upp_bnd() const = 0;
};

class bounded_interval : public interval {
public:
	bounded_interval(double low_bnd, double upp_bnd);
	bool has_low_bnd() const { return true; }
	bool has_upp_bnd() const { return true; }
	double get_low_bnd() const { return low_bnd; }
	double get_upp_bnd() const { return upp_bnd; }

private:
	double low_bnd, upp_bnd;
};

class lower_bounded_interval : public interval {
public:
	lower_bounded_interval(double low_bnd);
	bool has_low_bnd() const { return true; }
	bool has_upp_bnd() const { return false; }
	double get_low_bnd() const { return low_bnd; }
	double get_upp_bnd() const 
		{ throw std::runtime_error("Interval has no upper bound.") }

private:
	double low_bnd;
};

class upper_bounded_interval : public interval {
public:
	upper_bounded_interval(double upp_bnd);
	bool has_low_bnd() const { return false; }
	bool has_upp_bnd() const { return true; }
	double get_low_bnd() const 
		{ throw std::runtime_error("Interval has no lower bound.") }
	double get_upp_bnd() const { return upp_bnd; }
	
private:
	double upp_bnd;
};

typedef std::shared_ptr<interval> interval_ptr;

bool operator<( const interval_ptr& ival1, const interval_ptr& ival2) {
	return ival1->has_upp_bnd() && ival2->has_low_bnd() 
			&& ival1->get_upp_bnd() < ival2->get_low_bnd();
}

typedef std::set<interval_ptr> partition_of_reals;

// ------------------------------------


// possibly another header?
struct segment_data {
	double fun_val, deriv_val, integral;
	interval_ptr ival_ptr;
};

typedef std::map<double, segment_data> convex_hull;

double intersect(	double lower_point, double upper_point,
					double lower_fun, double upper_fun,
					double lower_deriv, double upper_deriv );



// struct boundary_data {
// 	double low_tan_pt, upp_tan_pt, exp_hgt;
// };

class estimating_distribution {

public:
	estimating_distribution(std::initializer_list<double>& tangents,
							std::initializer_list<double>& fun_at_tangets,
							std::initializer_list<double>& deriv_at_tangents);

private:
	convex_hull hull;
	partition_of_reals partition;
};

#endif