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
			// If the 1st value is to be minimized, check whether A's 1st value is the smaller one.
			first_dominance = first_perf_val_A < first_perf_val_B;
		}
		else {
			// Otherwise, check whether A's 1st value is the larger one.
			first_dominance = first_perf_val_A > first_perf_val_B;
		}

		bool second_dominance = false;
		if (second_minimize_A) {
			// If the 2nd value is to be minimized, check whether A's 2nd value is the smaller one.
			second_dominance = second_perf_val_A < second_perf_val_B;
		}
		else {
			// Otherwise, check whether A's 2nd value is the larger one.
			second_dominance = second_perf_val_A > second_perf_val_B;
		}

		// MDR considers relations in pairs (this is the smart bit)
		return first_dominance && second_dominance;
	}

	bool is_pareto_edge(const Design& A, const Design& B) {
		// Given two consecutive designs from a list of designs, ordered by using dominance relations,
		// state whether A is part of the pareto front. (ONLY VALID AT THE EDGES OF THE LIST).
		if (!A_dominates_B(A, B) && !A_dominates_B(B, A)) {
			return true;
		}
		return false;
	}

	bool is_pareto_mid(const Design& A, const Design& B) {
		// Given two consecutive designs from a list of designs, ordered by using dominance relations,
		// state whether B is part of the pareto front given that A is part of the pareto front.
		if (!A_dominates_B(A, B)) {
			return true;
		}
		return false;
	}

	void remove_non_pareto_designs(std::vector<Design>& design_list) {
		// Given a list of designs, previously ordered by using dominance relations, remove those of which
		// don't lie on the pareto front.

		size_t i = 0;

		// Case for i = 0
		if (!is_pareto_edge(design_list[0], design_list[1])) {
			// Make design_list an empty list if the first element is not part of the pareto front.
			design_list.clear();
		}
		i++;

		while (i < design_list.size()) {

			if (i == design_list.size() - 1) {

				// Case for the end of the list
				if (!is_pareto_edge(design_list[i - 1], design_list[i])) {
					design_list.pop_back();
					break;
				}

			}
			else {
				// Usual case
				if (!is_pareto_mid(design_list[i - 1], design_list[i])) {
					// If the current member is not in the pareto front
					for (size_t j = i; j < design_list.size() + 1; j++) { // +1 since we also want to
																							// remove the current value
						design_list.pop_back();
					}
					// Exit the while loop once all non-pareto members are removed.
					break;
				}
			}
			i++;
		}
	}

	void optimize_designs(std::vector<Design>& design_list, const std::vector<size_t>& perf_metric_id_order) {

		// Check the input order matches the design metric size
		assert(design_list[0].get_perf_vector().size() == perf_metric_id_order.size());

		// Check all designs have the same number of performance metrics
		for (size_t i = 1; i < design_list.size(); i++) {
			assert(design_list[i - 1].get_perf_vector().size() ==
				design_list[i].get_perf_vector().size());
		}

		std::vector<Design> result_designs = design_list; // Placeholder to store the resultant list

		// Loop over the dominance relations
		for (size_t i = 0; i < perf_metric_id_order.size() - 1; i + 2) { // Minus one to deal with the edge case

			// Set the active performance metrics
			for (size_t j = 0; j < result_designs.size(); j++) {
				result_designs[j].set_active_perf_metrics(perf_metric_id_order[i], perf_metric_id_order[i + 1]);
			}

			// Sort the results vector according to the dominance relation of the previous metrics
			std::sort(result_designs.begin(), result_designs.end(), A_dominates_B);

			// Remove the non-pareto designs
			remove_non_pareto_designs(result_designs);

		}

		// ***** Edge case begin *****

		if (perf_metric_id_order.size() % 2 != 0) {
			for (size_t j = 0; j < result_designs.size(); j++) {
				// If the number of metrics is not even, then choose the last two design metrics.
				// Otherwise, nothing changes.
				size_t metric_id_size = perf_metric_id_order.size();
				result_designs[j].set_active_perf_metrics(perf_metric_id_order[metric_id_size - 2],
					perf_metric_id_order[metric_id_size - 1]);
			}
		}

		// Remove the non-pareto designs
		remove_non_pareto_designs(result_designs);

		// ***** Edge case end *****

		design_list = result_designs;
	}
}
