#include <functional>
#include <iostream>

using namespace std;

void normal_target_fun (double x, double& fx, double& dfx, double prec) {
	fx = -0.5 * prec * x * x;
	dfx = -prec * x;
}

// simple version of R's do.call
void eval_target (function<void(double, double&, double&)> target_fun, 
			 	  double x, double& fx, double& dfx) {
  target_fun(x, fx, dfx);
}

int main() {
	// auto bound_target = [](double x, double& fx, double& dfx) {
	// 	normal_target_fun(x, fx, dfx, 1.);
	// };
	
	double prec = 1;
	auto target_fun = [&prec] (double x, double& fx, double& dfx) {
		normal_target_fun(x, fx, dfx, prec);
	};
	
	double x = -2., fx, dfx;
	eval_target(target_fun, x, fx, dfx);
	cout << "prec=" << prec << ": " << x << "  " << fx << "  " << dfx << endl;
	
	prec = 0.5;
	eval_target(target_fun, x, fx, dfx);
	cout << "prec=" << prec << ": " << x << "  " << fx << "  " << dfx << endl;
	
	return 0;
}
