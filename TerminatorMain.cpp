#include "ros/ros.h"
#include <std_msgs/Int32.h>
#include <signal.h>

int stop_function(int pid_no)
{

    std::string signals[] = {"SIGINT", "SIGQUIT", "SIGTERM"};
    int signal_code [] = {2, 3, 15};
    int i=0;
    bool search = true;
    //check to see if the PID received is valid
    if (kill(pid_no, 0) != 0)
    {
        std::cout << "This is not a correct PID" << std::endl;
        std::exit(0);
    }
    while(search and i < 3)
    {
        std::cout << "Sending: " << signals[i] << std::endl;
        bool signal_sent = kill(pid_no, signal_code[i]) == 0;

        while(signal_sent == false and ros::ok())
        {
            signal_sent = kill(pid_no, signal_code[i]) == 0;
            ros::Duration(0.1).sleep();
        }
        ros::Duration(1).sleep(); //this is necessary
        if (kill(pid_no, 0) == 0) i++;
        else  search = false;
    }

    if (search)
    {
        std::cout << "Program not killed" << std::endl;
    }
    else
    {
        std::cout << "The signal that killed the program was: " << signals[i] << std::endl;
        ros::shutdown();
    }
}

void terminationCallback(const std_msgs::Int32::ConstPtr& msg)
{
    int pid_no = msg->data;
    stop_function(pid_no);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "program_termination");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("pid_no", 1, terminationCallback);
    ros::spin();
    return 0;
}
