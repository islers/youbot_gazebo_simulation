 
/******************************************************************************
* Copyright (c) 2014
* Locomotec
*
* Author:
* Stefan Isler
*
*
* Listens to brics_actuator JointPositions messages on
* 	- /arm_1/arm_controller/position_command
* 	- /arm_1/gripper_controller/position_command
* and republishes these as separate std_msgs/Float64 on
* 	- /arm_1/arm_controller/joint_i/command
* 
* The node is supposed to serve as an interface between the youbot control classes
* and its simulation in Gazebo to enable control of the arm and gripper joints.
*
******************************************************************************/

#include <iostream>
#include <assert.h>

#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"
#include "control_msgs/JointTrajectoryControllerState.h"
#include "brics_actuator/CartesianWrench.h"
#include "brics_actuator/JointValue.h"
#include <std_msgs/Float64.h>

#include <boost/units/io.hpp>

#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/conversion.hpp>

#include <iostream>
#include <assert.h>

#include "ros/ros.h"
#include "brics_actuator/JointPositions.h"

#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/io.hpp>

#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/conversion.hpp>

using namespace std;

vector<ros::Publisher> armPosRepublisher;
//ros::Publisher gripperPositionCommandRepublisher;

ros::Subscriber armPositionCommandListener;
//ros::Subscriber armGripperCommandListener;

void armInterface( const brics_actuator::JointPositionsConstPtr& _newPositions )
{
  if( _newPositions->positions.size()!=5 )
  {
    cout<<endl<<"Ignoring position command. It does not contain the expected number of joints for the youbot arm (5)."<<endl;
    return;
  }
  
  for( int i=0; i<5; i++ )
  {
    std_msgs::Float64 targetPosition;
    targetPosition.data = _newPositions->positions[i].value;
    armPosRepublisher[i].publish( targetPosition );
  }
    
  return;
}

/*void gripperInterface( const brics_actuator::JointPositionsConstPtr& _newPositions )
{
  //message to  be published
  trajectory_msgs::JointTrajectory toPublish;
  trajectory_msgs::JointTrajectoryPoint targetPosition;
  
  
  vector<brics_actuator::JointValue>::const_iterator firstPos = _newPositions->positions.begin();
  vector<brics_actuator::JointValue>::const_iterator endPos = _newPositions->positions.end();
  
  if( _newPositions->positions.size()>0 ) toPublish.header.stamp = _newPositions->positions[0].timeStamp;
  
  for( vector<brics_actuator::JointValue>::const_iterator it = firstPos; it!=endPos; it++ )
  {
    toPublish.joint_names.push_back( (*it).joint_uri );
    
    targetPosition.positions.push_back( (*it).value );
  }
  toPublish.points.push_back( targetPosition );
  
  //gripperPositionCommandRepublisher.publish( toPublish );
  
  return;
}*/

int main(int argc, char **argv) {

	ros::init(argc, argv, "ba_jointposition_listener");
	ros::NodeHandle n;
	
	armPosRepublisher.resize(5);
	armPosRepublisher[0] =  n.advertise<std_msgs::Float64>("arm_1/arm_controller/joint_1/command",1);
	armPosRepublisher[1] =  n.advertise<std_msgs::Float64>("arm_1/arm_controller/joint_2/command",1);
	armPosRepublisher[2] =  n.advertise<std_msgs::Float64>("arm_1/arm_controller/joint_3/command",1);
	armPosRepublisher[3] =  n.advertise<std_msgs::Float64>("arm_1/arm_controller/joint_4/command",1);
	armPosRepublisher[4] =  n.advertise<std_msgs::Float64>("arm_1/arm_controller/joint_5/command",1);
	
	//gripperPositionCommandRepublisher = n.advertise<trajectory_msgs::JointTrajectory>("arm_1/gripper_controller/command",100);
	
	armPositionCommandListener = n.subscribe("/arm_1/arm_controller/position_command",100, &armInterface );
	//armGripperCommandListener = n.subscribe("/arm_1/gripper_controller/position_command",100, &gripperInterface );
		
	cout<<endl<<"Listening on arm_1/arm_controller/position_command...";
	cout<<endl<<"Publishing on arm_1/arm_controller/joint_i/command..."<<endl;
	
	ros::spin();
	
	return 0;
}
