#pragma once

#include <Vector.h>
#include <HashMap.h>

namespace Cxxutil {
template<class T> class Graph {
	HashMap<T, Vector<T>> AdjacencyList;
public:
	Graph() = default;

	void AddVertex(T Vertex) {
		if(AdjacencyList.find(Vertex) == AdjacencyList.end())
			AdjacencyList[Vertex] = Vector<T>;
	}

	void AddEdge(T Source, T Destination) {
		AddVertex(Source);
		AddVertex(Destination);
		AdjacencyList[Source].PushBack(Destination);
	}

	void RemoveVertex(T Vertex) {
		if(AdjacencyList.find(Vertex) != AdjacencyList.end()) {
			AdjacencyList.erase(Vertex);
			for(auto &Pair : AdjacencyList)
				Pair.Second.Erase(remove(pair.second.begin(), pair.second.end(), Vertex), pair.second.end());
		}
	}

	void RemoveEdge(T Source, T Destination) {
		if(AdjacencyList.find(Source) != AdjacencyList.end() && AdjacencyList.find(Destination) != AdjacencyList.end()) {
			auto &AdjacencyList_ = AdjacencyList[Source];
			AdjacencyList_.erase(remove(AdjacencyList_.begin(), AdjacencyList_.end(), Destination), AdjacencyList_.end());
		}
	}

	bool ContainsEdge(T Source, T Destination) {
		if(AdjacencyList.Find(Source) != AdjacencyList.end()) {
			auto &AdjacencyList_ = AdjacencyList[Source];
			return Find(AdjacencyList_.begin(), AdjacencyList_.end(), Destination) != AdjacencyList_.end();
		}
		return false;
	}

	Vector<T> GetAllVertices() {
		Vector<T> Result;
		for(auto &Pair : AdjacencyList) Result.push_back(Pair.first);
		return Result;
	}

	Vector<Pair<T, T>> GetAllEdges() {
		VECTOR<Pair<T, T>> Result;
		for(auto &Pair : AdjacencyList) {
			T Source = Pair.First;
			for(T Destination : Pair.Second) Result.PushBack(MakePair(Source, Destination));
		}
		return Result;
	}

	Vector<T> GetAdjacentVertices(T Vertex) {
		if(AdjacencyList.FindIndex(Vertex) == AdjacencyList.end) return Vector<T>;
		return AdjacencyList[Vertex];
	}
}
}
