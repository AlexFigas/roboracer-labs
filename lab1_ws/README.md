# Lab 1: Intro to ROS 2 - Command Reference

This document contains all the key commands used to complete Lab 1.

## Setup and Workspace Creation

```bash
# Create the workspace directory structure
mkdir -p ~/lab1_ws/src
cd lab1_ws

# Build the workspace for the first time
colcon build

# Source the ROS 2 environment
source /opt/ros/foxy/setup.bash

# Source the workspace setup (after building)
source install/setup.bash
```

## Creating the Package

```bash
# Navigate to the src directory
cd src

# Create the lab1_pkg package with Python and C++ support, including ackermann_msgs dependency
ros2 pkg create --build-type ament_cmake lab1_pkg --dependencies rclcpp rclpy ackermann_msgs

# Install dependencies (if needed)
rosdep install -i --from-path src --rosdistro foxy -y
```

## Building the Package

```bash
# From the workspace root (lab1_ws)
cd ..
colcon build

# Or build a specific package
colcon build --packages-select lab1_pkg
```

## Creating and Running Nodes

### Node Creation
- **talker.cpp** or **talker.py**: Publishes `AckermannDriveStamped` messages with v and d ROS parameters
- **relay.cpp** or **relay.py**: Subscribes to drive topic, multiplies speed/steering by 3, publishes to drive_relay

### Running the Nodes

```bash
# Terminal 1: Source the workspace and launch the nodes
source install/setup.bash
ros2 launch lab1_pkg lab1_launch.py

# Or run nodes individually in separate terminals
ros2 run lab1_pkg talker
ros2 run lab1_pkg relay
```

### Setting ROS Parameters

```bash
# Option 1: Set parameters when launching the node
ros2 run lab1_pkg talker --ros-args -p v:=1.0 -p d:=0.5

# Option 2: Set parameters at runtime (while node is running)
ros2 param set /talker v 1.0
ros2 param set /talker d 0.2

# Or in a launch file using parameter configuration
```

## Testing and Debugging Commands

```bash
# List all active topics
ros2 topic list

# Get information about a specific topic
ros2 topic info drive
ros2 topic info /drive

# View messages on a topic in real-time
ros2 topic echo /drive
ros2 topic echo /drive_relay

# List all active nodes
ros2 node list

# Get information about a specific node
ros2 node info /talker
ros2 node info /relay

# Check and set parameters at runtime
ros2 param list
ros2 param get /talker v
ros2 param set /talker v 1.0
ros2 param set /talker d 0.2

# Show the dependency graph
rqt_graph
```

## Launch File

```bash
# Launch both nodes using the launch file
ros2 launch lab1_pkg lab1_launch.py

# Launch with parameters set in the launch file
ros2 launch lab1_pkg lab1_launch.py v:=1.0 d:=0.5
```
