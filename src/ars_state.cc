#include <algorithm>
#include <exception>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <vector>
#include "ars_state.h"

// function definitions for estimating_distribution
estimating_distribution::estimating_distribution (const tangent_set& inits) {
	
	if ( inits.size() < 3 )
		throw std::invalid_argument(
			"Must provide at least 3 initial values in 'inits'.");
	
	tangents = inits;
	
	// compute boundaries between pieces.
	auto lowtan = tangents.begin(), uptan = tangents.begin();
	for ( ++uptan; uptan != tangents.end(); ++lowtan, ++uptan )
		bnds.emplace(*lowtan, *uptan);
}


void estimating_distribution::insert_point (double x, double fx, double dfx) {
	
	// when there are > 2 tangents, processing depends whether the inserted
	// tangent is the minimum, maximum or somewhere in between
	auto empl_res = tangents.emplace(x, fx, dfx);
	if ( empl_res.first == tangents.begin() ) {
		// if inserted tangent is the minimum, we just need to intersect it
		// with the old minimum
		auto upper = empl_res.first;
		bnds.emplace( *empl_res.first, *(++upper) );
	} else if ( distance(empl_res.first, tangents.end()) == 1 ) {
		// if the inserted tangent is the maximum, we just need to intersect it
		// with the old maximum.
		auto lower = empl_res.first;
		bnds.emplace( *(--lower), *empl_res.first );
	} else {
		// otherwise, we need to erase the intersect between the largest value less
		// than and smallest value greater than the inserted value, and compute the
		// two new intersections.
		auto lower = empl_res.first, upper = empl_res.first;
		auto erase_pos = bnds.begin();
		std::advance(erase_pos, std::distance(tangents.begin(), --lower));
		bnds.erase(erase_pos);
		bnds.emplace_hint(--erase_pos, *lower, *upper);
		bnds.emplace_hint( ++erase_pos, *(++lower), *(++upper) );
	}
}

double estimating_distribution::upper_hull (double y) const {
	
	if ( y < bnds.rbegin()->get_loc() ) {
		auto t = tangents.begin();
		for ( auto b : bnds ) {
			if ( y < b.get_loc() ) break;
			++t;
		}
		return t->height(y);
	}
	
	return tangents.rbegin()->height(y); 
}

// still untested.
double estimating_distribution::lower_hull (double y) const {
	
	if ( y < tangents.begin()->get_x() || y > tangents.rbegin()->get_x() )
		throw std::invalid_argument(
			"Evaluating lower hull at 'y' results in infinite value.");
	
	auto lower = tangents.begin(), upper = tangents.begin();
	++upper;
	for ( ; upper->get_x() < y; ++upper, ++lower);
	return ( (upper->get_x() - y) * lower->get_fx() + 
		(y - lower->get_x()) * upper->get_fx() ) / 
			(upper->get_x() - lower->get_x()); 
}

double estimating_distribution::quantile(double u) const {
	
/*	auto lowbnd = bnds.begin(), upbnd = bnds.begin();
	std::vector<double> piece_cdf;
	piece_cdf.push_back( upbnd->get_lower_exp() );
	for ( ++upbnd ; upbnd != bnds.end(); ++lowbnd, ++upbnd )
		piece_cdf.push_back( upbnd->get_lower_exp() - lowbnd->get_upper_exp() );
	
	piece_cdf.push_back( -lowbnd->get_lower_exp() );
	auto integral = std::accumulate(changes.begin(), changes.end(), 0.); */
	
	
	return 0;
}

void estimating_distribution::print_state () const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Tangents:\nx\tfx\tdfx\n---\t---\t---\n";
	for ( auto t : tangents )
		std::cout << t.get_x() << "\t" << t.get_fx() << "\t" 
			<< t.get_dfx() << std::endl;
	
	std::cout << "\nIntersections:\nloc\tu exp\tl exp\n---\t---\t---\n";
	for ( auto b : bnds )
		std::cout << b.get_loc() << "\t" << b.get_upper_exp()
			<< "\t" << b.get_lower_exp() << std::endl;
	
	std::cout << "Piece Integrals:  ";
	for ( auto i : piece_integrals )
		std::cout << i << "  ";
	std::cout << std::endl;
}