#include "driver.hpp"

#include <lgraph/graph_traversal/traversal_ux.hpp>
#include <lgraph/data_structures/node_path.hpp>
using namespace traversal;

namespace graph_driver {

	void print_unweighted_options() {
		cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "Options for the unweighted graph driver" << endl;
		cout << "---------------------------------------" << endl;
		cout << endl;
		cout << "    For the case of undirected graphs, an edge between two nodes U and V" << endl;
		cout << "    can be denoted indistinctintly as (U,V) or (V,U). For directed graphs," << endl;
		cout << "    however, this cannot be done and the order matters. Give edges accordingly." << endl;
		cout << endl;
		cout << "    * help: show the options of this driver" << endl;
		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "MAKING A GRAPH" << endl;
		cout << endl;
		cout << "    * init N: initialise the graph with N nodes. It is needed" << endl;
		cout << "        before being able to safely add edges." << endl;
		cout << endl;
		cout << "    * add-node: add a single to the graph" << endl;
		cout << endl;
		cout << "    * add-nodes N: adds N nodes to the graph" << endl;
		cout << endl;
		cout << "    * add-edge U V: add an edge (U,V)." << endl;
		cout << endl;
		cout << "    * add-edges N u1 v1 u2 v2 ... uN vN: add N edges. Each edge" << endl;
		cout << "        is a pair of nodes (ui,vi)." << endl;
		cout << endl;
		cout << "    * remove-edge U V: remove the edge (U,V)." << endl;
		cout << endl;
		cout << "    * remove-edges N u1 v1 u2 v2 ... uN vN: remove N edges. Each edge" << endl;
		cout << "        is a pair of nodes (ui,vi)." << endl;
		cout << endl;
		cout << "    * remove-node U: remove node U from the graph." << endl;
		cout << endl;
		cout << "    * get-edges: prints the list of edges." << endl;
		cout << endl;
		cout << "    -----------------------------------" << endl;
		cout << "    Classic graphs:" << endl;
		cout << endl;
		cout << "    * complete-graph N: make a complete graph of N vertices" << endl;
		cout << endl;
		cout << "    * linear-tree N (orientation): make a linear tree of N vertices" << endl;
		cout << "        If the graph is directed indicate the orientation with an integer" << endl;
		cout << "        from 1 to 3 for clockwise, counter-clockwise, or both orientations" << endl;
		cout << "        respectively." << endl;
		cout << endl;
		cout << "    * cycle-graph N (orientation): make a cycle graph of N vertices" << endl;
		cout << "        If the graph is directed indicate the orientation with an integer" << endl;
		cout << "        from 1 to 3 for clockwise, counter-clockwise, or both orientations" << endl;
		cout << "        respectively." << endl;
		cout << endl;
		cout << "    * star-graph N (orientation): make a star graph of N vertices" << endl;
		cout << "        If the graph is directed indicate the orientation with an integer" << endl;
		cout << "        from 1 to 3 for clockwise, counter-clockwise, or both orientations" << endl;
		cout << "        respectively." << endl;
		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "PATHS IN A GRAPH" << endl;
		cout << endl;
		cout << "    * find-one-st-path U V: finds one shortest path from node U to node V" << endl;
		cout << endl;
		cout << "    * find-all-st-path U V: finds all the shortest paths from node U to node V" << endl;
		cout << endl;
		cout << "    * find-one-s-path U: finds one shortest path between node U and all the other" << endl;
		cout << "        nodes in the graph." << endl;
		cout << endl;
		cout << "    * find-all-s-path U: finds all shortest paths between node U and all the other" << endl;
		cout << "        nodes in the graph." << endl;
		cout << endl;
		cout << "    * find-one-path: finds one shortest path between any pair of nodes in the graph" << endl;
		cout << endl;
		cout << "    * find-all-path: finds all shortest paths between any pair of nodes in the graph" << endl;
		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "STRUCTURE" << endl;
		cout << endl;
		cout << "    * connected-components: outputs the label of the connected component" << endl;
		cout << "        each vertex belongs to" << endl;
		cout << endl;
		cout << "---------------------------------------" << endl;
		cout << "MISCELLANEA" << endl;
		cout << endl;
		cout << "    * has-edge U V: outputs YES or NO depending on whether the graph" << endl;
		cout << "        has edge (U,V) or not" << endl;
		cout << endl;
		cout << "    * is-weighted: outputs YES if the graph is weighted. Outputs NO if otherwise" << endl;
		cout << endl;
		cout << "    * is-directed: outputs YES if the graph is directed. Outputs NO if otherwise" << endl;
		cout << endl;
		cout << "    * clear: clear the graph." << endl;
		cout << endl;
		cout << "    * print: for each node, print its neighbourhood into standard output." << endl;
		cout << endl;
		cout << "    * store-graph FORMAT FILE: store the graph into FILE using format FORMAT." << endl;
		cout << "        Allowed values for FORMAT:" << endl;
		cout << "        edge-list, graph6, sparse6, digraph6" << endl;
		cout << endl;
		cout << "    * read-file FORMAT FILE: read an unweighted graph format from FILE using format FORMAT." << endl;
		cout << "        Allowed values for FORMAT:" << endl;
		cout << "        edge-list, graph6, sparse6, digraph6" << endl;
		cout << endl;
		cout << "    * quit: exit the driver" << endl;
		cout << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
	}

	void driver_unweighted(bool directed) {
		uxgraph *G = nullptr;

		if (directed) {
			// do nothing
			cout << "Execute driver for directed graphs" << endl;
			G = new udgraph();
		}
		else {
			cout << "Execute driver for undirected graphs" << endl;
			G = new uugraph();
		}

		string option;
		cout << "> ";
		while (cin >> option and option != "quit") {
			timing::time_point begin = timing::now();

			if (option == "help") {
				print_unweighted_options();
			}
			else if (option == "init") {
				size_t n;
				cin >> n;
				G->init(n);
			}
			else if (option == "add-node") {
				G->add_node();
			}
			else if (option == "add-nodes") {
				size_t n;
				cin >> n;
				G->add_n_nodes(n);
			}
			else if (option == "add-edge") {
				node u,v;
				cin >> u >> v;

				G->add_edge(u, v);
			}
			else if (option == "add-edges") {
				size_t n;
				cin >> n;

				node u,v;
				for (size_t i = 0; i < n; ++i) {
					cin >> u >> v;
					G->add_edge(u, v);
				}
			}
			else if (option == "has-edge") {
				node u,v;
				cin >> u >> v;
				cout << "Does graph has edge (" << u << "," << v << ")? "
					 << (G->has_edge(u,v) ? "Yes" : "No") << endl;
			}
			else if (option == "remove-edge") {
				node u,v;
				cin >> u >> v;

				G->remove_edge(u, v);
			}
			else if (option == "remove-edges") {
				size_t n;
				cin >> n;

				node u,v;
				for (size_t i = 0; i < n; ++i) {
					cin >> u >> v;
					G->remove_edge(u, v);
				}
			}
			else if (option == "remove-node") {
				node u;
				cin >> u;

				G->remove_node(u);
			}
			else if (option == "get-edges") {
				vector<edge> all_edges;
				G->edges(all_edges);
				for (const edge& e : all_edges) {
					cout << "(" << e.first << "," << e.second << ")" << endl;
				}
				cout << endl;
			}
			else if (option == "complete-graph") {
				G->clear();

				size_t N;
				cin >> N;

				if (G->is_directed()) {
					complete_graph(N, *(static_cast<udgraph *>(G)));
				}
				else {
					complete_graph(N, *(static_cast<uugraph *>(G)));
				}
			}
			else if (option == "linear-tree") {
				G->clear();

				size_t N;
				cin >> N;

				if (G->is_directed()) {
					int d;
					cin >> d;
					linear_tree(N, *(static_cast<udgraph *>(G)), static_cast<uint8_t>(d));
				}
				else {
					linear_tree(N, *(static_cast<uugraph *>(G)));
				}
			}
			else if (option == "cycle-graph") {
				G->clear();

				size_t N;
				cin >> N;

				if (G->is_directed()) {
					int d;
					cin >> d;
					cycle_graph(N, *(static_cast<udgraph *>(G)), static_cast<uint8_t>(d));
				}
				else {
					cycle_graph(N, *(static_cast<uugraph *>(G)));
				}
			}
			else if (option == "star-graph") {
				G->clear();

				size_t N;
				cin >> N;

				if (G->is_directed()) {
					int d;
					cin >> d;
					star_graph(N, *(static_cast<udgraph *>(G)), static_cast<uint8_t>(d));
				}
				else {
					star_graph(N, *(static_cast<uugraph *>(G)));
				}
			}
			else if (option == "find-one-st-path") {
				node u,v;
				cin >> u >> v;
				node_path<_new_> p;
				uxpath(G, u, v, p);
				cout << p << endl;
			}
			else if (option == "find-all-st-path") {
				node u,v;
				cin >> u >> v;
				node_path_set<_new_> ps;
				uxpaths(G, u, v, ps);
				for (const node_path<_new_>& p : ps) {
					cout << "    " << p << endl;
				}
			}
			else if (option == "find-one-s-path") {
				node u;
				cin >> u;
				vector<node_path<_new_> > p;
				uxpath(G, u, p);
				for (node v = 0; v < G->n_nodes(); ++v) {
					cout << u << " -> " << v << ": " << p[v] << endl;
				}
			}
			else if (option == "find-all-s-path") {
				node u;
				cin >> u;
				vector<node_path_set<_new_> > ps;
				uxpaths(G, u, ps);
				for (node v = 0; v < G->n_nodes(); ++v) {
					cout << u << " -> " << v << ":" << endl;
					const node_path_set<_new_>& Puv = ps[v];
					for (const node_path<_new_>& p : Puv) {
						cout << "    " << p << endl;
					}
				}
			}
			else if (option == "find-one-path") {
				vector<vector<node_path<_new_> > > ps;
				uxpath(G, ps);
				for (node u = 0; u < G->n_nodes(); ++u) {
					for (node v = 0; v < G->n_nodes(); ++v) {
						cout << u << " -> " << v << ": " << ps[u][v] << endl;
					}
				}
			}
			else if (option == "find-all-path") {
				vector<vector<node_path_set<_new_> > > ps;
				uxpaths(G, ps);
				for (node u = 0; u < G->n_nodes(); ++u) {
					for (node v = 0; v < G->n_nodes(); ++v) {
						cout << u << " -> " << v << ":" << endl;
						const node_path_set<_new_>& Puv = ps[u][v];
						for (const node_path<_new_>& p : Puv) {
							cout << "    " << p << endl;
						}
					}
				}
			}
			else if (option == "connected-components") {
				vector<size_t> labels, bins;
				size_t n_comps;

				if (G->is_directed()) {
					udgraph *_G = static_cast<udgraph *>(G);
					n_comps = connected_components(*_G, labels, &bins);
				}
				else {
					uugraph *_G = static_cast<uugraph *>(G);
					n_comps = connected_components(*_G, labels, &bins);
				}

				cout << "There are in total " << n_comps << " connected components" << endl;
				for (node u = 0; u < G->n_nodes(); ++u) {
					cout << "    Node " << u << " is in component " << labels[u] << endl;
				}
				cout << "Each connected component has:" << endl;
				for (size_t i = 0; i < bins.size(); ++i) {
					cout << "    Component " << i << " has " << bins[i] << " nodes" << endl;
				}
				cout << endl;
			}
			else if (option == "is-weighted") {
				cout << "Is the graph weighted? "
					 << (G->is_weighted() ? "Yes" : "No") << endl;
			}
			else if (option == "is-directed") {
				cout << "Is the graph directed? "
					 << (G->is_directed() ? "Yes" : "No") << endl;
			}
			else if (option == "clear") {
				G->clear();
			}
			else if (option == "print") {
				cout << *G << endl;
			}
			else if (option == "store-graph") {
				string format, filename;
				cin >> format >> filename;
				if (format == "edge-list") {
					edge_list::write(filename, G);
				}
				else if (format == "graph6") {
					uugraph *Gu = static_cast<uugraph *>(G);
					graph6::write(filename, *Gu);
				}
				else if (format == "sparse6") {
					uugraph *Gu = static_cast<uugraph *>(G);
					sparse6::write(filename, *Gu);
				}
				else if (format == "digraph6") {
					udgraph *Gd = static_cast<udgraph *>(G);
					digraph6::write(filename, *Gd);
				}
			}
			else if (option == "read-file") {
				string format, filename;
				cin >> format >> filename;
				if (format == "edge-list") {
					edge_list::read(filename, G);
				}
				else if (format == "graph6") {
					uugraph *Gu = static_cast<uugraph *>(G);
					graph6::read(filename, *Gu);
				}
				else if (format == "sparse6") {
					uugraph *Gu = static_cast<uugraph *>(G);
					sparse6::read(filename, *Gu);
				}
				else if (format == "digraph6") {
					udgraph *Gd = static_cast<udgraph *>(G);
					digraph6::read(filename, *Gd);
				}
			}
			else if (option == "---") {
				cout << "-----------------------------------" << endl;
			}
			else {
				cout << "    Unknown option '" << option << "'" << endl;
			}

			timing::time_point end = timing::now();
			cout << "    In " << timing::elapsed_seconds(begin, end) << " seconds" << endl;

			cout << "> ";
		}

		delete G;
	}
}
