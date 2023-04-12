#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class T> class Graph {
	HASHMAP(T, VECTOR(T)) AdjacencyList;
public:
	Graph() = default;

	void AddVertex(T Vertex) {
		if(AdjacencyList.find(Vertex) == AdjacencyList.end()) AdjacencyList[Vertex] = VECTOR(T);
	}

	void AddEdge(T Source, T Destination) {
		AddVertex(Source);
		AddVertex(Destination);
		AdjacencyList[Source].push_back(Destination);
	}

	VECTOR(T) GetAdjacentVertices(T Vertex) {
		if(AdjacencyList.find(vertex) == AdjacencyList.end) return VECTOR(T);
		return AdjacencyList[Vertex];
	}
}
}
