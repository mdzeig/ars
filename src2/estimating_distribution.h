#ifndef __ESTIMATING_DISTRIBUTION_H__
#define __ESTIMATING_DISTRIBUTION_H__

#include <functional>
#include <initializer_list>
#include <map>

typedef std::function<void(double, double&, double&)> ars_target_evaltr;

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
	estimating_distribution(ars_target_evaltr eval_target,
							std::initializer_list<double>& tangents);

private:
	convex_hull hull;
	partition_of_reals partition;
	ars_target_evaltr eval_target;
};

#endif