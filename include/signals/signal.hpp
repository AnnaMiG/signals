#ifndef SIGNAL_HPP
#define SIGNAL_HPP
#include "ros/ros.h"
#include <std_msgs/Int32.h>


class Signal
{
private:
    ros::Publisher signal_pub;
public:
    Signal(ros::Publisher signal_pub);
    void publish_pid(std_msgs::Int32 msg);
    static void sig_Handler(int sig_num);
    static void sig_ignore_Handler(int sig_num);
};

#endif
