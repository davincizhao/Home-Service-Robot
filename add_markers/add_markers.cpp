#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

using namespace std;

class Marker_control{
    protected:  
        ros::Subscriber odom_subscriber;
        visualization_msgs::Marker marker;
        ros::Publisher marker_pub;
        bool drop_off_show_marker;
        bool show_marker;
     public:
        Marker_control(int argc, char** argv);
        void odom_callback(const nav_msgs::Odometry::ConstPtr& odom);
        void run();
};

Marker_control::Marker_control(int argc, char** argv){
    // Note : we provide the callback (a member) + a state (this)
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ROS_INFO("I am in class creator");
    odom_subscriber = n.subscribe<nav_msgs::Odometry>("/odom", 1,&Marker_control::odom_callback,this);
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
    drop_off_show_marker = false;
    
  
  }

void Marker_control::odom_callback(const nav_msgs::Odometry::ConstPtr& odom) {
     ROS_INFO("I am in  callback ,odom x:%f,y:%f",odom->pose.pose.position.x,odom->pose.pose.position.y); 
      
    if ((odom->pose.pose.position.x >= 3.4f && odom->pose.pose.position.x <=3.75f) && 
    (odom->pose.pose.position.y >= -0.19 && odom->pose.pose.position.y <= -0.13) && show_marker){
    //hide the marker and pause 5 seconds
        ROS_INFO("I am in  callback function,reachED pick up zone");

        drop_off_show_marker = false;
        show_marker = false;
        
    }
      
    if ((odom->pose.pose.position.x >= 3.4f && odom->pose.pose.position.x <=3.7f) && 
    (odom->pose.pose.position.y <= -2.9 && odom->pose.pose.position.y >= -3.1)){

        drop_off_show_marker = true;
        //show_marker = false;
        ROS_INFO("I am in callback,reack drop off zone,SHOW");
        
    }
  if (show_marker && (!drop_off_show_marker)) {
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("apporching to pick up zone,SHOW");
  }
  
  if ((!show_marker) && (!drop_off_show_marker)) {
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);        
    ROS_INFO("reached pick up zone,NOT SHOW");
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

void Marker_control::run() {
  	ros::spin();
 }


int main( int argc, char** argv )
{
  
  Marker_control marker_op(argc,argv) ;
  marker_op.run();
}  
  