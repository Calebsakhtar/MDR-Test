#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include "../headers/DesignClasses.h"

namespace MDR {
	bool A_dominates_B(const Design& A, const Design& B) {
		// Given two Designs A and B, return whether A dominates B in their active
		// performance metrics.

		const std::vector<size_t> active_perf_ids_A = A.get_active_perf_metric_ids();
		const std::vector<size_t> active_perf_ids_B = B.get_active_perf_metric_ids();

		// Verify that the performance ID's are the same
		assert(active_perf_ids_A[0] == active_perf_ids_B[0]);
		assert(active_perf_ids_A[1] == active_perf_ids_B[1]);

		const size_t first_metric_id = active_perf_ids_A[0];
		const size_t second_metric_id = active_perf_ids_A[1];

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

	bool is_pareto_edge(const Design& A, const Design& B) {
		// Given two consecutive designs from a list of designs, ordered by using dominance relations,
		// state whether these are part of the pareto front. (ONLY VALID AT THE EDGES).
		if (!A_dominates_B(A, B) && !A_dominates_B(B, A)) {
			return true;
		}
		return false;
	}

	bool is_pareto_mid(const Design& A, const Design& B, const Design& C) {
		// Given three consecutive designs from a list of designs, ordered by using dominance relations,
		// state whether these are part of the pareto front.
		if (is_pareto_edge(A, B) && is_pareto_edge(A, C)) {
			return true;
		}
		return false;
	}

	bool optimize_designs(std::vector<Design>& design_list, const std::vector<size_t>& perf_metric_id_order) {

		// Check the input order matches the design metric size
		assert(design_list[0].get_perf_vector().size() == perf_metric_id_order.size());

		for (size_t i = 1; i < design_list.size(); i++) {

			// Check all designs have the same number of performance metrics
			assert(design_list[i - 1].get_perf_vector().size() ==
				design_list[i].get_perf_vector().size());
		}

		std::vector<Design> result_designs = design_list; // Placeholder to store the resultant list

		// Set the active performance metrics at the start
		for (size_t j = 0; j < design_list.size(); j++) {
			result_designs[j].set_active_perf_metrics(perf_metric_id_order[0], perf_metric_id_order[1]);
		}

		// Loop over the dominance relations
		for (size_t i = 2; i < perf_metric_id_order.size(); i + 2) {

			// Sort the results vector according to the dominance relation of the previous metrics
			std::sort(result_designs.begin(), result_designs.end(), A_dominates_B);

			// Loop over the remaining designs
			for (size_t j = 0; j < result_designs.size(); j++) {

				if (j == 0) {
					if (!is_pareto_edge(result_designs[0], result_designs[1])) {
						std::erase(result_designs, result_designs[0]);
					}
				}
				else if (j == result_designs.size() - 1) {
					if (!is_pareto_edge(result_designs[j - 1], result_designs[j])) {
						std::erase(result_designs, result_designs[j]);
					}
				}
				else {
					if (!is_pareto_mid(result_designs[j - 1], result_designs[j], result_designs[j + 1])) {
						std::erase(result_designs, result_designs[j]);
					}
				}

				// Set the active performance metrics
				result_designs[j].set_active_perf_metrics(perf_metric_id_order[i], perf_metric_id_order[i + 1]);
			}
		}

		if (perf_metric_id_order.size() % 2 != 0) {

		}

		return true;
	}
}
