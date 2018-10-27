#include <lgraph/utils/random_generator.hpp>

namespace lgraph {
namespace utils {

template<class G, typename dT>
drandom_generator<G,dT>::drandom_generator() : random_generator<G,dT>() {
	U = nullptr;
	B = nullptr;
}

template<class G, typename dT>
drandom_generator<G,dT>::~drandom_generator() {
	if (U != nullptr) {
		delete U;
	}
	if (B != nullptr) {
		delete B;
	}
}

/* Initialisers of the distributions */

template<class G, typename dT>
void drandom_generator<G,dT>::init_uniform(dT a, dT b) {
	if (U != nullptr) {
		delete U;
		U = nullptr;
	}
	U = new std::uniform_int_distribution<dT>(a, b);
}

template<class G, typename dT>
void drandom_generator<G,dT>::init_binomial(dT a, double p) {
	if (B != nullptr) {
		delete B;
		B = nullptr;
	}
	B = new std::binomial_distribution<dT>(a, p);
}

/* Get pseudo-random numbers */

template<class G, typename dT>
dT drandom_generator<G,dT>::get_uniform() {
	assert(U != nullptr);

	dT r = (*U)(random_generator<G,dT>::gen);
	return r;
}

template<class G, typename dT>
dT drandom_generator<G,dT>::get_binomial() {
	assert(B != nullptr);

	dT r = (*B)(random_generator<G,dT>::gen);
	return r;
}
	
} // -- namespace utils
} // -- namespace lgraph

