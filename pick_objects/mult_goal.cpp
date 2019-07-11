#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <visualization_msgs/Marker.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
/**
void callback(const visualization_msgs::Marker::ConstPtr& msg)
{
  move_base_msgs::MoveBaseGoal goal;
  MoveBaseClient ac("move_base", true);
  ROS_INFO("I received marker: [%f,%f,%f]", msg->pose.position.x, msg->pose.position.y,msg->pose.position.z); //store x,y,z position values

  ROS_INFO("I am here");
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

   // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  //goal.target_pose.pose.position.x = 3.7;//pick up point
  //goal.target_pose.pose.position.y = -0.3;
  //goal.target_pose.pose.orientation.w = 1.0;
  goal.target_pose.pose.position.x = msg->pose.position.x;//pick up point
  goal.target_pose.pose.position.y = msg->pose.position.y;
  goal.target_pose.pose.orientation.w = 1.0; 
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");  

}
**/
int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_ojects");
  ros::NodeHandle n;
  ros::Rate r(1);


  move_base_msgs::MoveBaseGoal goal;
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

   // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 3.7;//pick up point
  goal.target_pose.pose.position.y = -0.1;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, reack the pick up zone");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");    

 	sleep(5);
   // drop off goal

  move_base_msgs::MoveBaseGoal drop_goal;

  // set up the frame parameters
  drop_goal.target_pose.header.frame_id = "map";
  drop_goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  drop_goal.target_pose.pose.position.x = 3.7;
  drop_goal.target_pose.pose.position.y = -3.0;
  drop_goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop goal");
  ac.sendGoal(drop_goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("reached the drop off goal");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");
  
  ros::spin();
  return 0;
}