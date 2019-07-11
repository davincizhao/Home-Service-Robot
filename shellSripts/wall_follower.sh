#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../world/myworld" &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo gmapping_demo.launch " &
#xterm  -e "roslaunch gmapping slam_gmapping_pr2.launch " & 
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm  -e  " rosrun wall_follower wall_follower_node " 
