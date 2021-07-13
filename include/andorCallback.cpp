#include "andorCallback.h"

andorCallback::andorCallback(string andor_graph_name, string andor_file_path, string andor_file_name)
{
	onlineElapse = 0.0;
	offlineElapse = 0.0;

	double time1, time2;

	time1 = ros::Time::now().toSec();

	graphVector.emplace_back(make_shared<AOgraph>(andor_graph_name));
	graphVector.back()->loadFromFile(andor_file_path, andor_file_name);

	time2 = ros::Time::now().toSec();
	offlineElapse = time2 - time1;

	cout << FGRN(BOLD("*************************************")) << endl;
	cout << FGRN(BOLD("Graphs Name: "));
	for (int i = 0; i < graphVector.size(); i++)
		cout << graphVector[i]->gName << " , ";
	cout << endl;
	cout << "AND/OR graph offline phase time elapse: " << offlineElapse << " sec" << endl;
	cout << FGRN(BOLD("AND/OR graph is alive... ")) << endl;
	cout << FGRN(BOLD("*************************************")) << endl;
};

andorCallback::~andorCallback(){};

bool andorCallback::updateANDOR(andor::andorSRV::Request &req, andor::andorSRV::Response &res)
{
	cout << FBLU("------------- andor receive request -------------") << endl;
	/*! when arrive a request:
	 * 1- check for the graph name, if it is not valid, return and error
	 * 2- if the solved nodes or hyper-arcs set is empty, it responds the query by the feasible nodes/hyper-arcs and costs pair sets
	 * 3- if a node or hyper-arc is solved, it updates the graph, and responds the query by the feasible nodes/hyper-arcs and costs pair sets
	 * 4- if the root node is solved, respond by setting the graphSolved=true
	 */

	double time1, time2;
	// 1- check for the graph name
	time1 = ros::Time::now().toSec();
	int gIndex = -1; //! requested graph index number in graphVector, initialize wit random big value
	string GraphName = req.graphName;
	for (int i = 0; i < graphVector.size(); i++)
	{
		if (GraphName == graphVector[i]->gName)
			gIndex = i;
	}

	// Check if the graph name which is coming from the query is correct
	if (gIndex == -1)
	{
		cout << FRED("Graph Name:'" << req.graphName << "' Is False, Not Found in graph vector, check the graph name you are requesting") << endl;
		return false;
	}

	// graph name is correct!
	if (req.solvedNodes.size() > 0)
	{
		for (int i = 0; i < req.solvedNodes.size(); i++)
		{
			graphVector[gIndex]->solveByNameNode(req.solvedNodes[i].graphName, req.solvedNodes[i].nodeName);
		}
	}
	if (req.solvedHyperarc.size() > 0)
	{
		for (int i = 0; i < req.solvedHyperarc.size(); i++)
		{
			graphVector[gIndex]->solveByNameHyperarc(req.solvedHyperarc[i].graphName, req.solvedHyperarc[i].hyperarcName);
		}
	}
	if (graphVector[gIndex]->isGraphSolved())
	{
		cout << FGRN(BOLD("An And/Or graph is solved and deleted from vector of And/Or graphs; Name: ")) << graphVector[gIndex]->gName << endl;
		vector<shared_ptr<AOgraph>>::iterator it = graphVector.begin() + gIndex;
		graphVector.erase(it);
		res.graphSolved = true;
		time2 = ros::Time::now().toSec();
		onlineElapse += time2 - time1;
		cout << "online time: " << onlineElapse << endl;
	}
	else
	{
		res.graphSolved = false;
		vector<andor::Node> feasileNodeVector;
		vector<andor::Hyperarc> feasileHyperarcVector;
		graphVector[gIndex]->getFeasibleNode(feasileNodeVector);
		graphVector[gIndex]->getFeasibleHyperarc(feasileHyperarcVector, feasileNodeVector);

		for (int i = 0; i < feasileHyperarcVector.size(); i++)
			res.feasibleHyperarcs.push_back(feasileHyperarcVector[i]);
		for (int i = 0; i < feasileNodeVector.size(); i++)
			res.feasibleNodes.push_back(feasileNodeVector[i]);

		time2 = ros::Time::now().toSec();
		onlineElapse += time2 - time1;
	}

	return true;
};
