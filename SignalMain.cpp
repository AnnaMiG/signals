#include "ros/ros.h"
#include <std_msgs/Int32.h>
#include "signals/signal.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "signal_publisher");
    ros::NodeHandle n;
    ros::Publisher signal_pub = n.advertise<std_msgs::Int32>("pid_no", 1);
    Signal signalObj(signal_pub);
    std_msgs::Int32 msg;

    while(ros::ok())
    {
        signalObj.publish_pid(msg);
        ros::Duration(1).sleep();
    }

}
