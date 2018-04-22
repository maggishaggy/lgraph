#include "debug.hpp"

namespace debug {

	template<class T>
	void deb_distances_t(const xxgraph<T> *G, node source, node target) {
		const T N = G->n_nodes();
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "DISTANCES:" << endl;

		// node-node
		LOG.log() << "- node to node" << endl;
		size_t n_paths;
		T d1 = traversal::xwdistance(G, source, target);
		T d2 = traversal::xwdistance(G, source, target, n_paths);
		LOG.log() << "    Distance from " << source << " to " << target << ": ";
		if (d1 == utils::inf_t<T>() or d2 == utils::inf_t<T>()) LOG.log() << "inf";
		else {
			LOG.log() << d1 << " -- " << d2;
			if (d1 != d2) {
				cout << " distances disagree! " << endl;
			}
		}
		LOG.log() << " (" << n_paths << ")" << endl;

		// node-all
		LOG.log() << "- node to all" << endl;
		vector<T> ds;
		vector<size_t> va_n_paths;
		traversal::xwdistance<T>(G, source, ds, va_n_paths);
		if (va_n_paths.size() > 0) {
			for (size_t i = 0; i < N; ++i) {
				LOG.log() << "    Distance from " << source << " to " << i << ": ";
				if (ds[i] == utils::inf_t<T>()) LOG.log() << "inf";
				else LOG.log() << ds[i] << " (" << va_n_paths[i] << ")";
				LOG.log() << endl;
			}
		}
		else {
			LOG.log() << "EMPTY!" << endl;
		}

		// all-all
		vector<vector<T> > all_ds;
		vector<vector<size_t> > all_n_paths;
		traversal::xwdistances(G, all_ds, all_n_paths);
		LOG.log() << "- all to all" << endl;
		print_distance_matrix(all_ds, all_n_paths);
	}

	template<class T>
	void deb_paths_t(const xxgraph<T> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "SINGLE NODE PATHS:" << endl;

		// node-node
		LOG.log() << "- node to node" << endl;
		node_path<T> p;
		traversal::xwpath(G, source, target, p);
		LOG.log() << "    Path from " << source << " to " << target << ": ";
		if (p.size() > 0) LOG.log() << p;
		else LOG.log() << "No path!";
		LOG.log() << endl;

		// node-all
		LOG.log() << "- node to all" << endl;
		vector<node_path<T> > ps;
		traversal::xwpath(G, source, ps);
		if (ps.size() > 0) {
			for (node target = 0; target < G->n_nodes(); ++target) {
				LOG.log() << "    Path from " << source << " to " << target << ": ";
				if (ps[target].size() > 0) LOG.log() << ps[target];
				else LOG.log() << "No path!";
				LOG.log() << endl;
			}
		}
		else {
			LOG.log() << "EMPTY!" << endl;
		}

		// all-all
		LOG.log() << "- all to all" << endl;
		vector<node_path_set<T> > all_ps;
		traversal::xwpath(G, all_ps);
		if (all_ps.size() > 0) {
			for (node source = 0; source < G->n_nodes(); ++source) {
				for (node target = 0; target < G->n_nodes(); ++target) {
					LOG.log() << "    Path from " << source << " to " << target << ": ";
					if (all_ps[source][target].size() > 0) LOG.log() << all_ps[source][target];
					else LOG.log() << "No path!";
					LOG.log() << endl;
				}
			}
		}
		else {
			LOG.log() << "    EMPTY!" << endl;
		}
	}

	template<class T>
	void deb_all_paths_t(const xxgraph<T> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "ALL NODE SHORTEST PATHS:" << endl;

		// node-node
		LOG.log() << "- node to node" << endl;
		node_path_set<T> node_node_ps;
		traversal::xwpaths(G, source, target, node_node_ps);
		LOG.log() << "    paths from " << source << " to " << target << ": ";
		if (node_node_ps.size() == 0) {
			LOG.log() << "No paths" << endl;
		}
		else {
			LOG.log() << endl;
			for (const node_path<T>& path : node_node_ps) {
				LOG.log() << "        " << path << endl;
			}
		}

		// node-all
		LOG.log() << "- node to all" << endl;
		vector<node_path_set<T> > node_all_ps;
		traversal::xwpaths(G, source, node_all_ps);
		for (node target = 0; target < G->n_nodes(); ++target) {
			LOG.log() << "    Paths from " << source << " to " << target << ": ";
			const node_path_set<T>& paths_to_target = node_all_ps[target];
			if (paths_to_target.size() == 0) {
				LOG.log() << "No paths" << endl;
			}
			else {
				LOG.log() << endl;
				for (const node_path<T>& path : paths_to_target) {
					LOG.log() << string(8, ' ') << path << endl;
				}
			}
		}

		// all-all
		LOG.log() << "- all to all" << endl;
		vector<vector<node_path_set<T> > > all_all_paths;
		traversal::xwpaths(G, all_all_paths);
		for (node source = 0; source < G->n_nodes(); ++source) {
			for (node target = 0; target < G->n_nodes(); ++target) {

				LOG.log() << "    Paths from " << source << " to " << target << ": ";
				const node_path_set<T>& paths_to_target = all_all_paths[source][target];
				if (paths_to_target.size() == 0) {
					LOG.log() << "No paths" << endl;
				}
				else {
					LOG.log() << endl;
					for (const node_path<T>& path : paths_to_target) {
						LOG.log() << string(8, ' ') << path << endl;
					}
				}
			}
		}
	}

	template<class T>
	void deb_bpaths_t(const xxgraph<T> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "SINGLE BOOLEAN PATHS:" << endl;

		// node-node
		LOG.log() << "- node to node" << endl;
		boolean_path<T> p;
		traversal::xwpath(G, source, target, p);
		LOG.log() << "    Path from " << source << " to " << target << ": ";
		if (p.size() > 0) {
			LOG.log() << p.to_node_path(G, source);
		}
		else {
			LOG.log() << "No path!";
		}
		LOG.log() << endl;

		// node-all
		LOG.log() << "- node to all" << endl;
		vector<boolean_path<T> > ps;
		traversal::xwpath(G, source, ps);
		for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
			LOG.log() << "    Path from " << source << " to " << TARGET << ": ";
			if (ps[TARGET].size() > 0) {
				LOG.log() << ps[TARGET].to_node_path(G, source);
			}
			else {
				LOG.log() << "No path!";
			}
			LOG.log() << endl;
		}

		// all-all
		LOG.log() << "- all to all" << endl;
		vector<vector<boolean_path<T> > > all_ps;
		traversal::xwpath(G, all_ps);
		for (node SOURCE = 0; SOURCE < G->n_nodes(); ++SOURCE) {
			for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
				LOG.log() << "    Path from " << SOURCE << " to " << TARGET << ": ";
				if (all_ps[SOURCE][TARGET].size() > 0) {
					LOG.log() << all_ps[SOURCE][TARGET].to_node_path(G, SOURCE);
				}
				else {
					LOG.log() << "No path!";
				}
				LOG.log() << endl;
			}
		}
	}

	template<class T>
	void deb_all_bpaths_t(const xxgraph<T> *G, node source, node target) {
		logger<cout_stream>& LOG = logger<cout_stream>::get_logger();

		LOG.log() << "ALL BOOLEAN SHORTEST PATHS:" << endl;

		// node-node
		LOG.log() << "- node to node" << endl;
		boolean_path_set<T> node_node_paths;
		traversal::xwpaths(G, source, target, node_node_paths);
		LOG.log() << "    paths from " << source << " to " << target << ": ";
		if (node_node_paths.size() == 0) {
			LOG.log() << "No paths" << endl;
		}
		else {
			LOG.log() << endl;
			for (const boolean_path<T>& path : node_node_paths) {
				LOG.log() << "        " << path.to_node_path(G, source) << endl;
			}
		}

		// node-all
		LOG.log() << "- node to all" << endl;
		vector<boolean_path_set<T> > node_all_paths;
		traversal::xwpaths(G, source, node_all_paths);
		for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {
			LOG.log() << "    Paths from " << source << " to " << TARGET << ": ";
			const boolean_path_set<T>& paths_to_target = node_all_paths[TARGET];
			if (paths_to_target.size() == 0) {
				LOG.log() << "No paths" << endl;
			}
			else {
				LOG.log() << endl;
				for (const boolean_path<T>& path : paths_to_target) {
					LOG.log() << string(8, ' ') << path.to_node_path(G, source) << endl;
				}
			}
		}

		// all-all
		LOG.log() << "- all to all" << endl;
		vector<vector<boolean_path_set<T> > > all_all_paths;
		traversal::xwpaths(G, all_all_paths);
		for (node SOURCE = 0; SOURCE < G->n_nodes(); ++SOURCE) {
			for (node TARGET = 0; TARGET < G->n_nodes(); ++TARGET) {

				LOG.log() << "    Paths from " << SOURCE << " to " << TARGET << ": ";
				const boolean_path_set<T>& paths_to_target = all_all_paths[SOURCE][TARGET];
				if (paths_to_target.size() == 0) {
					LOG.log() << "No paths" << endl;
				}
				else {
					LOG.log() << endl;
					for (const boolean_path<T>& path : paths_to_target) {
						LOG.log() << string(8, ' ') << path.to_node_path(G, SOURCE) << endl;
					}
				}
			}
		}
	}

}
