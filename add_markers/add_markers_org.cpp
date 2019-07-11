#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
static bool show_marker = false;
static bool drop_off_show_marker = false;
void odom_callback(const nav_msgs::Odometry::ConstPtr& odom)
{
  
  	
  ROS_INFO("I received odom: [%f,%f,%f]", odom->pose.pose.position.x, odom->pose.pose.position.y,odom->pose.pose.position.z); //store x,y,z position values
  ros::NodeHandle n;
  ros::Rate r(1);
  visualization_msgs::Marker marker;
  marker.header.stamp = ros::Time::now();
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    
  if ( ! show_marker){

    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0; 
    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;    

    marker.pose.position.x = 3.7f;
    marker.pose.position.y = -0.1f;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;
    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration(); 
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    show_marker = true;
    ROS_INFO("I am in callback, first time to show marker");
  }
  if ((odom->pose.pose.position.x >= 3.4f && odom->pose.pose.position.x <=3.75f) && (odom->pose.pose.position.y <= -0.8 && odom->pose.pose.position.y >= -0.13) && show_marker){
    //hide the marker and pause 5 seconds
    ROS_INFO("I am in marker call back function,reach pick up zone");
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    //show_marker=false;
    drop_off_show_marker = true;
 
   }
  if ((odom->pose.pose.position.x >= 3.4f && odom->pose.pose.position.x <=3.8f) && (odom->pose.pose.position.y <= -2.80 && odom->pose.pose.position.y >= -3.2) && drop_off_show_marker ){

    // ADD the marker in drop out zone.
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 3.7f;
    marker.pose.position.y = -3.0;
    marker.pose.position.z = 0;
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;
    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;
    ROS_INFO("I am in main,reach drop off zone SHOW marker");
    // Publish the marker
    marker_pub.publish(marker); //public drop off marker 
  
  }

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  show_marker = false;
  drop_off_show_marker = false;
  //ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //subscribe to odom added by  kz
  ros::Subscriber odom_subscriber;
  // Subscribe to the /odom topic and call the odom_callback function

  odom_subscriber = n.subscribe<nav_msgs::Odometry>("/odom", 100,odom_callback); 
  //ROS_INFO("I am marker in main function after odom_sub");
 // }
  //ros::spin();
  
}