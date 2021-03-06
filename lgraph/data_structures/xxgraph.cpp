#include <lgraph/data_structures/xxgraph.hpp>

// C includes
#include <assert.h>

namespace lgraph {

// PROTECTED

size_t xxgraph::get_neighbour_position(const neighbourhood& n, node u) const {
	size_t p = 0;
	while (p < n.size()) {
		if (n[p] == u) {
			return p;
		}
		++p;
	}
	return n.size();
}

void xxgraph::initialise_adjacency_list(size_t n) {
	adjacency_list = std::vector<neighbourhood>(n);
}

void xxgraph::clear_adjacency_list() {
	adjacency_list.clear();
}

void xxgraph::initialise_parent_graph(size_t n) {
	initialise_adjacency_list(n);
	num_edges = 0;
}

void xxgraph::clear_parent_graph() {
	clear_adjacency_list();
	num_edges = 0;
}

// PUBLIC

xxgraph::xxgraph() {
	num_edges = 0;
}

xxgraph::~xxgraph() {
}

// OPERATORS

// MODIFIERS

size_t xxgraph::add_node() {
	adjacency_list.push_back(neighbourhood());
	return adjacency_list.size() - 1;
}

size_t xxgraph::add_n_nodes(size_t n) {
	adjacency_list.insert(adjacency_list.end(), n, neighbourhood());
	return adjacency_list.size() - 1;
}

void xxgraph::remove_edge(const edge& e) {
	remove_edge(e.first, e.second);
}

void xxgraph::remove_edges(const std::vector<edge>& edge_list) {
	for (const edge& e : edge_list) {
		remove_edge(e.first, e.second);
	}
}

// GETTERS

bool xxgraph::has_node(node u) const {
	return u < adjacency_list.size();
}

size_t xxgraph::n_nodes() const {
	return adjacency_list.size();
}

size_t xxgraph::n_edges() const {
	return num_edges;
}

void xxgraph::nodes(std::vector<node>& all_nodes) const {
	all_nodes.resize(adjacency_list.size());
	for (size_t u = 0; u < all_nodes.size(); ++u) {
		all_nodes[u] = u;
	}
}

const neighbourhood& xxgraph::get_neighbours(node u) const {
	return adjacency_list[u];
}

size_t xxgraph::degree(node u) const {
	return adjacency_list[u].size();
}

long long int xxgraph::genus() const {
	long long int e = static_cast<long long int>(n_edges());
	long long int v = static_cast<long long int>(n_nodes());
	return e - v + 1;
}

// I/O

// FEATURES OF GRAPHS

void xxgraph::get_adjacency_matrix(std::vector<std::vector<bool> >& adj_mat) const {
	const size_t N = n_nodes();
	adj_mat = std::vector<std::vector<bool> >(N, std::vector<bool>(N, false));
	for (size_t u = 0; u < N; ++u) {
		const neighbourhood& Nu = get_neighbours(u);
		for (size_t v : Nu) {
			adj_mat[u][v] = true;
		}
	}
}

void xxgraph::get_degree_sequence(std::map<size_t, size_t>& deg_seq) const {
	for (size_t u = 0; u < adjacency_list.size(); ++u) {
		size_t deg = degree(u);
		if (deg_seq.find(deg) == deg_seq.end()) {
			deg_seq[deg] = 1;
		}
		else {
			++deg_seq[deg];
		}
	}
}

size_t xxgraph::n_triangles() const {
	size_t tris = 0;
	const size_t N = n_nodes();

	for (size_t u = 0; u < N; ++u) {

		const neighbourhood& Nu = get_neighbours(u);
		for (size_t v_it = 0; v_it < Nu.size(); ++v_it) {
			node v = Nu[v_it];

			for (size_t w_it = v_it + 1; w_it < Nu.size(); ++w_it) {
				node w = Nu[w_it];

				// existing edges: (u, v), (u, w)
				// check edge (v, w) for triangles

				if (has_edge(v, w)) {
					++tris;
				}
			}
		}

	}

	// Each triangle is counted three times
	return tris/3;
}

} // -- namespace lgraph
