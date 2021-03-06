#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <iostream>
#include <cmath>

#include "../headers/DesignClasses.h"
#include "../headers/MDRFunctions.h"

namespace MDR {

	// DISCLAIMER:
	// ALL FUNCTIONS IN THIS DOCUMENT HAVE BEEN INSPIRED BY THE PSEUDO-CODE
	// IN THE FOLLOWING ARTICLE:
	//
	// L. W. Cook, K. E. Willcox, and J. P. Jarrett,
	// “Design optimization using multiple dominance relations,”
	// International Journal for Numerical Methods in Engineering, vol. 121,
	// no. 11, pp. 2481–2502, 2020. doi: https://doi.org/10.1002/nme.6316.
	//
	// Unless otherwise stated, these functions adapt the teachings and algorithms
	// of the above article.


	// Given two Designs A and B, return whether A dominates B in their active
	// performance metrics (if both id1 and id2 are 0) or in the input metrics.
	//
	// Implement a binary relation from L. W. Cook et. al.
	bool A_dominates_B_2D(const Design& A, const Design& B,
			const size_t& id1, const size_t& id2) {

		size_t first_metric_id = id1;
		size_t second_metric_id = id2;

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

	// Given two Designs A and B, return whether A dominates B given an order perf_ids.
	// The perf_ids must hold an even number of ids
	// MO concept from https://en.wikipedia.org/wiki/Multi-objective_optimization
	bool A_dominates_B_MO(const Design& A, const Design& B, std::vector<size_t> perf_ids) {

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

	// Check whether A dominates B according to MDR given a list of dominance relations
	// 
	// Implementation of a Algorithm 3 from L. W. Cook et. al.
	bool A_dominates_B_MDR(const Design& A, const Design& B,
		const std::vector<DomRel>& dominance_relations) {

		// Check the dominance relation layer by layer (MDR)
		for (size_t i = 0; i < dominance_relations.size(); i++) {
			DomRel current_dom_rel = dominance_relations[i];

			if (A_dominates_B_2D(A, B, current_dom_rel[0], current_dom_rel[1])) {
				// If A dominates B at the current dominance level, A dominates B according to MDR.
				return true;
			}
			else if (A_dominates_B_2D(B, A, current_dom_rel[0], current_dom_rel[1])) {
				// If B dominates A at the current dominance level, B dominates A according to MDR.
				// Therefore A does not dominate B, so return false
				return false;
			}
		}

		// If no dominance is clear, B is not dominated by A
		return false;
	}


	// Update the rank vector of both the existing designs and the new design according
	// to layers of dominance
	//
	// Implementation of Algorithm 2 from L. W. Cook et. al.
	void update_ranks(Design& new_design, std::vector<Design>& existing_designs,
		std::vector<DomRel> id_order) {
		// For each existing design
		for (size_t i = 0; i < existing_designs.size(); i++) {
			Design current_design = existing_designs[i];

			// For each dominance layer
			for (size_t j = 0; j < id_order.size(); j++) {
				DomRel current_rel = id_order[j];

				if (A_dominates_B_2D(current_design, new_design,
					current_rel[0], current_rel[1])) {
					// If the new design is dominated by an existing design, increase the
					// rank value of the new design
					new_design.increase_rank_val(j);
				}
				else if (A_dominates_B_2D(new_design, current_design,
					current_rel[0], current_rel[1])) {
					// If the new design dominates an existing design, increase the
					// rank value of the existing design
					current_design.increase_rank_val(j);
				}
			}
		}
	}

	// Returns the 2D pareto front within a list of designs and a set of dominance relations
	// 
	// A part of the combined implementations of Algorithms 2 and 4 from L. W. Cook et. al.
	std::vector<Design> find_pareto_front(std::vector<Design>& design_list, const DomRel& dom_rel) {

		// Initialise the vector containing the dominance relations
		std::vector<DomRel> dom_rels = { dom_rel };

		// Initialise the vector containing the pareto front
		std::vector<Design> pareto_front;

		// Initialise the vector to store the ranks of the design
		std::vector<double> dominations(design_list.size());
		std::fill(dominations.begin(), dominations.end(), 0);

		for (size_t i = 0; i < design_list.size() - 1; i++)
		{
			for (size_t j = i + 1; j < design_list.size(); j++) {

				// Tally the number of times a design is dominated
				if (A_dominates_B_MDR(design_list[i], design_list[j], dom_rels)) {
					dominations[j] += 1;
				}
				else if (A_dominates_B_MDR(design_list[j], design_list[i], dom_rels)) {
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


	// Find the set of pareto fronts given a list of designs and some dominance relations
	// A part of the combined implementations of Algorithms 2 and 4 from L. W. Cook et. al.
	std::vector<std::vector<Design>> optimize_designs(const std::vector<Design>& design_list,
		const std::vector<DomRel>& dom_rels) {

		std::vector<std::vector<Design>> pareto_fronts;
		pareto_fronts.push_back(design_list);

		// Check all designs have the same number of performance metrics
		for (size_t i = 1; i < design_list.size(); i++) {
			assert(design_list[i - 1].get_perf_vector().size() ==
				design_list[i].get_perf_vector().size());
		}

		std::vector<Design> result_designs = design_list; // Placeholder to store the resultant list

		// Loop over the dominance relations
		for (size_t i = 0; i < dom_rels.size(); i += 2) { // Minus one to deal with the edge case

			// Find the current pareto front
			result_designs = find_pareto_front(result_designs, dom_rels[i]);
			pareto_fronts.push_back(result_designs);
		}

		return pareto_fronts;
	}


	// DEPRECATED
	//
	// Failed attempt to make the function sortable (of my own design)
	// 
	// Given two consecutive designs from a list of designs, ordered by using dominance relations,
	// state whether A is part of the pareto front. (ONLY VALID AT THE EDGES OF THE LIST).
	bool is_pareto_edge(const Design& A, const Design& B) {
		if (!A_dominates_B_2D(A, B) && !A_dominates_B_2D(B, A)) {
			return true;
		}
		return false;
	}

	// DEPRECATED
	//
	// Failed attempt to make the function sortable (of my own design)
	// 
	// Given two consecutive designs from a list of designs, ordered by using dominance relations,
	// state whether B is part of the pareto front given that A is part of the pareto front.
	bool is_pareto_mid(const Design& A, const Design& B) {
		if (!A_dominates_B_2D(A, B)) {
			return true;
		}
		return false;
	}

	// DEPRECATED
	//
	// Failed attempt at implementing is_pareto_edge and is_pareto_mid (of my own design)
	// 
	// Given a list of designs, previously ordered by using dominance relations, remove those of which
	// don't lie on the pareto front.
	void remove_non_pareto_designs(std::vector<Design>& design_list) {

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

}
