#include <iostream>
#include <vector>
#include "estimating_distribution.h"

using namespace std;

double calc_fx (double x) { return -0.5 * x * x; }
double calc_dfx (double x) { return -x; }

int main() {
	
	vector<double> pts = {-1, 0, -2, 1};
	tangent_set inits;
	for ( auto x : pts )
		inits.insert( {x, calc_fx(x), calc_dfx(x)} );
	
	estimating_distribution distn(inits);
	
	cout << "--------------------------------------\n";
	cout << "State after ctor:\n";
	distn.print_state();
	cout << endl;
	distn.quantile(0.7);
	cout << "\nDone\n";
/*	
	pts.clear();
	pts.insert(pts.begin(), {2, 1, -3});
	for ( auto x : pts ) {
		distn.insert_point(x, calc_fx(x), calc_dfx(x));
		cout << "--------------------------------------\n";
		cout << "State after inserting " << x << ":\n";
		distn.print_state();
		cout << endl;
	}
	
	cout << "Test of upper_hull:\n";
	vector<double> hull_pts = {-2.6, -0.9, 0.1, 1.2, 2.6};
	for ( auto x : hull_pts )
		cout << "x=" << x << ", uh=" << distn.upper_hull(x) << endl;
	
	cout << "\nTest of lower_hull:\n";
	double lh;
	for ( auto x : hull_pts ) {
		try {
			lh = distn.lower_hull(x);
		} catch (const std::invalid_argument& ia) {
			continue;
		}
		
		cout << "x=" << x << ", lh=" << lh << endl;
	}
*/	
	return 0;
}