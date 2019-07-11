#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 6
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../world/my_map.yaml" &
#xterm  -e "roslaunch gmapping slam_gmapping_pr2.launch " & 
sleep 6
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 6
xterm  -e  " rosrun add_markers add_markers_node " 
