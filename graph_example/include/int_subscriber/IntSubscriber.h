#include <ros/ros.h>
#include <std_msgs/Int32.h>

#ifndef INT_SUBSCRIBER__INT_SUBSCRIBER_H
#define INT_SUBSCRIBER__INT_SUBSCRIBER_H

namespace int_subscriber
{
class IntSubscriber
{
public:
    IntSubscriber();
    int getLastData();
private:
    void onMsgCallback(const std_msgs::Int32::ConstPtr & msg);

    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    int received_n_;
};
}   // end int_subscriber

#endif