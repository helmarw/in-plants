// -----------------------------------------
// Publish Argon data and Dashboard with Capacitive Moisture Sensors
// -----------------------------------------
// This app will publish an event every 30 seconds reporting the moisture sensor analog and percentage


// We start by declaring which pins everything is plugged into.

int boardLed = D7; // This is the LED that is already on your device.
// On the Core, it's the LED in the upper right hand corner.
// On the Photon, it's next to the D7 pin.

int moisture_pin = A1; // This is where your capacitive moisture sensor is plugged in.

// declaration on variables
double airvalue = 3520;  // analog value measured in air = 0%
double watervalue = 2230; // analog value measured in water = 100%
double moisture_analog;
double moisture_percentage;
double voltage;

// We start with the setup function.

void setup() {
  pinMode(boardLed,OUTPUT); // Our on-board LED is output as well
  pinMode(moisture_pin,INPUT);  // Our capacitive moisture sensor pin is input (reading the capacitive moisture sensor)
  //publish variable e.g. for IFTTT
  Particle.variable("Moisture", &moisture_percentage, DOUBLE); 
  Particle.variable("Batt_V", &voltage, DOUBLE); 
  Particle.variable("Moisture_Analog", &moisture_analog, DOUBLE); 
  // Just to make sure everything is workign we are going to toggle the LED on and then off really quickly 3x
  digitalWrite(boardLed,HIGH);
  delay(200);
  digitalWrite(boardLed,LOW);
  delay(200);

}


void loop() {
    /* In this loop function, we're going to check to read the moisture sensor
    After a specified time period we'll send a Particle.publish() to the cloud.
    */

   digitalWrite(boardLed,HIGH);
    // Now we'll take some readings...
    moisture_analog = round(analogRead(moisture_pin)); // read capacitive sensor
    moisture_percentage = round(map(moisture_analog, airvalue, watervalue, 0.0, 100.0));  //after calibraing the value in air and the value in water
    //float moisture_percentage = (100 - ( (moisture_analog/4095.00) * 100 ) );  //or just apropimate values wihtout calibrateion
    Particle.publish("BATT_Status", String(BATT),60,PUBLIC);
    voltage = analogRead(BATT) * 0.0011224;
     // Send a publish to your devices...
    Particle.publish("plantStatus_voltage", String(voltage,2),60,PUBLIC);
     // need to wait a bit if you publish to ThingSpeak
    delay(60000);
    digitalWrite(boardLed,LOW);
    Particle.publish("plantStatus_percentage", String(moisture_percentage,0),60,PUBLIC);
    delay(2000);
    // for calibration purpose
    Particle.publish("plantStatus_analog", String(moisture_analog,0),60,PUBLIC);
    //delay(50000); // for testing when sleep mode is off
     // put device to sleep for 
     // 6h
    delay(10000);
    WiFi.off();
    delay(250);
    System.sleep(D1,RISING,6h);
}
