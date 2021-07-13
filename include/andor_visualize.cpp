#include "andor_visualize.h"

VizGraph::VizGraph(string name)
{
	gname = name;
	g = new Graph(GraphP{name});
	dp.property("node_id", get(&VertexP::tag, *g));
	dp.property("label", get(&VertexP::tag, *g));
	dp.property("label", get(&EdgeP::symbol, *g));
	dp.property("rankdir", boost::make_constant_property<Graph *>(std::string("LR")));
	dp.property("dummy", boost::make_function_property_map<Graph *>([](Graph const *g) { return g->m_property->orientation; }));
}

VizGraph::Graph::vertex_descriptor VizGraph::addNode(string nodeName)
{
	return add_vertex(VertexP{nodeName}, *g);
}

void VizGraph::addEdge(string parentName, vector<string> childNames, string edgeName)
{
	Graph::vertex_descriptor p = addNode(parentName);
	for (string &cname : childNames)
	{
		Graph::vertex_descriptor c = addNode(cname);
		add_edge(p, c, EdgeP{edgeName}, *g);
	}
}

void VizGraph::saveGraph(string filePath)
{
	stringstream dot_ss;
	dot_ss << filePath << "0_" << gname << ".dot";
	string dot_file_name = dot_ss.str();
	ofstream dot_file(dot_file_name);

	stringstream dcmd_ss;
	dcmd_ss << "dot -Tpng " << dot_file_name << " -o " << filePath << "1_" << gname << ".png";
	string dcmd = dcmd_ss.str();

	write_graphviz_dp(dot_file, *g, dp);

	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(dcmd.c_str(), "r"), pclose);
	if (!pipe)
	{
		throw runtime_error("popen() failed!");
	}
}