#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../world/myworld" &
sleep 6
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../world/my_map.yaml " &

sleep 6
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 6
xterm  -e  " rosrun add_markers add_markers_node "  &
sleep 6
xterm  -e  " rosrun pick_objects pick_objects_node " 
