#include "ros/ros.h"
#include "ros/console.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"
#include "ackermann_msgs/AckermannDrive.h"
#include "ackermann_msgs/AckermannDriveStamped.h"
#include <sstream>
#include <iostream>   // std::cout
#include <string> 
#include <math.h>

class TwistToAackermann {
    public:
        TwistToAackermann()
        {
        //Topic you want to publish 
        //pubAD_ = n_.advertise<ackermann_msgs::AckermannDrive>("/ackermann_cmd", 1);
        //pubADS_ = n_.advertise<ackermann_msgs::AckermannDriveStamped>("/rbcar_robot_control/command", 1);

        pubLeftWheelHinge_ = n_.advertise<std_msgs::Float64>("/ack/joint_lwh_position_controller/command", 1);
        pubRightWheelHinge_ = n_.advertise<std_msgs::Float64>("/ack/joint_rwh_position_controller/command", 1);
        pubLeftWheelRotate_ = n_.advertise<std_msgs::Float64>("/ack/joint_lw_velocity_controller/command", 1);
        pubRightWheelRotate_ = n_.advertise<std_msgs::Float64>("/ack/joint_rw_velocity_controller/command", 1); 

        //Topic you want to subscribe
        sub_ = n_.subscribe("/twist_to_ackermann", 1, &TwistToAackermann::callback, this);
        }

        void callback(const geometry_msgs::Twist& msg) {

            // Vehicle wheel base geometry. wheelBase is the distance between front
            // and back axles, track is the distance between left and right wheels.    
            double wheelBase = 1.753;
            double track = 1.245; 
            std_msgs::Float64 lwh; 
            std_msgs::Float64 rwh;
            std_msgs::Float64 lwr;
            std_msgs::Float64 rwr;
            double r = 0;  

            if (msg.angular.z==0 || msg.linear.x==0) {
                lwh.data = 0;
                rwh.data = 0;

            }
            else {
                r = msg.linear.x/msg.angular.z; 
                lwh.data = atan(wheelBase/(r-(track/2)));
                rwh.data = atan(wheelBase/(r+(track/2)));
                lwr.data = (r-(track/2))*msg.angular.z;
                rwr.data = (r+(track/2))*msg.angular.z; 


                //ad.steering_angle = baseLength/(msg.linear.x/msg.angular.z);
				//ad.steering_angle = atan(wheelBase/(msg.linear.x/msg.angular.z));
            }

            //double R = static_cast<double>(msg.linear.x/msg.angular.z); 
            ROS_DEBUG("Test"); 

            //pubADS_.publish(ads); 
            pubLeftWheelHinge_.publish(lwh);
            pubRightWheelHinge_.publish(rwh); 
            pubLeftWheelRotate_.publish(lwr); 
            pubRightWheelRotate_.publish(rwr); 

        }
    private:
        ros::NodeHandle n_;
        ros::Publisher pubLeftWheelHinge_;
        ros::Publisher pubRightWheelHinge_;
        ros::Publisher pubLeftWheelRotate_;
        ros::Publisher pubRightWheelRotate_; 
        ros::Subscriber sub_;
};
// void ackermanCallback(const ackermann_msgs::AckermannDrivePtr& str) {
//     ros::init(argc, argv, "twist_to_ackermann");
//     ros::NodeHandle n; 

//     ros::Publisher ackermann_pub = 
//         n.advertise<ackermann_msgs::AckermannDrive>("ackermann_cmd",1000);
//     ros::Rate loop_rate(10); 
// }

int main(int argc, char **argv) {
    ros::init(argc, argv, "twist_to_ackermann");
    
    TwistToAackermann SAPObject; 
    ros::spin(); 

    //ros::NodeHandle n; 

    // ros::Publisher ackermann_pub = 
    //     n.advertise<ackermann_msgs::AckermannDrive>("ackermann_cmd",1000);
    // ros::Rate loop_rate(10); 

    //int count=0;

    // while (ros::ok()) {
    //     ackermann_msgs::AckermannDrive msg;

    //     msg.steering_angle = 0.0; 
    //     msg.steering_angle_velocity = 1.0;
    //     msg.speed = 1.0; 
    //     msg.acceleration = 1.0; 
    //     msg.jerk = 0.0;  

    //     //std::cout << msg.data.c_str(); 
    //     //ROS_INFO("%s", msg.data.c_str()); 

    //     ackermann_pub.publish(msg); 
    //     ros::spinOnce(); 
    //     loop_rate.sleep();
    //     ++count; 
    // }
    return 0; 
}
