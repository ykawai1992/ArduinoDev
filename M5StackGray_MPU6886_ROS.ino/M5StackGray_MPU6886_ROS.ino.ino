#define M5STACK_MPU6886 

#include <M5Stack.h>

#undef ESP32 //追記
#include <ros.h>
#define ESP32 //追記
#include <sensor_msgs/Imu.h>

//MPU6886 IMU;
//M5Stack M5;

ros::NodeHandle nh;
sensor_msgs::Imu imu_msg;
ros::Publisher pub("imu", &imu_msg);

unsigned long count = 0;

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float temp = 0.0F;

void setup() {
  //M5.begin();
  M5.begin( true, false, true, true );
  Wire.begin();

  M5.IMU.Init();//MPU6886関連追記

  nh.getHardware()->setBaud(57600);//追記
  nh.initNode();
  nh.advertise(pub);

  while (!nh.connected()) {
    nh.spinOnce();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(GREEN , BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0); M5.Lcd.print("Waitting ROS...");
    delay(100);
  }
}

void loop() {
  M5.update();

  count++;

  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getTempData(&temp);
  
    if (count % 20) {
        M5.Lcd.setCursor(0, 20);  
        M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ);
        M5.Lcd.setCursor(220, 42);
        M5.Lcd.print(" o/s");
        M5.Lcd.setCursor(0, 65);
        M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
        M5.Lcd.setCursor(220, 87);
        M5.Lcd.print(" G");
        M5.Lcd.setCursor(0, 110);
        M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw);
        M5.Lcd.setCursor(220, 132);
        M5.Lcd.print(" degree");
        M5.Lcd.setCursor(0, 155);
        M5.Lcd.printf("Temperature : %.2f C", temp);
    }

    setIMUData();
    pub.publish(&imu_msg);
    nh.spinOnce();
    delay(200);

}

void setIMUData(void) {
//  imu_msg.header.frame_id = "imu"; いらなかった。
  imu_msg.header.stamp = nh.now();
  imu_msg.linear_acceleration.x = 9.81 * accX;
  imu_msg.linear_acceleration.y = 9.81 * accY;
  imu_msg.linear_acceleration.z = 9.81 * accZ;

  imu_msg.angular_velocity.x = 3.141 / 180.0 * gyroX;
  imu_msg.angular_velocity.y = 3.141 / 180.0 * gyroY;
  imu_msg.angular_velocity.z = 3.141 / 180.0 * gyroZ;

}
