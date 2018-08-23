#include "driver.hpp"

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
		cout << "    * store-file FILE: store the graph into FILE in edge list format." << endl;
		cout << endl;
		cout << "    * read-file FILE: read an unweighted graph in edge list format from FILE." << endl;
		cout << endl;
		cout << "    * quit: exit the driver" << endl;
		cout << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++" << endl;
	}

	void driver_unweighted(bool directed) {
		uxgraph* G = nullptr;

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
			if (option == "help") {
				print_unweighted_options();
			}
			else if (option == "init") {
				size_t n;
				cin >> n;
				G->init(n);
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
				size_t N;
				cin >> N;

				if (G->is_directed()) {
					networks::classic::complete_graph(N, *(static_cast<udgraph *>(G)));
				}
				else {
					networks::classic::complete_graph(N, *(static_cast<uugraph *>(G)));
				}
			}
			else if (option == "linear-tree") {
				size_t N;
				cin >> N;

				if (G->is_directed()) {
					int d;
					cin >> d;
					networks::classic::linear_tree(N, *(static_cast<udgraph *>(G)), static_cast<uint8_t>(d));
				}
				else {
					networks::classic::linear_tree(N, *(static_cast<uugraph *>(G)));
				}
			}
			else if (option == "cycle-graph") {
				size_t N;
				cin >> N;

				if (G->is_directed()) {
					int d;
					cin >> d;
					networks::classic::cycle(N, *(static_cast<udgraph *>(G)), static_cast<uint8_t>(d));
				}
				else {
					networks::classic::cycle(N, *(static_cast<uugraph *>(G)));
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
			else if (option == "store-file") {
				string filename;
				cin >> filename;
				G->store_in_file(filename);
			}
			else if (option == "read-file") {
				string filename;
				cin >> filename;
				G->read_from_file(filename);
			}
			else if (option == "---") {
				cout << "-----------------------------------" << endl;
			}
			cout << "> ";
		}

		delete G;
	}
}
