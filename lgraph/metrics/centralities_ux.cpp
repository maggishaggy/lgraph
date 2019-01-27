#include <lgraph/metrics/centralities_ux.hpp>

// C++ includes
#include <numeric>
using namespace std;

// lgraph includes
#include <lgraph/graph_traversal/traversal_ux.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* DEGREE */

double degree(const uxgraph *G, node u) {
	// number of nodes minus 1
	const double nm1 = G->n_nodes() - 1;
	return G->degree(u)/nm1;
}

void degree(const uxgraph *G, std::vector<double>& dc) {
	std::vector<node> nds;
	G->nodes(nds);

	// number of nodes minus 1
	const double nm1 = G->n_nodes() - 1;
	dc.clear();

	transform(
		// iterate through all nodes
		nds.begin(), nds.end(),

		// append value at the back of dc
		back_inserter(dc),

		// calculate degree centrality
		[&](node u) {
			return G->degree(u)/nm1;
		}
	);
}

/* CLOSENESS */

double closeness(const uxgraph *G, node u) {
	std::vector<_new_> ds;
	traversal::uxdistance(G, u, ds);
	double sum = std::accumulate
	(
		ds.begin(), ds.end(), 0.0,
		[](double acc, _new_ d) {
			// if d is infinite 1.0/d equals 0:n no need to divide
			if (d != inf_t<_new_>() and d > 0) {
				acc += 1.0/d;
			}
			return acc;
		}
	);

	return 1.0/(sum/(G->n_nodes() - 1));
}

void closeness(const uxgraph *G, std::vector<double>& cc) {
	std::vector<std::vector<_new_> > ds;
	traversal::uxdistances(G, ds);
	return closeness(G, ds, cc);
}

void closeness(const uxgraph *G, const std::vector<std::vector<_new_> >& ds, std::vector<double>& cc) {
	transform(
		// iterate through all nodes
		ds.begin(), ds.end(),

		// append value at the back of cc
		back_inserter(cc),

		// calculate closeness centrality
		[&](const std::vector<_new_>& ds_i) {
			double sum = std::accumulate
			(
				ds_i.begin(), ds_i.end(), 0.0,
				[](double acc, _new_ d) {
					if (d != inf_t<_new_>() and d > 0) {
						acc += 1.0/d;
					}
					return acc;
				}
			);

			return 1.0/(sum/(G->n_nodes() - 1));
		}
	);
}

double mcc(const uxgraph *G) {
	std::vector<double> cc;
	closeness(G, cc);
	return mcc(G, cc);
}

double mcc(const uxgraph *G, const std::vector<double>& cc) {
	double S = std::accumulate(cc.begin(), cc.end(), 0.0);
	return S/G->n_nodes();
}

/* BETWEENNES */

double betweenness(const uxgraph *G, node u) {
	std::vector<std::vector<boolean_path_set<_new_> > > all_to_all_paths;
	traversal::uxpaths(G, all_to_all_paths);
	return betweenness(G, all_to_all_paths, u);
}

double betweenness(
	const uxgraph *G,
	const std::vector<std::vector<boolean_path_set<_new_> > >& paths,
	node u
)
{
	double B = 0.0;

	const size_t N = G->n_nodes();
	for (node s = 0; s < N; ++s) {
		for (node t = s; t < N; ++t) {
			// amount of shortest paths between s and t
			const double g_st = paths[s][t].size();

			// don't do any more calculations if there are no paths from s to t
			if (g_st == 0.0) {
				continue;
			}

			// amount of shortest paths between s and t in which u lies on
			size_t g_st_i = 0;
			for (const boolean_path<_new_>& bp : paths[s][t]) {
				if (bp[u]) {
					++g_st_i;
				}
			}

			// calculate the "partial" centrality
			B += g_st_i/g_st;
		}
	}

	// normalise with "(n - 1) choose 2"
	const size_t n_minus_1__chose_2 = ((N - 1)*(N - 2))/2;
	B = B/n_minus_1__chose_2;
	return B;
}

void betweenness(const uxgraph *G, std::vector<double>& bc) {
	std::vector<std::vector<boolean_path_set<_new_> > > all_to_all_paths;
	traversal::uxpaths(G, all_to_all_paths);
	betweenness(G, all_to_all_paths, bc);
}

void betweenness(
	const uxgraph *G,
	const std::vector<std::vector<boolean_path_set<_new_> > >& paths,
	std::vector<double>& bc
)
{
	const size_t N = G->n_nodes();

	// amount of shortest paths between s and t in
	// which vertices of the graph lie on
	std::vector<size_t> g_st_i(N);
	// initialise data
	bc = std::vector<double>(N, 0);

	for (node s = 0; s < N; ++s) {
		for (node t = s; t < N; ++t) {

			// amount of shortest paths between s and t
			const size_t g_st = paths[s][t].size();

			// don't do any more calculations if there
			// are no paths from s to t
			if (g_st == 0) {
				continue;
			}

			// set vector to 0
			std::fill(g_st_i.begin(), g_st_i.end(), 0);

			for (node u = 0; u < N; ++u) {
				for (const boolean_path<_new_>& bp : paths[s][t]) {
					if (bp[u]) {
						++g_st_i[u];
					}
				}
			}

			// calculate the "partial" centrality for each node
			for (node u = 0; u < N; ++u) {
				bc[u] += g_st_i[u]/g_st;
			}
		}
	}

	// normalise
	const size_t n_minus_1__chose_2 = ((N - 1)*(N - 2))/2;
	for (node u = 0; u < N; ++u) {
		bc[u] /= n_minus_1__chose_2;
	}
}
	
} // -- namespace centralities
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

