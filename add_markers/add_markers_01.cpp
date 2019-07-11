#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>


class Marker_control {
public:
  Marker_control(){
    // Note : we provide the callback (a member) + a state (this)
    
    odom_subscriber = n.subscribe<nav_msgs::Odometry>("/odom", 100,Marker_control::odom_callback, this);
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    marker.header.stamp = ros::Time::now();
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
    ROS_INFO("I am in main, first time to show marker");    
  }

  static void odom_callback(const nav_msgs::Odometry::ConstPtr& odom) {
      
    drop_off_show_marker = false;
    show_marker = true;
      
    if ((odom->pose.pose.position.x >= 3.4f && odom->pose.pose.position.x <=3.75f) && (odom->pose.pose.position.y <= -0.8 && odom->pose.pose.position.y >= -0.13) && show_marker){
    //hide the marker and pause 5 seconds
        ROS_INFO("I am in marker call back function,reach pick up zone");

        drop_off_show_marker = false;
        show_marker = false;

    }
      
    if ((odom->pose.pose.position.x >= 3.4f && odom->pose.pose.position.x <=3.8f) && 
    (odom->pose.pose.position.y <= -2.80 && odom->pose.pose.position.y >= -3.2)){

        drop_off_show_marker = true;
        //show_marker = false;

    }
  }

  void run() {
    if (show_marker && (!drop_off_show_marker)) {
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
        ROS_INFO("I am in run,apporching to pick up zone,SHOW");
    }
    if ((!show_marker) && (!drop_off_show_marker)) {
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);        
        ROS_INFO("I am in run,reach pick up zone");
    }
    if (drop_off_show_marker){
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
        ROS_INFO("I am in run,reach drop off zone SHOW marker");
        // Publish the marker
        marker_pub.publish(marker); //public drop off marker         
    }
  }
protected:
  // state here
  
  ros::NodeHandle n;
  //ros::Rate r(int 1);
  ros::Subscriber odom_subscriber;
  visualization_msgs::Marker marker;
  ros::Publisher marker_pub;
  bool drop_off_show_marker;
  bool show_marker;
};

int main( int argc, char** argv )
{
  //ros::init(argc, argv, "add_markers");
  Marker_control marker_op(int argc, char** argv) ;
  marker_op.run();
  ROS_INFO("I am in main");
 // }
  //ros::spin();
  
}