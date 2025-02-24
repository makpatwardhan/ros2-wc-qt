#include "mainwindow.h"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <QApplication>

class Ros2QtNode : public rclcpp::Node {
public:
    Ros2QtNode() : Node("ros2_qt_node") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            [this]() { this->timer_callback(); });
    }

private:
    void timer_callback() {
        auto message = std_msgs::msg::String();
        message.data = "Hello, ROS2 with Qt6!";
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Ros2QtNode>();
    rclcpp::spin(node);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
