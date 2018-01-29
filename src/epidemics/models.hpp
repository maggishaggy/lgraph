#pragma once

/// C++ includes
#include <vector>
using namespace std;

/// Custom includes
#include "src/random_generator.hpp"
#include "src/graph.hpp"

namespace dsa {

using namespace utils;

namespace networks {
namespace epidemics {
	
	/*
	Implementation of algorithms to simulate the spread of an infection
	over a network. We say that a non-infected agent is healhy.
	
	Epidemic models implemented are:
	- SIR: Susceptible -> Infected -> Recovered
	- SIS: Susceptible -> Infected -> Susceptible
	
	
	All methods follow the same convention for their input parameters:
	- G: the network over which the infection spreads
	- p0: initial proportion of infected individuals.
		0 <= p0 <= 1
	- beta: rate of infection of an individual with a single neighbour.
		0 <= beta <= 1
	- gamma: rate of recovery of an individual with a single neighbour.
		0 <= gamma <= 1
	- T: maximum number of steps of the simulation
	- rg: the random generator used to generate real uniform numbers
		between 0 and 1.
	
	Likewise for their output parameters:
	- n_inf: n_infected[i] contains the amount of infected nodes at step i.
		The number of healthy agents at step i can be obtained doing:
		n_healthy[i] = G.n_nodes() - n_inf[i]
	*/
	
	template<
		class G = default_random_engine,
		typename cT = float
	>
	void SIR
	(
		const graph& net,
		double p0, double beta, double gamma,
		size_t T,
		crandom_generator<> *rg,
		
		vector<size_t>& n_inf
	);
	
	template<
		class G = default_random_engine,
		typename cT = float
	>
	void SIS
	(
		const graph& net,
		double p0, double beta, double gamma,
		size_t T,
		crandom_generator<> *rg,
		
		vector<size_t>& n_inf
	);
	
	
} // -- namespace epidemics
} // -- namespace networks
} // -- namespace dsa

#include "sir.cpp"
#include "sis.cpp"
