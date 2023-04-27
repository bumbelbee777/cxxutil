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

	void RemoveVertex(T Vertex) {
		if(AdjacencyList.find(Vertex) != AdjacencyList.end()) {
			AdjacencyList.erase(Vertex);
			for(auto &Pair : AdjacencyList) Pair.second.erase(remove(pair.second.begin(), pair.second.end(), Vertex), pair.second.end());
		}
	}

	void RemoveEdge(T Source, T Destination) {
		if(AdjacencyList.find(Source) != AdjacencyList.end() && AdjacencyList.find(Destination) != AdjacencyList.end()) {
			auto &AdjacencyList_ = AdjacencyList[Source];
			AdjacencyList_.erase(remove(AdjacencyList_.begin(), AdjacencyList_.end(), Destination), AdjacencyList_.end());
		}
	}

	bool ContainsEdge(T Source, T Destination) {
		if(AdjacencyList.find(Source) != AdjacencyList.end()) {
			auto &AdjacencyList_ = AdjacencyList[Source];
			return find(AdjacencyList_.begin(), AdjacencyList_.end(), Destination) != AdjacencyList_.end();
		}
		return false;
	}

	VECTOR(T) GetAllVertices() {
		VECTOR(T) Result;
		for(auto &Pair : AdjacencyList) Result.push_back(Pair.first);
		return Result;
	}

	VECTOR<PAIR<T, T>> GetAllEdges() {
		VECTOR<pair<T, T>> Result;
		for(auto &Pair : AdjacencyList) {
			T Source = Pair.first;
			for(T Destination : Pair.second) edges.push_back(make_pair(Source, Destination));
		}
		return Result;
	}

	VECTOR(T) GetAdjacentVertices(T Vertex) {
		if(AdjacencyList.find(Vertex) == AdjacencyList.end) return VECTOR(T);
		return AdjacencyList[Vertex];
	}
}
}
