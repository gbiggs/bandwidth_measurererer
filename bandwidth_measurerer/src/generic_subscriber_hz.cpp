// Copyright 2021 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class BandwidthMeasuringNode : public rclcpp::Node
{
public:
  BandwidthMeasuringNode(std::string topic_name, std::string topic_type)
  : Node("bandwidth_measurer")
  {
    rclcpp::QoS qos(1);
    subscriber_ = create_generic_subscription(
      topic_name,
      topic_type,
      qos,
      [this](std::shared_ptr<rclcpp::SerializedMessage> /*message*/) {
        receive_count_++;
      });

    timer_ = create_wall_timer(
      1s,
      [this]() {
        RCLCPP_INFO(get_logger(), "%ld Hz", receive_count_);
        receive_count_ = 0;
      });
  }

private:
  std::shared_ptr<rclcpp::GenericSubscription> subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t receive_count_ = 0;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BandwidthMeasuringNode>(argv[1], argv[2]));
  rclcpp::shutdown();
  return 0;
}
