#include <Servo.h>
#include <Wire.h>
#include <ros.h>
#include <std_msgs/String.h>

Servo valve; 
Servo pump;

unsigned long actionStartTime = 0;
unsigned long actionDuration = 5000;
bool actionInProgress = false;
char currentAction[8];

ros::NodeHandle nh;

void startAction(const char* action) {
  strncpy(currentAction, action, sizeof(currentAction));
  actionStartTime = millis();
  actionInProgress = true;

  if (strcmp(action, "suction") == 0) {
    valve.write(0);
    pump.write(180);
    Serial.println("suction");
  } else if (strcmp(action, "hold") == 0) {
    valve.write(0);
    pump.write(0);
    Serial.println("hold");
  } else if (strcmp(action, "exhaust") == 0) {
    valve.write(180);
    pump.write(0);
    Serial.println("exhaust");
  }
}

void stopAction() {
  if (strcmp(currentAction, "suction") == 0 || strcmp(currentAction, "hold") == 0) {
    pump.write(0);
  } else if (strcmp(currentAction, "exhaust") == 0) {
    valve.write(0);
  }
  Serial.print(currentAction);
  Serial.println(" completed");
  actionInProgress = false;
}

void vacuumgripper(const std_msgs::String& msg) {
  const char* data = msg.data;
  if (strcmp(data, "suction") == 0 || strcmp(data, "hold") == 0 || strcmp(data, "exhaust") == 0) {
    startAction(data);
  } else {
    Serial.println("Invalid command");
  }
}

ros::Subscriber<std_msgs::String> sub("gripper_control", &vacuumgripper);

void setup() {
  valve.attach(11);
  pump.attach(8);

  Serial.begin(9600);
  delay(100);
  Serial.println("Setup complete. Waiting for commands...");

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  if (actionInProgress && (millis() - actionStartTime >= actionDuration)) {
    stopAction();
  }
}
