/*!
 *===============================================================================//
 * Name			 :  andor_main.cpp
 * Author(s)	 :  Kourosh Darvish
 * Affiliation   :  University of Genoa, Italy - dept. DIBRIS
 * Version		 :  Hierarchical, First-Order-Logic, and Standard AND/OR graph
 * Description   : Main program using the AND-OR graph
 *===============================================================================//
*/

#include <iostream>
#include <ros/ros.h>
#include "andor_aograph.h"
#include "std_msgs/String.h"
#include <andor/andorSRV.h>
#include <andor/Hyperarc.h>
#include <andor/Node.h>
#include <boost/shared_ptr.hpp>
#include "andorCallback.h"

using namespace std;

//vector<shared_ptr<AOgraph>> graphVector;// , OfflineGraphVector;
//double onlineElapse=0.0;
//ros::Publisher pub_ctrl_cmnd;
//
//bool updateANDOR(andor_msgs::andorSRV::Request &req, andor_msgs::andorSRV::Response &res){
//	cout<<FBLU("------------- andor receive request -------------")<<endl;
//	/*! when arrive a request:
//	 * 1- check for the graph name, if it is not valid, return and error
//	 * 2- if the solved nodes or hyper-arcs set is empty, it responds the query by the feasible nodes/hyper-arcs and costs pair sets
//	 * 3- if a node or hyper-arc is solved, it updates the graph, and responds the query by the feasible nodes/hyper-arcs and costs pair sets
//	 * 4- if the root node is solved, respond by setting the graphSolved=true
//	 */
//
//	double timeNow1,timeNow2;
//	// 1- check for the graph name
//	timeNow1=ros::Time::now().toSec();
//	int gIndex=-1; //! requested graph index number in graphVector, initialize wit random big value
//	for (int i=0;i<graphVector.size();i++)
//	{
//		string GraphName=req.graphName;
//		if(GraphName==graphVector[i]->gName)
//			gIndex=i;
//	}
//	// Check if the graph name which is coming from the query is correct
//
//	if (gIndex==-1){
//		cout<<FRED("Graph Name:'"<<req.graphName<<"' Is False, Not Found in Online or Offline Graph Vectors, Check Your Graph Name You Are Requesting")<<endl;
//		return false;
//	}
//	// graph name is correct!
//	else
//	{
//		if(req.solvedNodes.size()>0)
//		{
//			for (int i=0; i<req.solvedNodes.size();i++)
//			{
//				graphVector[gIndex]->solveByNameNode(req.solvedNodes[i].graphName, req.solvedNodes[i].nodeName);
//			}
//
//		}
//		if(req.solvedHyperarc.size()>0)
//		{
//			for (int i=0; i<req.solvedHyperarc.size();i++)
//			{
//				graphVector[gIndex]->solveByNameHyperarc(req.solvedHyperarc[i].graphName,req.solvedHyperarc[i].hyperarcName);
//			}
//
//		}
//		if (graphVector[gIndex]->isGraphSolved())
//		{
//			cout<<FGRN(BOLD("An And/Or graph is solved and deleted from vector of And/Or graphs; Name: "))<<graphVector[gIndex]->gName<<endl;
//			vector<shared_ptr<AOgraph>>::iterator it =graphVector.begin()+gIndex;
//			graphVector.erase(it);
//			res.graphSolved=true;
//			timeNow2=ros::Time::now().toSec();
//			onlineElapse+=timeNow2-timeNow1;
//			cout<<"online time: "<<onlineElapse<<endl;
//
//			std_msgs::String msgData;
//			msgData.data="Test_DONE";
//
//			pub_ctrl_cmnd.publish(msgData);
//		}
//		else
//		{
//
//			res.graphSolved=false;
//			vector<andor_msgs::Node> feasileNodeVector;
//			vector<andor_msgs::Hyperarc> feasileHyperarcVector;
//			graphVector[gIndex]->getFeasibleNode(feasileNodeVector);
//			graphVector[gIndex]->getFeasibleHyperarc(feasileHyperarcVector, feasileNodeVector);
//
//			for(int i=0;i<feasileHyperarcVector.size();i++)
//				res.feasibleHyperarcs.push_back(feasileHyperarcVector[i]);
//			for(int i=0;i<feasileNodeVector.size();i++)
//				res.feasibleNodes.push_back(feasileNodeVector[i]);
//
//			timeNow2=ros::Time::now().toSec();
//			onlineElapse+=timeNow2-timeNow1;
//
//		}
//
//	}
//
//	return true;
//}


/*!
 * Andor graph service name is "andorService"
 *
 *
 * */

int main(int argc, char **argv)
{
	ros::init(argc, argv, "andor");
	ros::NodeHandle nh;

	const char* home=getenv("HOME");
	string andor_file_path(home), andor_file_name, andor_graph_name ;

	andor_graph_name = ""; //!< Notice that, this name will be replaced with the name written in the and/or graph file description
	andor_file_path+="/catkin_ws/src/ANDOR/files/TRO-IKEAKitchenAssembly/"; //!< The path to the uploaded AND/OR graph
	andor_file_name="KitchenAssembly";                                    //!< The name of the uploaded AND/OR graph

	andorCallback callack_obj(andor_graph_name, andor_file_path, andor_file_name);
	ros::ServiceServer service = nh.advertiseService("andorService", &andorCallback::updateANDOR, &callack_obj); //!< The ROS service for querying from the AND/OR graph

	//DEL
//	graphVector.emplace_back(make_shared <AOgraph>(andor_graph_name));
//	double timeNow1,timeNow2, offlineElapse;
//	timeNow1=ros::Time::now().toSec();
//	graphVector.back()->loadFromFile(andor_file_path,andor_file_name);
//	timeNow2=ros::Time::now().toSec();
//	offlineElapse=timeNow2-timeNow1;
//
//	// print information of the AND/OR graph in terminal
//	cout << FGRN(BOLD("*****************")) << endl;
//	cout<<FGRN(BOLD("Graphs Name: "));
//	for(int i=0;i<graphVector.size();i++)
//		cout<<graphVector[i]->gName<<" , ";
//	cout<<endl;
//	cout<<"AND/OR graph offline phase time elapse: "<<offlineElapse<<" sec"<<endl;
//	cout << FGRN(BOLD("AND/OR graph is alive: ")) << endl;
	//DEL

	//////////////////////////////////////////////////////////////
	// IF YOU WANT TO TRY THE RUN_TESTER PROCESS, UNCOMENNT THE FOLLOWING LINES

	ros::Publisher pub_ctrl_cmnd=nh.advertise<std_msgs::String>("andorTester",80);
	std_msgs::String msgData;
	msgData.data="RUN_TESTER";
	int count=0;
	ros::Rate loop_rate(10);
	while(ros::ok() && count<10)
	{
		if (count==8)
			pub_ctrl_cmnd.publish(msgData);
		count++;
		ros::spinOnce();
		loop_rate.sleep();
	}
	//////////////////////////////////////////////////////////////

	ros::spin();
	return 1;
};

