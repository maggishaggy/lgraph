#include <lgraph/communities/communities.hpp>

namespace lgraph {
namespace networks {
namespace communities {

	size_t connected_components(const uugraph& g, vector<size_t>& comps) {
		const size_t N = g.n_nodes();

		// initialise with a value equal to the number
		// of nodes to indicate unprocessed node
		comps = vector<size_t>(N, N);
		// the label of each connected component
		size_t label = 0;

		bfs_terminate term = [](const uxgraph *, node, const vector<bool>&) -> bool {
			// the BFS algorithm will terminate by its own accord
			// when it can't find more neighbours to expand the
			// search to.
			return false;
		};
		bfs_process_current proc_cur = [&](const uxgraph *, node u, const vector<bool>&) -> void {
			// assign to vertex u the current label
			comps[u] = label;
		};
		bfs_process_neighbour proc_neigh = [](const uxgraph *, node, node, const vector<bool>&) -> void {
			// no need to do anything
		};

		for (node u = 0; u < g.n_nodes(); ++u) {
			// if a node has already been processed, skip
			if (comps[u] < N) {
				continue;
			}

			// Launch the BSF traversal starting at node u.
			BFS(&g, u, term, proc_cur, proc_neigh);

			// The traversal has found a whole new component
			// -> increment label
			++label;
		}

		return label;
	}

	size_t connected_components(const udgraph& g, vector<size_t>& comps) {
		comps = vector<size_t>(g.n_nodes(), g.n_nodes());

		return 0;
	}

} // -- namespace communities
} // -- namespace networks
} // -- namespace lgraph
