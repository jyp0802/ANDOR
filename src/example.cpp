#include <iostream>
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <andor/andorSRV.h>
#include <andor/Hyperarc.h>
#include <andor/Node.h>

#define RST "\x1B[0m"
#define KBLU "\x1B[34m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define FBLU(x) KBLU x RST
#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define BOLD(x) "\x1B[1m" x RST

using namespace std;

int main(int argc, char **argv)
{
	string andorGraphName;
	bool isGraphSolved;
	bool call_srv = false;
	bool ask_user = true;

	ros::init(argc, argv, "AndOr_example");
	ros::NodeHandle nh;
	ros::ServiceClient andorSRV_client = nh.serviceClient<andor::andorSRV>("andorService");
	ros::Rate loop_rate(40);

	cout << FGRN("- Insert AND/OR graph name: ");
	cin >> andorGraphName;
	cout << endl;

	int count = 0;
	while (ros::ok())
	{
		andor::andorSRV andor_srv;
		andor::andorSRV andor_srv0;
		andor_srv0.request.graphName = andorGraphName;

		if (ask_user)
		{

			andor_srv.request.graphName = andorGraphName;

			call_srv = false;
			ask_user = false;

			if (count > 0)
			{
				string stateName, type, graphName;
				cout << FGRN("Insert the following info for your intended solved node or hyperarc: [N(Node)/H(Hyper-arc)] [graph name] [state name]") << endl;
				cin >> type >> graphName >> stateName;
				cout << endl;

				if (type == "N" || type == "n")
				{
					call_srv = true;
					andor::Node solvedNode;
					solvedNode.nodeName = stateName;
					solvedNode.graphName = graphName;
					andor_srv.request.solvedNodes.push_back(solvedNode);
				}
				else if (type == "H" || type == "h")
				{
					call_srv = true;
					andor::Hyperarc solvedHA;
					solvedHA.hyperarcName = stateName;
					solvedHA.graphName = graphName;
					andor_srv.request.solvedHyperarc.push_back(solvedHA);
				}
				else
				{
					cout << FGRN("Please respond correctly the request, try again! ") << type << endl;
					ask_user = true;
				}
			}
			else
			{
				call_srv = true;
			}
		}

		if (call_srv)
		{
			if (andorSRV_client.call(andor_srv))
			{
				isGraphSolved = andor_srv.response.graphSolved;
				cout << FBLU("Is the graph solved: ") << isGraphSolved << endl;

				cout << FBLU("Feasible Nodes: [and/or graph name in hierarchy] [feasible node name] [cost]") << endl;
				for (int i = 0; i < andor_srv.response.feasibleNodes.size(); i++)
				{
					string feasbible_state_name = andor_srv.response.feasibleNodes[i].nodeName;
					string andorNameHierarchy = andor_srv.response.feasibleNodes[i].graphName;
					int cost = andor_srv.response.feasibleNodes[i].nodeCost;

					cout << i + 1 << ") " << andorNameHierarchy << " , " << feasbible_state_name << " , " << cost << endl;
				}
				cout << endl << FBLU("Feasible Hyper-arcs:: [and/or graph name in hierarchy] [feasible hyperarc name] [cost]") << endl;
				for (int i = 0; i < andor_srv.response.feasibleHyperarcs.size(); i++)
				{
					string feasbible_state_name = andor_srv.response.feasibleHyperarcs[i].hyperarcName;
					string andorNameHierarchy = andor_srv.response.feasibleHyperarcs[i].graphName;
					int cost = andor_srv.response.feasibleHyperarcs[i].hyperarcCost;

					cout << i + 1 << ") " << andorNameHierarchy << " , " << feasbible_state_name << " , " << cost << endl;
				}

				if (isGraphSolved)
					return 1;
			}
			call_srv = false;
			ask_user = true;
			cout << FGRN("*************************************************************") << endl;
		}
		ros::spinOnce();
		loop_rate.sleep();
		count++;
	}

	return 1;
}
