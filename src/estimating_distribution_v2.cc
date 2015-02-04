#include "estimating_distribution_v2.h"
#include <exception>

intersect( 	double lower_point, double upper_point,
			double lower_fun, double upper_fun,
			double lower_deriv, double upper_deriv) {

	return ( upper_fun - lower_fun - upper_point * upper_deriv +
		lower_point * lower_deriv ) / ( lower_deriv - upper_deriv );
}

estimating_distribution::estimating_distribution(
		std::initializer_list<double>& tangents,
		std::initializer_list<double>& fun_at_tangets,
		std::initializer_list<double>& deriv_at_tangents) {
			
	if ( tangents.size() < 3 )
		throw std::invalid_argument(
			"Must provide at least 3 initial values in 'inits'.");	
	
	if ( tangents.size() != fun_at_tangents.size() ||
			tangents.size() != deriv_at_tangents.size() )
		throw std::invalid_argument(
			"'tangents', 'fun_at_tangents' and 'deriv_at_tangents' must have equal sizes.")
	
	// compute the value at each
	auto curr_tang = tangents.begin(), curr_fun = fun_at_tangents.begin(),
		curr_deriv = deriv_at_tangents.begin();	
	auto next_tang = curr_tang, next_fun = curr_fun, next_deriv = curr_deriv;
	
	auto bnd_loc = intersect(*curr_tang, *curr_fun, *curr_deriv,
								*(++next_tang), *(++next_fun), *(++next_deriv))
	
	bnds.emplace( bnd_loc );
	
	// add the first segment into the hull.
	// TODO: implement an number of interval classes (bounded, bounded from below 
	// 		and bounded from above needed) to get around using infinity.
	hull.emplace( *curr_tang, 
				{ *curr_fun, *curr_deriv,
					std::exp( *curr_fun + *curr_deriv * (tang_isect - *curr_tang) ),
					INFINITY, bnd_loc } );
	
	// TODO: complete the algorithm for adding the tangent information to the hull.
	
	
	for ( ; curr_tang != tangents.end(); ++curr_tang, ++curr_fun, ++curr_deriv )
		hull.emplace( *curr_tang, segment_data(*curr_fun, *curr_deriv) );
	
	
	

	double fun_val, deriv_val;
	for ( double x : inits ) {
		eval_target (x, fun_val, deriv_val);
		hull.insert ( hull_element(x, {fun_val, deriv_val, 0., 0., 0.}) );
	}
	
	
}