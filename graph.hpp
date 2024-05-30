#pragma once
#include <vector>
#include <unordered_map>
#include<iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class Vertex {
public:
    Vertex(){} 
    Vertex(int label) : _label(label) { }
    bool operator==(const Vertex& other) const {
        return _label == other._label;
    }
    ~Vertex(){}

    int _label = 0;
};

class Edge {
public:
    Edge() {}
	Edge(Vertex vert1, Vertex vert2) : _vert1(vert1), _vert2(vert2) { }
    bool operator==(const Edge& other) const {
        return (_vert1 == other._vert1) && (_vert2 == other._vert2);
    }
    ~Edge() {}

    Vertex _vert1;
    Vertex _vert2;
};

class Graph {
public:
    Graph() {}
    Graph(const std::vector <Vertex>& vertices,const std::vector<Edge>& edges) {
        _vertices = vertices;
        _edges = edges;
    }
    ~Graph() {}

    void addVertex(Vertex&);
	void addEdge(Edge&);
    void adjmaker(int, int);

    void insertGraph(const std::string&);
    void reprGraph(const std::string&);
    void generateGraph(const std::string&);

    void print();

    void APUtilDFS(int, std::vector<int>&, std::vector<int>&, std::vector<int>&);
    void findAPs_Tarjan();
    void printAP();

    void drawAP(const std::string&);
private:
    std::vector<Vertex> _vertices {0};
    std::vector<Edge> _edges {0};
    //it will be complicated to declare unordered_map with argument list of vertex and vector of edges 
    //consider vertex as int, and std::vector<int> as edges related with this vertex 
    // because vertex is just int label, edges just pair of int
    //std::unordered_map <Vertex, std::vector<Edge>> adj;
    std::unordered_map<int, std::vector<int>> adj;
    std::vector<bool> articulation_Point{false};
	
    
};
