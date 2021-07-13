/*!
 *===============================================================================//
 * Name			 :  andor_main.cpp
 * Author(s)	 :  Kourosh Darvish
 * Affiliation   :  University of Genoa, Italy - dept. DIBRIS
 * Version		 :  Hierarchical, First-Order-Logic, and Standard AND/OR graph
 * Description   : Main program using the AND-OR graph
 *===============================================================================//
 */

#include "andorCallback.h"
#include "andor_aograph.h"
#include "std_msgs/String.h"
#include <andor/Hyperarc.h>
#include <andor/Node.h>
#include <andor/andorSRV.h>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <ros/ros.h>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "andor");
	ros::NodeHandle nh;
    ros::NodeHandle nh_private("~");

	// const char *home = getenv("HOME");
	string andor_file_path, andor_file_name, andor_graph_name;


    nh_private.getParam("andor_graph_name", andor_graph_name);
    nh_private.getParam("andor_file_path", andor_file_path);
    nh_private.getParam("andor_file_name", andor_file_name);
	// andor_graph_name = "TableAssembly";                                        
	// andor_file_path += "/HRI/andor/catkin_ws/src/ANDOR/files/TableAssembly2/"; // path to the directory of the AND/OR graph
	// andor_file_name = "TableAssembly_hierarchical";                            // name of the text file of the AND/OR graph

	andorCallback callack_obj(andor_graph_name, andor_file_path, andor_file_name);
	ros::ServiceServer service = nh.advertiseService("andorService", &andorCallback::updateANDOR, &callack_obj);

	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		ros::spinOnce();
		loop_rate.sleep();
	}

	ros::spin();
	return 1;
};