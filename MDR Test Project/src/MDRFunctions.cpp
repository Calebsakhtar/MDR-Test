#include <vector>
#include <algorithm>
#include <assert.h>
#include "../headers/DesignClasses.h"

bool A_dominates_B(const MDR::Design& A, const MDR::Design& B) {

	const std::vector<size_t> active_perf_ids_A = A.get_active_perf_metric_ids();
	const std::vector<size_t> active_perf_ids_B = B.get_active_perf_metric_ids();

	// Verify that the performance ID's are the same
	assert(active_perf_ids_A[0] == active_perf_ids_B[0]);
	assert(active_perf_ids_A[1] == active_perf_ids_B[1]);

	const double first_metric_id = active_perf_ids_A[0];
	const double second_metric_id = active_perf_ids_A[1];

	// Retrieve the values of the first performance metric
	double first_perf_val_A = 0;
	double first_perf_val_B = 0;
	assert(A.get_perf_val(first_metric_id, first_perf_val_A)); // Check OK ID
	assert(B.get_perf_val(first_metric_id, first_perf_val_B)); // Check OK ID

	// Find out whether this value is to be minimized or maximized
	bool first_minimize_A = true;
	bool first_minimize_B = true;
	A.get_perf_minimize(first_metric_id, first_minimize_A);
	B.get_perf_minimize(first_metric_id, first_minimize_B);
	assert(first_minimize_A == first_minimize_B); // Check for errors in minimize

	// Retrieve the values of the second performance metric
	double second_perf_val_A = 0;
	double second_perf_val_B = 0;
	assert(A.get_perf_val(second_metric_id, second_perf_val_A)); // Check OK ID
	assert(B.get_perf_val(second_metric_id, second_perf_val_B)); // Check OK ID

	// Find out whether this value is to be minimized or maximized
	bool second_minimize_A = true;
	bool second_minimize_B = true;
	A.get_perf_minimize(second_metric_id, second_minimize_A);
	B.get_perf_minimize(second_metric_id, second_minimize_B);
	assert(second_minimize_A == second_minimize_B); // Check for errors in minimize

	// Evaluate the dominance relation

	bool first_dominance = false;
	if (first_minimize_A) {
		first_dominance = first_perf_val_A < first_perf_val_B;
	}
	else {
		first_dominance = first_perf_val_A > first_perf_val_B;
	}

	bool second_dominance = false;
	if (second_minimize_A) {
		second_dominance = second_perf_val_A < second_perf_val_B;
	}
	else {
		second_dominance = second_perf_val_A > second_perf_val_B;
	}

	return first_dominance && second_dominance;
}
