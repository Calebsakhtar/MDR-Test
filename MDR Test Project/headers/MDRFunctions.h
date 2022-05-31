#ifndef MDR_FUNCTIONS_H
#define MDR_FUNCTIONS_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>

#include "../headers/DesignClasses.h"

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


	// BEGIN DEPRECATED

	//// DEPRECATED (Can still be used if necessary)
	//
	// // Find the set of pareto fronts given a list of designs and some dominance relations
	// // A part of the combined implementations of Algorithms 2 and 4 from L. W. Cook et. al.
	//std::vector<std::vector<Design>> optimize_designs(const std::vector<Design>& design_list,
	//	const std::vector<DomRel>& dom_rels);

	// END DEPRECATED


	// Given two Designs A and B, return whether A dominates B in their active
	// performance metrics (if both id1 and id2 are 0) or in the input metrics.
	//
	// Implement a binary relation from L. W. Cook et. al.
	bool A_dominates_B_2D(const Design& A, const Design& B,
		const size_t& id1 = 0, const size_t& id2 = 0);
	
	// Given two Designs A and B, return whether A dominates B given an order perf_ids.
	// The perf_ids must hold an even number of ids.
	bool A_dominates_B_MO(const Design& A, const Design& B, std::vector<size_t> perf_ids = {});

	// Check whether A dominates B according to MDR given a list of dominance relations
	// Direct implementation of a Algorithm 3 from L. W. Cook et. al.
	bool A_dominates_B_MDR(const Design& A, const Design& B,
		const std::vector<DomRel>& dominance_relations);

	// Update the rank vector of both the existing designs and the new design according
	// to layers of dominance
	//
	// Implementation of Algorithm 2 from L. W. Cook et. al.
	void update_ranks(Design& new_design, std::vector<Design>& existing_designs,
		std::vector<DomRel> id_order);
}

#endif
