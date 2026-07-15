# Project Goal

Implement vision-based object tracking and following for a PX4 multicopter
in the aerial-autonomy-stack Gazebo SITL environment.

Target architecture:

Gazebo camera
-> existing yolo_py detector
-> target_tracking node
-> tracked detections
-> PX4 vision-follow offboard controller
-> PX4 SITL

# Scope

- SITL simulation only.
- PX4 only. Do not modify ArduPilot behavior.
- ROS2 Humble inside the existing aircraft container.
- Preserve the existing YOLO ONNX and GStreamer pipeline.
- Preserve all existing controllers and missions.
- Make small, reviewable changes.
- Do not perform broad refactoring.

# Safety Requirements

- Never send commands to real serial devices or real flight controllers.
- Do not automatically arm or take off a vehicle during unit tests.
- A stale or missing target must produce zero translational velocity.
- Apply explicit limits to forward, vertical, lateral, and yaw commands.
- Do not continue forward flight when the target is outside the configured
  horizontal field-of-view gate.
- Use simulation time for ROS timestamps.
- Clearly document ENU, FLU, FRD, and NED coordinate conversions.
- PX4 local position and velocity commands use NED coordinates.

# Dependency Rules

- Do not install Python packages directly on the host.
- Add required dependencies to the existing Docker build.
- Do not install pip opencv-python into the system Python environment.
  The existing GStreamer-enabled OpenCV must remain usable.
- Do not add an unpinned remote dependency.
- Do not commit large YOLO weight files.
- Do not replace the existing YOLO inference node unless explicitly requested.

# ROS Interfaces

Existing detector input:
- /detections
- vision_msgs/msg/Detection2DArray

New tracker output:
- /tracked_detections
- vision_msgs/msg/Detection2DArray
- Detection2D.id shall contain a numeric tracking ID as a string.
- Object class remains in results[].hypothesis.class_id.
- Preserve azimuth and elevation values in results[].pose.pose.position.x/y.

New PX4 controller name:
- vision-follow

# Development Workflow

For every task:

1. Inspect the relevant files first.
2. State the exact files that will be changed.
3. Make the smallest possible change.
4. Build only affected ROS packages first.
5. Run unit tests.
6. Show the diff.
7. Report known limitations.
8. Stop after completing the requested milestone.

Do not silently move to the next milestone.

# Build Commands

Aircraft workspace:

```bash
cd /aas/aircraft_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

Focused build:

```bash
colcon build --symlink-install \
  --packages-select target_tracking offboard_control yolo_py
```

Tests:

```bash
colcon test --packages-select target_tracking offboard_control
colcon test-result --verbose
```

# Definition of Done

A milestone is complete only when:

- The affected packages build.
- Automated tests pass.
- Existing controllers still compile.
- Topic names and message types are documented.
- Failure behavior is tested.
- The diff contains no unrelated formatting or refactoring.
