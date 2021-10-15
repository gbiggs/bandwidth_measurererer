# bandwidth_measurererer

A prototype tool to measure the bandwidth of a ROS 2 topic with minimal CPU overhead

Run like so:

```
ros2 run bandwidth_measurererer bandwidth_measurererer <topic> <topic type>
```

For example:

```
ros2 run bandwidth_measurererer bandwidth_measurererer /blag example_interfaces/msg/String
```
