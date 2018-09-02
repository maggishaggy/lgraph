#pragma once

// C includes
#include <assert.h>

// C++ includes
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <random>
#include <vector>
using namespace std;

// Custom includes
#include <lgraph/data_structures/random_generator.hpp>
#include <lgraph/data_structures/uugraph.hpp>
#include <lgraph/data_structures/svector.hpp>
#include <lgraph/generate_graphs/classic/classic.hpp>
#include <lgraph/utils/logger.hpp>

namespace lgraph {
using namespace utils;

namespace networks {
namespace random {

	/**
	 * @brief Watts & Strogatz's model.
	 *
	 * Create a cycle graph of @e N nodes, then connect each node with
	 * its @e k nearest nodes in the ring (or @e k - 1 if @e k is odd).
	 *
	 * The rewiring is done by iterating over all edges created in the
	 * previous two steps (@e u,@e v) and replacing it with an edge
	 * (@e u,@e w) with probability @e p.
	 *
	 * @e w is chosen uniformly at random from the set of non-neighbours
	 * of @e u at the moment of rewiring.
	 *
	 * @param crg Continuous random number generator. Has to be seeded by the caller.
	 * @param drg Discrete random number generator. Has to be seeded by the caller.
	 * @param   N Number of nodes of the graph.
	 * @param   k Number of the @e k nearest neighbours in a ring topology.
	 * Must satisfy: 2 <= @e k <= @e N - 1.
	 * @param   p Probability of rewiring an edge.
	 * @param  Gs The graph generated, following the Watts & Strogatz's model.
	 */
	template<
		class G = default_random_engine,
		typename cT = float,
		typename dT = size_t
	>
	void Watts_Strogatz(
		crandom_generator<G,cT> *crg,
		drandom_generator<G,dT> *drg,
		size_t N, size_t k, double p,
		uugraph& Gs
	);

} // -- namespace random
} // -- namespace networks
} // -- namespace lgraph

#include <lgraph/generate_graphs/random/watts_strogatz.cpp>
