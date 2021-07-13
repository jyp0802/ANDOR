
#ifndef AOVIZ_H
#define AOVIZ_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/function_property_map.hpp>
#include <cstdio>
#include <sstream>

using namespace std;

class VizGraph
{
public:
    struct VertexP { string tag; };
    struct EdgeP { string symbol; };
    struct GraphP { string orientation; };
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexP, EdgeP, GraphP, boost::listS> Graph;

    Graph* g;
    string gname;
    boost::dynamic_properties dp;
	vector<string> nodes_added;

	VizGraph(string name);

	Graph::vertex_descriptor addNode(string nodeName);
	void addEdge(string parentName, vector<string> childNames, string edgeName);
    void saveGraph(string filePath);

	//! destructor
	~VizGraph()
	{
	}

};

#endif