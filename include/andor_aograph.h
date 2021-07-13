//===============================================================================//
// Name			 :  andor_aograph.h
// Author(s)	 :  Kourosh Darvish, Barbara Bruno, Yeshasvi Tirupachuri V.S.
// Affiliation   :  University of Genoa, Italy - dept. DIBRIS
// Version		 :  Hierarchical
// Description   :  AND/OR graph
//===============================================================================//


#ifndef AOGRAPH_H
#define AOGRAPH_H

#include <algorithm>
#include <fstream>

#include "andor_visualize.h"
#include "andor_aonode.h"
#include <andor/Hyperarc.h>
#include <andor/Node.h>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>

using namespace std;

//! class "Path" for each unique path traversing the graph from the head to the leaves
class Path
{        
public:
	int pIndex;                 //!< index of the path
	int pCost;                  //!< overall cost of all the nodes in the path
	bool pComplete;             //!< complete: the path fully traverses the graph
	vector<AOnode*> pathNodes;  //!< set of the nodes in the path
	vector<int> pathArcs;       //!< set of the hyperarcs in the path
	vector<bool> checkedNodes;  //!< checked: the node has been analysed
	vector<bool> checkedHyperarcs;//!< checked: the node has been analysed


	//! constructor of class Path
	//! @param[in] cost 	cost of the path
	//! @param[in] index 	unique index of the path
	Path(int cost, int index);

	//! copy constructor of class Path
	//! @param[in] &toBeCopied  path to be copied
	//! @param[in] index        unique index of the path
	Path(const Path &toBeCopied, int index);

	//! display path information
	void printPathInfo();

	//! add a node in the path
	//! @param[in] node     node to add to the path
	void addNode(AOnode* node);

	//! update the path information (when a node is met)
	//! @param[in] nameNode     name of the node
	//! @param[in] cost         cost to subtract from the path cost
	void updatePath(string nameNode, int cost);

	//! update the path information (when a node is met)
	//! @param[in] nameNode     name of the node
	//! @param[in] cost         cost to subtract from the path cost
	void updatePathNode(string nameNode, int cost);

	//! update the path information (when a hyper-arc is solved)
	//! @param[in] namehyperarc     name of the hyper-arc
	//! @param[in] cost         	cost to subtract from the path cost
	void updatePathHyperarc(string namehyperarc, int cost);

	//! find the feasible node to suggest
	//! @return node to suggest
	string suggestNode();

	//! destructor
	~Path()
	{
		//DEBUG:cout<<endl <<"Destroying Path object" <<endl;
		//			for(int i=0;i<pathNodes.size();i++)
		//				delete pathNodes[i];
		//			pathNodes.clear();
		//			pathArcs.clear();
		//			checkedNodes.clear();
		//			checkedHyperarcs.clear();
	}
};

//! class "AOgraph" for the AND-OR graph
class AOgraph
{    
protected:

	//! add a node in the graph
	//! @param[in] nameNode    name of the node
	//! @param[in] cost        generic node cost
	void addNode(string nameNode, int cost);

	//! add a hyper-arc in the graph
	//! @param[in] hyperarc    a Hyper-arc
	void addHyperarc(HyperArc* hyperarc);

	//! find a node by name
	//! @param[in] nameNode    name of the node
	//! @return	               pointer to the node with given name
	AOnode* findByName(string nameNode);

	//! find a hyper-arc by name
	//! @param[in] nameHyperarc		name of the hyper-arc
	//! @return						pointer to the hyper-arc with given name
	HyperArc* findByNameHyperarc(string nameHyperarc);



	//! update the feasibility status of the nodes and hyper-arcs in the graph
	void updateFeasibility();

	//! update the feasibility status of hyper-arcs in the graph
	void updateHyperarcFeasibility();

	//! compute the cost to add to a path: The adding cost equals to the node cost + the child hyper-arc cost with 'hIndex'
	//! @param[in] node     reference to the node to use for cost computation
	//! @param[in] hIndex   index of the node's child hyperarc to use for cost computation
	//! @return             cost to add to a path
	int computeAddCost(AOnode &node, int hIndex);

	//! generate all possible paths navigating the graph
	void generatePaths();

	//! set up a graph
	void setupGraph();

	//! find the hyperarc connecting a parent node to a child nodes
	//! @param[in] parent   	reference to the parent node
	//! @param[in] child    	reference to the child node
	//! @param[in] pathIndex	the path index value
	//! @return             	index of the hyperarc connecting the parent to the child
	HyperArc* findHyperarc(AOnode &parent, AOnode &child, int pathIndex);

	//! compute the overall updating cost (intermediate step to update the path cost)
	//! @param[in] node     reference to the node to use for cost computation
	//! @return             overall update cost (to subtract from the path cost)
	int computeOverallUpdate(AOnode &node);

	//! update all paths (update path costs when a node is solved)
	//! @param[in] solved       reference to the solved node (to use for paths costs update)
	void updatePaths(AOnode &solved);

	//! update the path information (when a node is met)
	//! @param[in] solved	the reference to the node object which is met
	void updatePaths_NodeSolved(AOnode &solved);

	//! update the path information (when a hyper-arc is solved)
	//! @param[in] solved     the reference to the hyper-arc object which is solved
	void updatePaths_HyperarcSolved(HyperArc &solved);

	//! finds a graph by its name
	//! @param[in] graphName	the name of the graph
	//! @return					pointer to the graph with the given name
	AOgraph* findGraph(string graphName);


	//! find the optimal path (long-sighted strategy)
	//! @return index of the optimal path (minimum cost)
	int findOptimalPath();

	//! write a brief description
	//! @param[in] previousOptimalPathIndex 	previous optimal path index
	//! @return		an integer index of the optimal path
	int findNextOptimalPath(int previousOptimalPathIndex);

public:
	string gName;           		//!< name of the graph
	vector<AOnode> graph;   		//!< set of nodes in the AND-OR graph
	vector<HyperArc*> graphHA;		//!< set of hyper-arcs in the AND-OR graph
	HyperArc* upperLevelHyperarc; 	//!< in case of hierarchical and/or graph, from a graph we can go the upper level hyper-arc.
	AOnode* head;           		//!< pointer to the node = final assembly
	vector<Path> paths;     		//!< set of paths in the AND-OR graph
	vector<int> pIndices;   		//!< indices of the updated paths
	vector<int> pUpdate;    		//!< costs subtracted to the updated paths
	vector<string> Nodes_solved_infeasible; //!< Nodes that become infeasible when an hyper-arc is solved

	//! constructor of class AOgraph
	//! @param[in] name 	name of the graph
	AOgraph(string name);

	//! load the graph description from a file
	//! @param[in] fileName    name of the file with the graph description
	//! @param[in] filePath    path to the file with the graph description
	void loadFromFile(string filePath, string fileName);

	//! display the graph information
	void printGraphInfo();

	//! suggests the node to solve
	//! @param[in] strategy     "0" = short-sighted, "1" = long-sighted (optimal)
	//! @return                 name of the suggested node
	string suggestNext(bool strategy);

	//! meets a node, finding it by the node name and the graph name which contains the node
	//! @param[in] graphName   name of the graph which contains the node
	//! @param[in] nameNode    name of the node
	void solveByNameNode(string graphName, string nameNode);

	//! solves a hyper-arc, finding it by the hyper-arc name and the graph name which contains the node
	//! @param[in] graphName    	name of the graph which contains the node
	//! @param[in] nameHyperarc		name of the hyper-arc
	void solveByNameHyperarc(string graphName,string nameHyperarc);

	//! finds all the feasible nodes and their costs
	//! @param[in] feasileNodeVector	the reference to the set of the feasible nodes, the containing graph name, and the cost in hierarchical AND/OR graph
	//! this function only returns only the feasible nodes in the current graph level, for the lower level and/or graph feasible nodes, we use getFeasibleHyperarc method.
	void getFeasibleNode(vector<andor::Node> &feasileNodeVector);

	//! Finds all the feasible hyper-arcs and their costs
	//! @param[in] feasileHyperarcVector   	the reference to the set of all the feasible hyper-arcs, their containing graph name, and the cost in hierarchical AND/OR graph
	//! @param[in] feasileNodeVector    	the reference to the set of all the feasible nodes (from the lower level graphs), their containing graph name, and the cost in hierarchical AND/OR graph
	void getFeasibleHyperarc(vector<andor::Hyperarc> &feasileHyperarcVector, vector<andor::Node> &feasileNodeVector);

	//! checks if an AND/OR graph is solved
	bool isGraphSolved(void);

	//! destructor
	~AOgraph()
	{
		//DEBUG:cout<<endl <<"Destroying AOgraph object" <<endl;
		//			for(int i=0;i<graphHA.size();i++)
		//				delete graphHA[i];
		//			graphHA.clear();
		//			delete head;
		//			paths.clear();
		//			pIndices.clear();
		//			pUpdate.clear();
		//			Nodes_solved_infeasible.clear();
	}

};

#endif
