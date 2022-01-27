#ifndef MDR_FUNCTIONS_H
#define MDR_FUNCTIONS_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>

#include "../headers/DesignClasses.h"

namespace MDR {

	// Given two Designs A and B, return whether A dominates B in their active
	// performance metrics.
	bool A_dominates_B_2D(const Design & A, const Design & B);

	// Given two Designs A and B, return whether A dominates B given an order perf_ids.
	// The perf_ids must hold an even number of ids.
	bool A_dominates_B_multiobj(const Design& A, const Design& B, std::vector<size_t> perf_ids);

	// Given two consecutive designs from a list of designs, ordered by using dominance relations,
	// state whether A is part of the pareto front. (ONLY VALID AT THE EDGES OF THE LIST).
	bool is_pareto_edge(const Design& A, const Design& B);

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
