#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>

#include "../headers/DesignClasses.h"

namespace MDR {

	// Given two Designs A and B, return whether A dominates B in their active
	// performance metrics.
	bool A_dominates_B(const Design& A, const Design& B);

	// Given two consecutive designs from a list of designs, ordered by using dominance relations,
	// state whether A is part of the pareto front. (ONLY VALID AT THE EDGES OF THE LIST).
	bool is_pareto_edge(const Design& A, const Design& B);

	// Given two consecutive designs from a list of designs, ordered by using dominance relations,
	// state whether B is part of the pareto front given that A is part of the pareto front.
	bool is_pareto_mid(const Design& A, const Design& B);

	// Given a list of designs, previously ordered by using dominance relations, remove those of which
	// don't lie on the pareto front.
	void remove_non_pareto_designs(std::vector<Design>& design_list);

	void optimize_designs(std::vector<Design>& design_list, const std::vector<size_t>& perf_metric_id_order);
}
