// zoomkat 12-25-13 serial servo test
// type servo write 0 to 180 in serial monitor
// or for write, use a value like 1500
// Send an a to attach servo or d to detach servo
// for IDE 1.0.5 and later
// Powering a servo from the arduino usually DOES NOT WORK.

#include <Servo.h> 
String readString; //String captured from serial port

// create servo objects to control a servo motors
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;
Servo servoThumb;

int n; //value to write to servo

void setup() {
  Serial.begin(9600);

  //sets initial servo writes if desired
  servoIndex.write(0); 
  servoMiddle.write(0);
  servoRing.write(0);
  servoPinky.write(0);
  servoThumb.write(0);

  //assigns pin for the servo control, and range if desired
  servoIndex.attach(8, 500, 2500);
  servoMiddle.attach(9, 500, 2500);
  servoRing.attach(10, 500, 2500);
  servoPinky.attach(11, 500, 2500);
  servoThumb.attach(12, 500, 2500);
  
  Serial.println("servo all-in-one test code 12-25-13"); // so I can keep track of what is loaded
  Serial.println();
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured string 

      // attach or detach servo if desired
    if (readString == "d") { 

      //delay loop until pins are low
      while (digitalRead(8) && digitalRead(9) && digitalRead(10)&& digitalRead(11) && digitalRead(12)) {} // 
      
      //detach servos
      servoIndex.detach(); 
      servoMiddle.detach();
      servoRing.detach();
      servoPinky.detach();
      servoThumb.detach();

      Serial.println("servo detached");
      goto bailout; //jump over writing to servo
    }
    if (readString == "a") {
      servoIndex.attach(8); //reattach servo to pin 7
      servoMiddle.attach(9);
      servoRing.attach(10);
      servoPinky.attach(11);
      servoThumb.attach(12); 
      Serial.println("servo attached");
      goto bailout;
    }    

    n = readString.toInt();  //convert readString into a number

    // auto select appropriate value
    if(n == 1)
    {
      Serial.print("writing Microseconds: ");
      Serial.println(1);
      servoIndex.write(0);
      servoMiddle.write(0);
      servoRing.write(0);
      servoPinky.write(0);
      servoThumb.write(20);
    }
    else if (n == 2)
    {   
      Serial.print("writing Angle: ");
      Serial.println(2);
      servoIndex.write(90);
      servoMiddle.write(90);
      servoRing.write(90);
      servoPinky.write(90);
      servoThumb.write(90);
    }
    else if (n == 3)
    {   
      Serial.print("writing Angle: ");
      Serial.println(3);
      servoIndex.write(180);
      servoMiddle.write(180);
      servoRing.write(180);
      servoPinky.write(180);
      servoThumb.write(180);
    }

bailout: //reenter code loop
    Serial.print("Last servo command write: ");    
    Serial.println(servoIndex.read());
    Serial.println(servoMiddle.read());
    Serial.println(servoRing.read());
    Serial.println(servoPinky.read());
    Serial.println(servoThumb.read());
    Serial.println();
    readString=""; //empty for next input
  }
}
