#include <lgraph/metrics/distance.hpp>

namespace lgraph {
namespace networks {
namespace metrics {
namespace distance {

_new_ max_distance(const uxgraph *G) {
	std::vector<std::vector<_new_> > ds;
	traversal::uxdistances(G, ds);
	return max_distance(G, ds);
}

_new_ max_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds) {
	const size_t N = G->n_nodes();
	_new_ D = 0;
	for (size_t i = 0; i < N; ++i) {
		D = accumulate
		(
			ds[i].begin() + i + 1, ds[i].end(), D,
			[](_new_ M, _new_ d) {
				if (d != inf_t<_new_>()) {
					M = std::max(M, d);
				}
				return M;
			}
		);

	}
	return D;
}

double mean_distance(const uxgraph *G) {
	std::vector<std::vector<_new_> > ds;
	traversal::uxdistances(G, ds);
	return mean_distance(G, ds);
}

double mean_distance(const uxgraph *G, const std::vector<std::vector<_new_> >& ds) {
	const size_t N = G->n_nodes();
	double m = 0;
	for (size_t i = 0; i < N; ++i) {

		// sum values only if they are not infinite
		double li = accumulate
		(
			ds[i].begin(), ds[i].end(), 0.0,
			[](double acc, _new_ d) {
				if (d != inf_t<_new_>()) {
					acc += d;
				}
				return acc;
			}
		);
		// divide by (N - 1) because ds[i][i] = 0
		li /= (N - 1);

		m += li;
	}
	return m/N;
}

double mcc(const uxgraph *G) {
	std::vector<double> cc;
	centralities::closeness(G, cc);
	return mcc(G, cc);
}

double mcc(const uxgraph *G, const std::vector<double>& cc) {
	double S = std::accumulate(cc.begin(), cc.end(), 0.0);
	return S/G->n_nodes();
}

} // -- namespace distance
} // -- namespace metrics
} // -- namespace networks	
} // -- namespace lgraph

