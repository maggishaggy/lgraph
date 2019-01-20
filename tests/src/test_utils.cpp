#include "src/test_utils.hpp"

// C includes
#include <assert.h>

// C++ includes
#include <iostream>
using namespace std;

// lgraph includes
#include <lgraph/data_structures/node_path.hpp>
using namespace lgraph;

// custom includes
#include "definitions.hpp"

namespace test_utils {

bool comp_ux_paths(const node_path<_new_>& p, const node_path<_new_>& q) {
	// in this case, if the two paths are the shortest then
	// they must have the same number of nodes. They are
	// unweighted paths.
	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i] < q[i]) {
			return true;
		}
		else if (p[i] > q[i]) {
			return false;
		}
	}

	// same path! Should never happen
	cerr << ERROR("test_utils.cpp", "comp_ux_paths") << endl;
	cerr << "    Fatal: comparing two equal paths." << endl;
	cerr << "    Aborting..." << endl;
	assert(false);
}

} // -- namespace test_utils

