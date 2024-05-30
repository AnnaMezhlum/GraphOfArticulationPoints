#include "graph.hpp"

void Graph::addVertex(Vertex& vertex) {
    for(Vertex vert : _vertices) {
        if (vert == vertex) {
            return;
        }
    }
    _vertices.push_back(vertex);
}
void Graph::addEdge(Edge& edge) {
    for(Edge ed : _edges) {
        if(ed == edge) {
            return;
        }
    }
    _edges.push_back(edge);
}
void Graph::adjmaker(int u, int v) {
    adj[v].push_back(u);
    adj[u].push_back(v);
    Vertex v1(u),v2(v);
    addVertex(v1);
    addVertex(v2);
    Edge ed(v1,v2);
    addEdge(ed);
}

void Graph:: insertGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    int u, v;
    std::cout << "\nInsert graph: \n";
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> u >> v) {
            std::cout << "Adding edge: " << u << " " << v << std::endl;
            adjmaker(u,v);

        } else {
            std::cerr << "Failed to parse line: " << line << std::endl;
        }
    }

    file.close();
    this->reprGraph("inputGraph.dot");
}
void Graph::reprGraph(const std::string& filename) {
    if (adj.empty()) {
        std::cerr << "Adjacency  is empty. Nothing to represent" << std::endl;
        return;
    }

    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    outfile << "Graph G {" << std::endl;
    for (auto i = 0; i < _edges.size(); ++i) {
        outfile << _edges[i]._vert1._label << " -- " << _edges[i]._vert2._label << ";" << std::endl;
    }
    outfile << "}\n";
    outfile.close();
    std::cout << "DOT file generated: " << filename << std::endl;

    generateGraph(filename);
}
void Graph::generateGraph(const std::string& filename) {
    std::string output_filename = filename + ".png";
    std::string command = "dot -Tpng " + filename + " -o " + output_filename;
    int status = std::system(command.c_str());
    if (status != 0) {
        std::cerr << "Error generating graph PNG image." << std::endl;
    } else {
        std::cout << "Graph PNG image generated: " << output_filename << std::endl;
    }
}

void Graph::print() {
    std::cout << "Printing graph:" << std::endl;
    if (adj.empty()) {
        for (auto v : _vertices) {
            std::cout << "Adjacency list of vertex " << v._label << ": ";
            for (auto element : adj.at(v._label)){
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Edges: ";
        for (auto el : _edges) {
            std::cout << el._vert1._label << " " << el._vert2._label << " " ;
        }
        std::cout << std::endl;
    } else {
        std::cout << "Adjacency list is empty." << std::endl;
    }
}
void Graph::APUtilDFS(int u, std::vector<int>& disc, std::vector<int>& low, std::vector<int>& parent) {
    static int time = 0;
	disc[u] = low[u] = time;
	time += 1;
	int children = 0;

	for(int v : adj[u]) {
		if(disc[v] == -1){//If v is not visited
			children += 1;
			parent[v] = u;
			APUtilDFS(v, disc, low, parent);
			low[u] = std::min(low[u], low[v]);

			if(parent[u] == -1 and children > 1) {	//Case-1: U is root
				articulation_Point[u] = true;
            }
			if(parent[u] != -1 and low[v] >= disc[u]){	//Case-2: Atleast 1 component will get separated
				articulation_Point[u] = true;
            }
		}
		else if(v != parent[u]){	//Ignore child to parent edge
			low[u] = std::min(low[u], disc[v]);
        }
	}
}
void Graph::findAPs_Tarjan(){
    std::vector<int> disc(_vertices.size(), -1), low(_vertices.size(), -1), parent(_vertices.size(), -1);
	//std::vector<bool> articulation_Point(_vertices.size(), false);	//Avoids cross-edge

	for(int i = 0; i < _vertices.size(); ++i){
		if(disc[i] == -1){
			APUtilDFS(i,disc,low,parent);
        }
    }
    drawAP("APGraph.dot");

}
void Graph:: printAP() {
	std::cout<<"\nArticulation Points are: ";
	for(int i = 0; i <_vertices.size(); ++i){
		if(articulation_Point[i] == true){
			std::cout<< i << " ";
        }
    }
}
void Graph::drawAP(const std::string& filename){
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    outfile << "Graph G {" << std::endl;
    for (int i = 0; i < _vertices.size(); ++i) {
        if(articulation_Point[i] ){
            for(auto t : adj[i]) {
                if(articulation_Point[t] && _vertices[i]._label < _vertices[t]._label) {
                    outfile << _vertices[i]._label << " -- " << _vertices[t]._label << ";" << std::endl; 
                }
            }

        }
    }
    outfile << "}\n";
    outfile.close();
    std::cout << "DOT file generated: " << filename << std::endl;

    generateGraph(filename);
}


int main() {
    Graph obj;
    obj.insertGraph("graph.txt");
    obj.findAPs_Tarjan();
    obj.printAP();
    return 0;
}
