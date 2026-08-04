#include <ackermann_msgs/msg/ackermann_drive_stamped.hpp>
#include <rclcpp/rclcpp.hpp>

using std::placeholders::_1;

class Relay : public rclcpp::Node
{
  public:
    Relay() : Node("relay")
    {
        sub = this->create_subscription<ackermann_msgs::msg::AckermannDriveStamped>(
            "drive", 10, std::bind(&Relay::callback, this, _1));

        pub = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>("drive_relay", 10);
    }

  private:
    void callback(const ackermann_msgs::msg::AckermannDriveStamped::SharedPtr msg)
    {
        ackermann_msgs::msg::AckermannDriveStamped out;

        out.drive.speed = msg->drive.speed * 3.0;
        out.drive.steering_angle = msg->drive.steering_angle * 3.0;

        std::cout << "Relaying: speed = " << out.drive.speed << ", steering_angle = " << out.drive.steering_angle
                  << std::endl;
        pub->publish(out);
    }

    rclcpp::Subscription<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr sub;
    rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr pub;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Relay>());
    rclcpp::shutdown();
    return 0;
}