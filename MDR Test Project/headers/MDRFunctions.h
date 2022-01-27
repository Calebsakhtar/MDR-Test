#ifndef MDR_FUNCTIONS_H
#define MDR_FUNCTIONS_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>

#include "../headers/DesignClasses.h"

namespace MDR {

	// Given two Designs A and B, return whether A dominates B in their active
	// performance metrics (if both id1 and id2 are 0) or in the input metrics.
	bool A_dominates_B_2D(const Design& A, const Design& B,
		const size_t& id1, const size_t& id2);

	// Given two Designs A and B, return whether A dominates B given an order perf_ids.
	// The perf_ids must hold an even number of ids.
	bool A_dominates_B_MO(const Design& A, const Design& B, std::vector<size_t> perf_ids);

	// Check whether A dominates B according to MDR given a list of dominance relations
	bool A_dominates_B_MDR(const Design& A, const Design& B,
		const std::vector<DomRel>& dominance_relations);

	// Given two consecutive designs from a list of designs, ordered by using dominance relations,
	// state whether A is part of the pareto front. (ONLY VALID AT THE EDGES OF THE LIST).
	bool is_pareto_edge(const Design& A, const Design& B);

	// Update the rank vector of both the existing designs and the new design according
	// to layers of dominance
	void update_ranks(Design& new_design, std::vector<Design>& existing_designs,
		std::vector<DomRel> id_order);

	// Given two consecutive designs from a list of designs, ordered by using dominance relations,
	// state whether B is part of the pareto front given that A is part of the pareto front.
	bool is_pareto_mid(const Design& A, const Design& B);

	// Given a list of designs, previously ordered by using dominance relations, remove those of which
	// don't lie on the pareto front.
	void remove_non_pareto_designs(std::vector<Design>& design_list);

	std::vector<std::vector<Design>> optimize_designs(std::vector<Design>& design_list,
		const std::vector<size_t>& perf_metric_id_order);
}

#endif
