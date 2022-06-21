#include "int_subscriber/IntSubscriber.h"

namespace int_subscriber
{
    // PUBLIC METHODS

    IntSubscriber::IntSubscriber()
    : nh_("~"), received_n_(0)
    {
        ROS_INFO("Hello World");
        sub_ = nh_.subscribe("/count", 1, &IntSubscriber::onMsgCallback, this);
    }


    int
    IntSubscriber::getLastData()
    {
        return received_n_;
    }

    // PRIVATE METHODS

    void
    IntSubscriber::onMsgCallback(const std_msgs::Int32::ConstPtr & msg)
    {
        received_n_ = msg->data;
    }
}