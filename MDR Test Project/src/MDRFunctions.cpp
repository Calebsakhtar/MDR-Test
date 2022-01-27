#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <iostream>
#include <cmath>

#include "../headers/DesignClasses.h"
#include "../headers/MDRFunctions.h"

namespace MDR {

	bool A_dominates_B_2D(const Design& A, const Design& B,
			const size_t& id1 = 0, const size_t& id2 = 0) {
		// Given two Designs A and B, return whether A dominates B in their active
		// performance metrics (if both id1 and id2 are 0) or in the input metrics.

		size_t first_metric_id = 0;
		size_t second_metric_id = 0;

		if ((id1 == 0) && (id2 == 0)) {
			const std::vector<size_t> active_perf_ids_A = A.get_active_perf_metric_ids();
			const std::vector<size_t> active_perf_ids_B = B.get_active_perf_metric_ids();

			// Verify that the performance ID's are the same
			assert(active_perf_ids_A == active_perf_ids_B);

			first_metric_id = active_perf_ids_A[0];
			second_metric_id = active_perf_ids_A[1];
		}
		else {
			first_metric_id = id1;
			second_metric_id = id2;
		}

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
			first_dominance = first_perf_val_A > first_perf_val_B;
		}

		bool second_dominance = false;
		if (second_minimize_A) {
			// If the 2nd value is to be minimized, check whether A's 2nd value is the smaller one.
			second_dominance = second_perf_val_A < second_perf_val_B;
		}
		else {
			second_dominance = second_perf_val_A > second_perf_val_B;
		}

		// MDR considers relations in pairs (this is the smart bit)
		return first_dominance && second_dominance;
	}

	bool A_dominates_B_MO(const Design& A, const Design& B, std::vector<size_t> perf_ids = {}) {
		// Given two Designs A and B, return whether A dominates B given an order perf_ids.
		// The perf_ids must hold an even number of ids.

		std::vector<PerfMetric> perf_metrics_A = A.get_perf_vector();

		// Populate the perf_ids vector if empty
		if (perf_ids.size() < 1){
			for (size_t i = 1; i < perf_metrics_A.size(); i++) {
				perf_ids.push_back(i);
			}
		}

		// Store the result whether A dominates B in all required elements. Assume true
		bool dominance = true;

		// Loop across all performance metrics
		for (size_t i = 1; i < perf_ids.size(); i += 2) {
			const size_t first_metric_id = perf_ids[i-1];
			const size_t second_metric_id = perf_ids[i];

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
				first_dominance = first_perf_val_A > first_perf_val_B;
			}

			bool second_dominance = false;
			if (second_minimize_A) {
				// If the 2nd value is to be minimized, check whether A's 2nd value is the smaller one.
				second_dominance = second_perf_val_A < second_perf_val_B;
			}
			else {
				second_dominance = second_perf_val_A > second_perf_val_B;
			}

			// MDR considers relations in pairs (this is the smart bit)
			dominance == dominance && first_dominance && second_dominance;

			// Don't bother looping any more if the variable does not dominate
			if (dominance == false) {
				return false;
			}
		}

		// If the end has been reached, A must dominate B 
		return true;
	}

	bool is_pareto_edge(const Design& A, const Design& B) {
		// Given two consecutive designs from a list of designs, ordered by using dominance relations,
		// state whether A is part of the pareto front. (ONLY VALID AT THE EDGES OF THE LIST).
		if (!A_dominates_B_2D(A, B) && !A_dominates_B_2D(B, A)) {
			return true;
		}
		return false;
	}

	bool is_pareto_mid(const Design& A, const Design& B) {
		// Given two consecutive designs from a list of designs, ordered by using dominance relations,
		// state whether B is part of the pareto front given that A is part of the pareto front.
		if (!A_dominates_B_2D(A, B)) {
			return true;
		}
		return false;
	}

	std::vector<Design> find_pareto_front(std::vector<Design>& design_list) {

		//// Sort the design vector
		//std::sort(design_list.begin(), design_list.end(), [](Design A, Design B) {
		//	const std::vector<size_t> ids = A.get_active_perf_metric_ids();
		//	assert(A.get_active_perf_metric_ids() == B.get_active_perf_metric_ids());

		//	double perf_val_A = 0;
		//	double perf_val_B = 0;
		//	A.get_perf_val(ids[0], perf_val_A);
		//	B.get_perf_val(ids[0], perf_val_B);

		//	// Find out whether this value is to be minimized or maximized
		//	bool first_minimize_A = true;
		//	bool first_minimize_B = true;
		//	A.get_perf_minimize(ids[0], first_minimize_A);
		//	B.get_perf_minimize(ids[0], first_minimize_B);
		//	assert(first_minimize_A == first_minimize_B); // Check for errors in minimize

		//	if (first_minimize_A) {
		//		return perf_val_A < perf_val_B;
		//	}
		//	else {
		//		return perf_val_A > perf_val_B;
		//	}
		//	});

		//const std::vector<size_t> ids = design_list[0].get_active_perf_metric_ids();
		//for (size_t i = 0; i < design_list.size(); i++) {
		//	double perf_val = 0;
		//	design_list[i].get_perf_val(ids[0], perf_val);
		//	std::cout << perf_val << std::endl;
		//}

		//// Extract the pareto front from the sorted design vector
		//std::vector<Design> pareto_front = { design_list[0] }; // The first known point in the front is the 1st entry

		//// Compare the remaining designs with the 1st entry, which we know lies on the pareto front
		//for (size_t i = 1; i < design_list.size(); i++) {
		//	if (!A_dominates_B(design_list[0], design_list[i]) && !A_dominates_B(design_list[i], design_list[0])) {

		//		pareto_front.push_back(design_list[i]);
		//	}
		//}

		// Initialise the vector containing the pareto front
		std::vector<Design> pareto_front;

		// Initialise the vector to store the ranks of the design
		std::vector<double> dominations(design_list.size());
		std::fill(dominations.begin(), dominations.end(), 0);

		for (size_t i = 0; i < design_list.size() - 1; i++)
		{
			for (size_t j = i + 1; j < design_list.size(); j++) {

				// Tally the number of times a design is dominated
				if (A_dominates_B(design_list[i], design_list[j])) {
					dominations[j] += 1;
				}
				else if (A_dominates_B(design_list[j], design_list[i])) {
					dominations[i] += 1;
				}
			}
		}

		// Extract the minimum times a design is dominated
		const double mindom = *std::min_element(dominations.begin(), dominations.end());

		// If a design is dominated the minimum number of times, it's in the pareto front
		for (size_t i = 0; i < dominations.size(); i++) {
			if (std::abs(dominations[i] - mindom) < 1e-6) {
				pareto_front.push_back(design_list[i]);
			}
		}

		return pareto_front;
	}

		// Initialise the vector containing the pareto front
		std::vector<Design> pareto_front;

		// Initialise the vector to store the ranks of the design
		std::vector<double> dominations(design_list.size());
		std::fill(dominations.begin(), dominations.end(), 0);

		for (size_t i = 0; i < design_list.size() - 1; i++)
		{
			for (size_t j = i + 1; j < design_list.size(); j++) {

				// Tally the number of times a design is dominated
				if (A_dominates_B_2D(design_list[i], design_list[j])) {
					dominations[j] += 1;
				}
				else if (A_dominates_B_2D(design_list[j], design_list[i])) {
					dominations[i] += 1;
				}
			}
		}

		// Extract the minimum times a design is dominated
		const double mindom = *std::min_element(dominations.begin(), dominations.end());

		// If a design is dominated the minimum number of times, it's in the pareto front
		for (size_t i = 0; i < dominations.size(); i++) {
			if (std::abs(dominations[i] - mindom) < 1e-6) {
				pareto_front.push_back(design_list[i]);
			}
		}

		return pareto_front;
	}

	void remove_non_pareto_designs(std::vector<Design>& design_list) {
		// Given a list of designs, previously ordered by using dominance relations, remove those of which
		// don't lie on the pareto front.

		if (design_list.size() > 1) {
			size_t i = 0;

			// Case for i = 0
			if (!is_pareto_edge(design_list[0], design_list[1])) {
				// Make design_list an empty list if the first element is not part of the pareto front.
				design_list.clear();
			}
			i++;

			while (i < design_list.size()) {
				if (!is_pareto_mid(design_list[i - 1], design_list[i])) {
					// If the current member is not in the pareto front
					for (size_t j = i; j < design_list.size() + 1; j++) { // +1 since we also want to
																								// remove the current value
						design_list.pop_back();
					}
					// Exit the while loop once all non-pareto members are removed.
					break;
				}
				i++;
			}
		}
	}

	// Update the rank vector of both the existing designs and the new design according
	// to layers of dominance
	void update_ranks(Design& new_design, std::vector<Design>& existing_designs,
		std::vector<DomRel> id_order) {
		// For each existing design
		for (size_t i = 0; i < existing_designs.size(); i++) {
			Design current_design = existing_designs[i];

			// For each dominance layer
			for (size_t j = 0; j < id_order.size(); j++) {
				DomRel current_rel = id_order[j];

				if (A_dominates_B_2D(current_design, new_design,
					current_rel[1], current_rel[2])) {
					// If the new design is dominated by an existing design, increase the
					// rank value of the new design
					new_design.increase_rank_val(j);
				}
				else if (A_dominates_B_2D(new_design, current_design,
					current_rel[1], current_rel[2])) {
					// If the new design dominates an existing design, increase the
					// rank value of the existing design
					current_design.increase_rank_val(j);
				}
			}
		}
	}

	std::vector<std::vector<Design>> optimize_designs(std::vector<Design>& design_list,
		const std::vector<size_t>& perf_metric_id_order) {

		std::vector<std::vector<Design>> pareto_fronts;
		pareto_fronts.push_back(design_list);

		// Check all designs have the same number of performance metrics
		for (size_t i = 1; i < design_list.size(); i++) {
			assert(design_list[i - 1].get_perf_vector().size() ==
				design_list[i].get_perf_vector().size());
		}

		std::vector<Design> result_designs = design_list; // Placeholder to store the resultant list

		// Loop over the dominance relations
		for (size_t i = 0; i < perf_metric_id_order.size() - 1; i += 2) { // Minus one to deal with the edge case

																								// Set the active performance metrics
			for (size_t j = 0; j < result_designs.size(); j++) {
				result_designs[j].set_active_perf_metrics(perf_metric_id_order[i], perf_metric_id_order[i + 1]);
			}

			// Find the current pareto front
			result_designs = find_pareto_front(result_designs);
			pareto_fronts.push_back(result_designs);
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
			result_designs = find_pareto_front(result_designs);
			pareto_fronts.push_back(result_designs);
		}

		// ***** Edge case end *****

		design_list = result_designs;

		return pareto_fronts;
	}
}
