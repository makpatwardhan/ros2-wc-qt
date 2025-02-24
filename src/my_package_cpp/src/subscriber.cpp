#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <iostream>

class SubscriberNode : public rclcpp::Node {
public:
    SubscriberNode() : Node("qt6_subscriber_node") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "topic", 10, std::bind(&SubscriberNode::message_callback, this, std::placeholders::_1));
    }

private:
    void message_callback(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    std::cout << "Subscriber started" <<std::endl;	
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscriberNode>());
    rclcpp::shutdown();
    return 0;
}

