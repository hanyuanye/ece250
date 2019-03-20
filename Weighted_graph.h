#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include <vector>
#include <deque>
#include <unordered_set>
#include <algorithm>
#include "Exception.h"

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

class Weighted_graph {
	private:
		static const double INF;
		// your choice
		int m_vertices;
		int m_edge_count;
		std::vector< std::vector<double> > adjacency;

		bool isFinished(std::vector<double>) const;
		void print() const;
		bool invalid_argument(int vertex) const;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;

		void insert( int, int, double );


	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Enter definitions for all public functions here

Weighted_graph::Weighted_graph(int vertices) {
	if (vertices < 0) throw illegal_argument();
	m_vertices = vertices;
	adjacency = std::vector<std::vector<double>>(vertices, std::vector<double>(vertices, INF));
}

Weighted_graph::~Weighted_graph() {

}

int Weighted_graph::degree(int vertex) const {
	if (invalid_argument(vertex)) throw illegal_argument();
	int degreeCount = 0;
	for (int i = 0; i < adjacency[vertex].size(); i++) {
		if (adjacency[vertex][i] != INF) {
			degreeCount++;
		}
	}
	return degreeCount;
}

int Weighted_graph::edge_count() const {
	return m_edge_count;
}

double Weighted_graph::adjacent(int m, int n) const {
	if (invalid_argument(m) || invalid_argument(n)) throw illegal_argument();
	if (m == n) return 0;
	return adjacency[m][n];
}

//Breadth first search implementation
bool Weighted_graph::is_connected() const {
	std::vector<int> visited(m_vertices, 0);
	std::deque<int> queue;
	auto current = 0;
	visited[current] = 1;
	queue.push_back(current);
	int count = 1;
	while (!queue.empty()) {
		current = queue.front();
		queue.pop_front();
		for (auto i = 0; i < adjacency[current].size(); i++) {
			if (visited[i] == 0 && adjacency[current][i] != INF) {
				visited[i] = 1;
				queue.push_back(i);
				count++;
			}
		}
	}

	//If the number of visited nodes isn't the total number of nodes, return false
	return count == m_vertices;
}

double Weighted_graph::minimum_spanning_tree(int vertice) const {
	//Current Problems: Somehow updating the weights of the vertexes wrong
	//Doing min across all edges, not the currently connected edges.
	if (invalid_argument(vertice)) throw illegal_argument();

	std::vector<int> mstVertices;
	double currWeight = 0;
	std::vector<double> inputVertices(m_vertices);
	for (int i = 0; i < inputVertices.size(); i++) {
		if (vertice == i) inputVertices[i] = 0;
		else inputVertices[i] = INF;
	}

	while (!isFinished(inputVertices)) {
		auto min = std::min_element(inputVertices.begin(), inputVertices.end());
		auto index = min - inputVertices.begin();
		mstVertices.push_back(index);
		currWeight += *min;
		for (auto i = 0; i < adjacency[index].size(); i++) {
			if (std::find(mstVertices.begin(), mstVertices.end(), i) != mstVertices.end()) continue;

			auto weight = adjacency[index][i];
			if (weight != INF) {
				if (weight < inputVertices[i]) {
					inputVertices[i] = weight;
				}
			}
		}
		inputVertices[index] = INF;
	}
	
	return currWeight;
}

void Weighted_graph::insert(int m, int n, double w) {
	auto weight = w;

	if (weight < 0 || weight == INF ||
		invalid_argument(m) || invalid_argument(n) ||
		m == n) throw illegal_argument();

	if (weight == 0) {
		weight = INF;
		m_edge_count--;
	}
	else {
		m_edge_count++;
	}

	adjacency[m][n] = weight;
	adjacency[n][m] = weight;
}

bool Weighted_graph::isFinished(std::vector<double> weights) const {
	for (auto w : weights) {
		if (w != INF) return false;
	}
	return true;
}

void Weighted_graph::print() const {
	for (auto v : adjacency) {
		for (auto w : v) {
			std::cout << w << " , ";
		}
		std::cout << std::endl;
	}
}

bool Weighted_graph::invalid_argument(int vertex) const {
	return vertex < 0 || vertex >= m_vertices;
}



std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}



#endif
