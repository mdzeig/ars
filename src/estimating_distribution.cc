#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
#include "estimating_distribution.h"

double tangent_line::height(double y) const { 
	return fx + (y - x) * dfx; 
}

bool operator< (const tangent_line& t1, const tangent_line& t2) { 
	return t1.x < t2.x; 
}

// piece_boundary
piece_boundary::piece_boundary(const tangent_line& lower, 
								const tangent_line& upper) {
	
	loc = ( upper.fx - lower.fx - upper.x * upper.dfx
		+ lower.x * lower.dfx ) / (lower.dfx - upper.dfx);
	exp_hgt = std::exp( upper.height(loc) );
}

// function definitions for estimating_distribution
estimating_distribution::estimating_distribution (const tangent_set& inits) {
	
	if ( inits.size() < 3 )
		throw std::invalid_argument(
			"Must provide at least 3 initial values in 'inits'.");
	
	tangents = inits;
	
	// compute boundaries between pieces.
	auto lowtan = tangents.begin(), uptan = tangents.begin();
	for ( ++uptan; uptan != tangents.end(); ++lowtan, ++uptan )
		bnds.push_back( piece_boundary(*lowtan, *uptan) );
}

double estimating_distribution::quantile(double u) const {
	
	auto lowbnd = bnds.begin(), uppbnd = bnds.begin();
	auto tang = tangents.begin();
	
	// determine the integral over the exponential of the upper hull for
	// each piece of the estimating distribution	
	std::vector<double> piece_integral( tangents.size() );
	std::vector<double>::iterator curr_intg = piece_integral.begin();
	*curr_intg = uppbnd->exp_hgt / tang->dfx;
	auto total_integral = *curr_intg;

	for (++uppbnd, ++tang, ++curr_intg; 
		uppbnd != bnds.end(); 
		++lowbnd, ++uppbnd, ++tang, ++curr_intg ) {
		
		*curr_intg = tang->dfx > 0 ?
			(uppbnd->exp_hgt - lowbnd->exp_hgt) / tang->dfx :
			lowbnd->exp_hgt * (uppbnd->loc - lowbnd->loc);
		total_integral += *curr_intg;
	}

	*curr_intg = -lowbnd->exp_hgt / tang->dfx;
	total_integral += *curr_intg;
	
	// determine which piece u falls into
	u = total_integral * u;
	std::cout << "u = " << u << std::endl;
	tang = tangents.begin();
	auto running_total = 0.;
	for ( auto piece : piece_integral ) {
		running_total += piece;
		if ( running_total > u ) break;
		++tang;
	}
	
	std::cout << "Piece tangent: " << (--tang)->x << std::endl;
	
	std::cout << "Piece integrals:";
	for ( auto i : piece_integral )
		std::cout << "  " << i;
	std::cout << std::endl;
	
	return 0;
}

void estimating_distribution::print_state () const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Tangents:\nx\tfx\tdfx\n---\t---\t---\n";
	for ( auto t : tangents )
		std::cout << t.x << "\t" << t.fx << "\t" 
			<< t.dfx << std::endl;
	
	std::cout << "\nIntersections:\nloc\te height\n---\t---\n";
	for ( auto b : bnds )
		std::cout << b.loc << "\t" << b.exp_hgt << std::endl;
}