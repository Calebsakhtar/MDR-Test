#include <vector>
#include <algorithm>
#include <assert.h>
#include "../headers/DesignClasses.h"

bool A_dominates_B(const MDR::Design& A, const MDR::Design& B, const size_t&
	first_metric_id, const size_t& second_metric_id) {

	double first_perf_val_A = 0;
	double first_perf_val_B = 0;
	assert(A.get_perf_val(first_metric_id, first_perf_val_A)); // Check OK ID
	assert(B.get_perf_val(first_metric_id, first_perf_val_B)); // Check OK ID

	bool first_minimize_A = true;
	bool first_minimize_B = true;
	A.get_perf_minimize(first_metric_id, first_minimize_A);
	B.get_perf_minimize(first_metric_id, first_minimize_B);
	assert(first_minimize_A == first_minimize_B); // Check for errors in minimize

	double second_perf_val_A = 0;
	double second_perf_val_B = 0;
	assert(A.get_perf_val(second_metric_id, second_perf_val_A)); // Check OK ID
	assert(B.get_perf_val(second_metric_id, second_perf_val_B)); // Check OK ID

	bool second_minimize_A = true;
	bool second_minimize_B = true;
	A.get_perf_minimize(second_metric_id, second_minimize_A);
	B.get_perf_minimize(second_metric_id, second_minimize_B);
	assert(second_minimize_A == second_minimize_B); // Check for errors in minimize

}
