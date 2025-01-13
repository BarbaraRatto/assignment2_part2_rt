#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"
//#include "interfaces/srv/lin_choice.hpp"


// --------------------------------------------------------------------------------------------------------		

rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;

using std::placeholders::_1;

// 
class Subscriber : public rclcpp::Node
{
	public:
	
		Subscriber() : Node("subscriber")
        {
                subscription = this->create_subscription<nav_msgs::msg::Odometry>( "/odom", 10, std::bind(&Subscriber::odom_callback, this, _1));
                
                // Publishers
        		publisher = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        		feet_pub = this->create_publisher<geometry_msgs::msg::Point>("position_feet", 10);

	}

	private:
	
	// callback function called by topic /odom
	void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) const
	{
          	geometry_msgs::msg::Twist my_vel;

                RCLCPP_INFO(this->get_logger(), "\nPosition x: %f\nPosition y: %f\n\n", msg->pose.pose.position.x, msg->pose.pose.position.y);

            	// implementing the required behaviour
		my_vel.linear.x = 1;
		my_vel.angular.z = 0;
	
		// making the turtle moving as request
		if (msg->pose.pose.position.x > 9.0)
		{
			my_vel.linear.x = 1;			// linear velocity
			my_vel.angular.z = 2.0;		// angular vel > 0--> to turn left
		}
	
		if (msg->pose.pose.position.x < 2.0)
		{
			my_vel.linear.x = 1;			// linear velocity
			my_vel.angular.z = -2.0;		// angular vel < 0 --> to turn right
		}



           	publisher->publish(my_vel);
           	
           	geometry_msgs::msg::Point pos;
			
		pos.x = msg->pose.pose.position.x * 3.28;
		pos.y = msg->pose.pose.position.y * 3.28;
			
		publisher->publish(pos);
            
            
	}
	rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription;
};


// ------- MAIN --------------------------------------------------------------------------------------------	

int main(int argc, char * argv[])
{
	// Initialize the node
      	rclcpp::init(argc, argv);

      	rclcpp::spin(std::make_shared<Subscriber>());
      	rclcpp::shutdown();
      	return 0;
}
