#pragma once

// C++ includes
#include <vector>

// lgraph includes
#include <lgraph/data_structures/uxgraph.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace distance {

/* ------------------------------- */
/* DISTANCES FOR UNWEIGHTED GRAPHS */

/**
 * @brief Diameter of a graph.
 *
 * Computes the distance between all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @return Returns the largest distance between all pairs of nodes.
 */
_new_ max_distance(const uxgraph *G);
/**
 * @brief Diameter of a graph.
 *
 * Uses the parameter @e ds to avoid computing the distance between
 * all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @param ds @e ds[u][v] contains the distance between nodes @e u and @e v.
 * @return Returns the largest distance between all pairs of nodes.
 */
_new_ max_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds);

/**
 * @brief Mean distance between all pairs of nodes.
 *
 * Computes the distance between all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @return Returns the average of the distance between all pairs of nodes.
 */
double mean_distance(const uxgraph *G);
/**
 * @brief Mean distance between all pairs of nodes.
 *
 * Uses the parameter @e ds to avoid computing the distance between
 * all pairs of nodes.
 *
 * @param G The graph to be evaluated.
 * @param ds @e ds[u][v] contains the distance between nodes @e u and @e v.
 * @return Returns the average of the distance between all pairs of nodes.
 */
double mean_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds);

} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph
