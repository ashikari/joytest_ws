#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <Servo.h>

Servo myservo;

int bluePin = 13;
int redPin = 11;
int greenPin = 12;

void colorCallback( const std_msgs::Float32MultiArray msg ){
  
  analogWrite(bluePin, 255*( msg.data[0]+1 )/2  );

  analogWrite(greenPin, 255*( msg.data[1]+1 )/2  );

  myservo.write( map(msg.data[0]*100,-100,100,0,180) );
     
  if(msg.data[2] == 1){
    digitalWrite(redPin, HIGH );
   }
   else if (msg.data[2] == 0){
    digitalWrite(redPin, LOW );
   }
   
}


//create the node handle and subscriber
ros::NodeHandle color;
ros:: Subscriber<std_msgs::Float32MultiArray> color_sub("color_cmd", &colorCallback);


void setup() {
  //set the pin mode for the color LEDS
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin,OUTPUT);

  myservo.attach(9);


  //initialize the ros node and subscriber
  color.initNode();
  color.subscribe(color_sub);
}

void loop() {
  // put your main code here, to run repeatedly:
  color.spinOnce();
  delay(1);
}
