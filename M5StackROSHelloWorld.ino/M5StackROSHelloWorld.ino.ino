#include <M5Stack.h>
#undef ESP32
#include <ros.h>
#define ESP32
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  M5.begin();
  M5.Speaker.begin();
  M5.Speaker.mute();  

  nh.initNode();
  nh.getHardware()->setBaud(57600);
  nh.advertise(chatter);

  M5.Lcd.printf("ROS Hello World Publisher Started\n");

}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
