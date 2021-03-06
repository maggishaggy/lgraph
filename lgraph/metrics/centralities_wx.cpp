#include <lgraph/metrics/centralities_ux.hpp>

// C++ includes
#include <numeric>

// lgraph includes
#include <lgraph/graph_traversal/traversal_wx.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace centralities {

/* CLOSENESS */

template<class T>
double closeness(const wxgraph<T> *G, node u) {
	std::vector<T> ds;
	traversal::wxdistance(G, u, ds);
	double sum = std::accumulate
	(
		ds.begin(), ds.end(), 0.0,
		[](double acc, _new_ d) {
			// if d is infinite 1.0/d equals 0:n no need to divide
			if (d != inf_t<_new_>()) {
				acc += static_cast<double>(d);
			}
			return acc;
		}
	);

	return 1.0/(sum/(G->n_nodes() - 1));
}

template<class T>
void closeness(const wxgraph<T> *G, std::vector<double>& cc) {
	std::vector<std::vector<T> > ds;
	traversal::wxdistances(G, ds);
	return closeness(G, ds, cc);
}

template<class T> void closeness
(const wxgraph<T> *G, const std::vector<std::vector<T> >& ds, std::vector<double>& cc)
{
	transform(
		// iterate through all nodes
		ds.begin(), ds.end(),
		// append value at the back of cc
		back_inserter(cc),

		// calculate closeness centrality
		[&](const std::vector<T>& ds_i) {
			double sum = std::accumulate
			(
				ds_i.begin(), ds_i.end(), 0.0,
				[](double acc, _new_ d) {
					if (d != inf_t<_new_>()) {
						acc += static_cast<double>(d);
					}
					return acc;
				}
			);
			return 1.0/(sum/(G->n_nodes() - 1));
		}
	);
}

template<class T>
double mcc(const wxgraph<T> *G) {
	std::vector<std::vector<T> > ds;
	traversal::wxdistances(G, ds);
	// compute sum of all the distance values.

	double sum = accumulate(
		ds.begin(), ds.end(), 0.0,
		[](double acc, const std::vector<T>& v) -> double {
			// sum of a row, accumulate values below infinte
			T s = accumulate(
				v.begin(), v.end(), static_cast<T>(0),
				[](_new_ acc_inner, _new_ d) -> T {
					if (d != inf_t<T>()) {
						acc_inner += d;
					}
					return acc_inner;
				}
			);
			// sum of inverse of distances
			return acc + 1.0/s;
		}
	);

	double n = static_cast<double>(G->n_nodes());
	return ((n - 1.0)/n)*sum;
}

template<class T>
double mcc(const wxgraph<T> *G, const std::vector<double>& cc) {
	double S = std::accumulate(cc.begin(), cc.end(), 0.0);
	return S/G->n_nodes();
}

/* BETWEENNES */

template<class T>
double betweenness(const wxgraph<T> *G, node u) {
	std::vector<std::vector<boolean_path_set<T> > > all_to_all_paths;
	traversal::wxpaths(G, all_to_all_paths);
	return betweenness(G, all_to_all_paths, u);
}

template<class T> double betweenness(
	const wxgraph<T> *G,
	const std::vector<std::vector<boolean_path_set<T> > >& paths,
	node u
)
{
	double B = 0.0;

	const size_t N = G->n_nodes();
	for (node s = 0; s < N; ++s) {
		for (node t = s + 1; t < N; ++t) {
			if (s == u or t == u) {
				// this should be obvious
				B += 1.0;
				continue;
			}

			// don't do anything if there are no paths from s to t
			if (paths[s][t].size() == 0) {
				continue;
			}

			// amount of shortest paths between s and t in which u lies on
			size_t g_st_i = 0;
			for (const boolean_path<T>& bp : paths[s][t]) {
				if (bp[u]) {
					++g_st_i;
				}
			}

			double g_st = paths[s][t].size();

			// calculate the "partial" centrality
			B += g_st_i/g_st;
		}
	}

	// normalise with "(n - 1) choose 2"
	const size_t n_minus_1__chose_2 = ((N - 1)*(N - 2))/2;
	B = B/n_minus_1__chose_2;
	return B;
}

template<class T>
void betweenness(const wxgraph<T> *G, std::vector<double>& bc) {
	std::vector<std::vector<boolean_path_set<T> > > all_to_all_paths;
	traversal::wxpaths(G, all_to_all_paths);
	betweenness(G, all_to_all_paths, bc);
}

template<class T> void betweenness(
	const wxgraph<T> *G,
	const std::vector<std::vector<boolean_path_set<T> > >& paths,
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
		for (node t = s + 1; t < N; ++t) {
			// don't do anything if there are no paths from s to t
			if (paths[s][t].size() == 0) {
				continue;
			}

			// set std::vector to 0
			std::fill(g_st_i.begin(), g_st_i.end(), 0);

			for (node u = 0; u < N; ++u) {
				for (const boolean_path<T>& bp : paths[s][t]) {
					if (bp[u]) {
						++g_st_i[u];
					}
				}
			}

			double g_st = paths[s][t].size();

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

