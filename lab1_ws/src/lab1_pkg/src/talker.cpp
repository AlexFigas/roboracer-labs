#include <ackermann_msgs/msg/ackermann_drive_stamped.hpp>
#include <rclcpp/rclcpp.hpp>

using std::placeholders::_1;

class Talker : public rclcpp::Node
{
  public:
    Talker() : Node("talker")
    {
        this->declare_parameter("v", 0.0);
        this->declare_parameter("d", 0.0);

        pub = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>("drive", 10);

        timer = this->create_wall_timer(std::chrono::milliseconds(1), std::bind(&Talker::publish_msg, this));
    }

  private:
    void publish_msg()
    {
        double v = this->get_parameter("v").as_double();
        double d = this->get_parameter("d").as_double();

        ackermann_msgs::msg::AckermannDriveStamped msg;
        msg.drive.speed = v;
        msg.drive.steering_angle = d;

        std::cout << "Publishing: speed = " << msg.drive.speed << ", steering_angle = " << msg.drive.steering_angle
                  << std::endl;
        pub->publish(msg);
    }

    rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr pub;
    rclcpp::TimerBase::SharedPtr timer;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Talker>());
    rclcpp::shutdown();
    return 0;
}