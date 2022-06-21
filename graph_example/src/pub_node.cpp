#include <ros/ros.h>
#include <std_msgs/Int32.h>

class IntPublisher
{
public:

    IntPublisher()
    : nh_("~"), n(0)
    {
        pub_ = nh_.advertise<std_msgs::Int32>("/count", 1, true);
    }

    void
    step()
    {
        std_msgs::Int32 msg;
        msg.data = n;
        n++;

        pub_.publish(msg);
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_;
    int n;
};

int
main(int argc, char ** argv)
{
    ros::init(argc, argv, "publisher_node");

    IntPublisher pub_node;

    ros::Rate loop_rate(2); // 2 Hz
    while (ros::ok())
    {
        ros::spinOnce();

        pub_node.step();
        loop_rate.sleep();
    }

    exit(EXIT_SUCCESS);
}