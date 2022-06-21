#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include "int_subscriber/IntSubscriber.h"

bool
is_pair(int n)
{
    return n % 2 == 0;
}

void
step(int n)
{
    if (is_pair(n))
    {
        ROS_INFO("It's even!");
    }
}

int
main(int argc, char ** argv)
{
    ros::init(argc, argv, "subscriber1_node");

    int_subscriber::IntSubscriber intSub;
    
    ros::Rate loop_rate(2);
    while (ros::ok())
    {
        ros::spinOnce();

        step(intSub.getLastData());

        loop_rate.sleep();
    }

    exit(EXIT_SUCCESS);
}