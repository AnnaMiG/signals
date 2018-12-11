#include <utility>
#include "signals/signal.hpp"
#include <signal.h>
#include "ros/ros.h"
#include <std_msgs/Int32.h>
#include <stdlib.h>


Signal::Signal(ros::Publisher pub) :
    signal_pub(pub)
{
    std::string signals[] = {"SIGINT", "SIGQUIT", "SIGTERM"};
    int index;
    srand(time(0));
    index = rand() % 3;
    int signal_code [] = {2, 3, 15};
    std::cout << "signal chosen at random: " << signals[index] << std::endl;
    for (int i=0; i<3; i++)
    {
        if (i == index) signal(signal_code[index], Signal::sig_Handler);
        else signal(signal_code[i], Signal::sig_ignore_Handler);
    }
}

    void Signal::publish_pid(std_msgs::Int32 msg)
    {
        msg.data = getpid();
   //     ROS_INFO_STREAM(msg);
        signal_pub.publish(msg);
    }

    void Signal::sig_Handler(int sig_num)
    {
        std::cout << "RECEIVED : "  << sig_num << std::endl;
        ros::shutdown();
    }

    void Signal::sig_ignore_Handler(int sig_num)
    {
        std::cout << sig_num << " is not the correct signal" <<std::endl;
    }