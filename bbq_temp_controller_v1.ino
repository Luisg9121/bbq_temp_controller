//import libraries for temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

//Using pin 2 for temp sensor
#define ONE_WIRE_BUS 2

//using light for now -This simulates a fan. Using pin 8
int LIGHT = 8;  

//holds celsius temperature to convert to fahrenheit
float CEL = 0;

//holds fahrenheit temperature
float FAR = 0;

//initialize OneWire object
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup()
{
  sensors.begin();
  Serial.begin(9600);
  pinMode(LIGHT,OUTPUT);
  Serial.println("BBQ temperature regulator");
}

void loop()
{ 
  //holds desired temperature of bbq pit
  //set to 70 for testing purposes
  //will be able to change through UI
  float desired_temp = 70;
  
  //check every 5 seconds
  delay(5000);
  sensors.requestTemperatures();
  CEL = sensors.getTempCByIndex(0);
  FAR = sensors.toFahrenheit(CEL);

  //print temperature to console
  Serial.print("Temperature: ");
  Serial.print(FAR);
  Serial.print("\n");

  //fire is too low - feed air to fire   
  if(FAR < desired_temp){
      //turn fan on
      digitalWrite(LIGHT,HIGH);  
  }
  //fire is hot enough or too hot- turn fan off (if it was on), or remain doing nothing
  else{
    digitalWrite(LIGHT, LOW);
  }
}
