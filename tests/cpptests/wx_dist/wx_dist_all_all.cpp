// C++ inlcudes
#include <iostream>
#include <vector>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/wugraph.hpp>
#include <lgraph/data_structures/wdgraph.hpp>
#include <lgraph/graph_traversal/traversal_wx.hpp>
#include <lgraph/io/io.hpp>
using namespace lgraph;

// custom includes
#include "definitions.hpp"
#include "io_wrapper.hpp"
#include "test_utils.hpp"
using namespace test_utils;

namespace exe_tests {

void wx_distance_all_all__single(const wxgraph<float> *G) {
	vector<vector<float> > uv_dists;
	traversal::wxdistances(G, uv_dists);
	for (node u = 0; u < G->n_nodes(); ++u) {
		for (node v = 0; v < G->n_nodes(); ++v) {
			cout << "(" << u << ", " << v << "): "
				 << floatpointout_dist(uv_dists[u][v]) << endl;
		}
	}
}

void wx_distance_all_all__all(const wxgraph<float> *G) {
	vector<vector<float> > uv_dists;
	vector<vector<size_t> > n_paths;
	traversal::wxdistances(G, uv_dists, n_paths);
	for (node u = 0; u < G->n_nodes(); ++u) {
		for (node v = 0; v < G->n_nodes(); ++v) {
			cout << "(" << u << ", " << v << "): "
				 << floatpointout_dist(uv_dists[u][v])
				 << " (" << n_paths[u][v] << ")"
				 << endl;
		}
	}
}

err_type wx_distance_all_all
(const string& graph_type, const string& many, ifstream& fin)
{
	string input_graph, format;
	size_t n;

	// parse input field
	string field;
	fin >> field;
	if (field != "INPUT") {
		cerr << ERROR("wx_distance_all_all.cpp", "wx_distance_all_all") << endl;
		cerr << "    Expected field 'INPUT'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}
	fin >> n;
	if (n != 1) {
		cerr << ERROR("wx_distance_all_all.cpp", "wx_distance_all_all") << endl;
		cerr << "    Only one input file is allowed in this test." << endl;
		cerr << "    Instead, " << n << " were specified." << endl;
		return err_type::test_format_error;
	}
	fin >> input_graph >> format;

	// parse body field
	fin >> field;
	if (field != "BODY") {
		cerr << ERROR("wx_distance_all_all.cpp", "wx_distance_all_all") << endl;
		cerr << "    Expected field 'BODY'." << endl;
		cerr << "    Instead, '" << field << "' was found." << endl;
		return err_type::test_format_error;
	}

	wxgraph<float> *G = nullptr;
	if (graph_type == "directed") {
		G = new wdgraph<float>();
	}
	else if (graph_type == "undirected") {
		G = new wugraph<float>();
	}
	else {
		cerr << ERROR("wx_distance_all_all.cpp", "wx_distance_all_all") << endl;
		cerr << "    Wrong value for parameter 'graph_type'." << endl;
		cerr << "    Received '" << graph_type << "'." << endl;
		return err_type::invalid_param;
	}

	err_type r = io_wrapper::read_graph(input_graph, format, G);
	if (r != err_type::no_error) {
		if (r == err_type::io_error) {
			cerr << ERROR("wx_distance_all_all.cpp", "wx_distance_all_all") << endl;
			cerr << "    Could not open file '" << input_graph << "'" << endl;
		}
		else if (r == err_type::graph_format_error) {
			cerr << ERROR("wx_distance_all_all.cpp", "wx_distance_all_all") << endl;
			cerr << "    Input file format '" << format << "' not supported." << endl;
		}
		return r;
	}

	// this test does not have a 'BODY'

	if (many == "single") {
		wx_distance_all_all__single(G);
	}
	else if (many == "all") {
		wx_distance_all_all__all(G);
	}
	else {
		cerr << ERROR("wx_distance_all_all.cpp", "wx_distance_all_all") << endl;
		cerr << "    Value of parameter 'many' is not valid." << endl;
		cerr << "    Received: '" << many << "'." << endl;
		return err_type::invalid_param;
	}

	delete G;
	G = nullptr;

	return err_type::no_error;
}

} // -- namespace exe_tests
