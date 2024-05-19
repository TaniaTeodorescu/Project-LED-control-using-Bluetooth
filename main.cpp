#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define btcServerName "ESP32_TANING"

// Define the LED pins
const int LED1_PIN = 15; // led1
const int LED2_PIN = 0;  // led2
const int LED3_PIN = 5;  // led3
const int LED4_PIN = 2;  // led4
const int LED5_PIN = 4;  // led5
const int LED6_PIN = 16; // led6
const int LED7_PIN = 17; // led7

// Define the LED channels for PWM control
const int LED1_CHANNEL = 0;  // led1
const int LED2_CHANNEL = 1;  // led2
const int LED3_CHANNEL = 2;  // led3
const int LED4_CHANNEL = -1; // led4
const int LED5_CHANNEL = -1; // led5
const int LED6_CHANNEL = -1; // led6
const int LED7_CHANNEL = -1; // led7

// Define the BluetoothSerial
BluetoothSerial SerialBT;

// Received data
String inputData = "";

// The receivedData function is called when data is available on Bluetooth (see loop function)
String teamId = "";

void setLedPWM(int channel_id, float duty_cycle)
{
  ledcWrite(channel_id, duty_cycle * 2.55);
}

void setLedNoPWM(int id, int value)
{
  digitalWrite(id, value);
}

void blinkLedNoPWM(int id, float frequency, int number)
{
  float time = 1.0 / frequency * 1000.0;
  for (int blink_number = 0; blink_number < number; ++blink_number)
  {
    setLedNoPWM(id, HIGH);
    delay((int)(time / 2));
    setLedNoPWM(id, LOW);
    delay((int)(time / 2));
  }
}

void blinkLedPWM(int id, float frequency, int number)
{
  float time = 1.0 / frequency * 1000.0;
  for (int blink_number = 0; blink_number < number; ++blink_number)
  {
    setLedPWM(id, 100);
    delay((int)(time / 2));
    setLedPWM(id, LOW);
    delay((int)(time / 2));
  }
}

void sweepLed(int id, int duration, int number)
{
  int time = duration * 5;
  for (int k = 0; k < number; ++k)
  {
    for (int i = 1; i <= 100; ++i)
    {
      setLedPWM(id, i);
      delay(time);
    }
    for (int i = 99; i >= 0; --i)
    {
      setLedPWM(id, i);
      delay(time);
    }
  }
}

void getLEDS(StaticJsonDocument<1500> readDoc)
{
  StaticJsonDocument<1500> printDoc;

  String team = readDoc["teamId"];
  teamId=team;
  String output = "";
  
  // led 1
  printDoc["color"] = "white";
  printDoc["pin"] = LED1_PIN;
  printDoc["pwm"] = true;
  printDoc["channel"] = LED1_CHANNEL;
  printDoc["id"] = 1;
  printDoc["teamId"] = teamId;

  serializeJson(printDoc, output);
  Serial.println(output);
  Serial.println();
  SerialBT.println(output);

  // led2
  printDoc["color"] = "blue";
  printDoc["pin"] = LED2_PIN;
  printDoc["pwm"] = true;
  printDoc["channel"] = LED2_CHANNEL;
  printDoc["id"] = 2;
  printDoc["teamId"] = teamId;

  output = "";
  serializeJson(printDoc, output);
  Serial.println(output);
  Serial.println();
  SerialBT.println(output);

  // led3
  printDoc["color"] = "yellow";
  printDoc["pin"] = LED3_PIN;
  printDoc["pwm"] = true;
  printDoc["channel"] = LED3_CHANNEL;
  printDoc["id"] = 3;
  printDoc["teamId"] = teamId;

  output = "";
  serializeJson(printDoc, output);
  Serial.println(output);
  Serial.println();
  SerialBT.println(output);

  // led4
  printDoc["color"] = "red";
  printDoc["pin"] = LED4_PIN;
  printDoc["pwm"] = false;
  printDoc["channel"] = LED4_CHANNEL;
  printDoc["id"] = 4;
  printDoc["teamId"] = teamId;

  output = "";
  serializeJson(printDoc, output);
  Serial.println(output);
  Serial.println();
  SerialBT.println(output);

  // led5
  printDoc["color"] = "yellow";
  printDoc["pin"] = LED5_PIN;
  printDoc["pwm"] = false;
  printDoc["channel"] = LED5_CHANNEL;
  printDoc["id"] = 5;
  printDoc["teamId"] = teamId;

  output = "";
  serializeJson(printDoc, output);
  Serial.println(output);
  Serial.println();
  SerialBT.println(output);

  // led6
  printDoc["color"] = "blue";
  printDoc["pin"] = LED6_PIN;
  printDoc["pwm"] = false;
  printDoc["channel"] = LED6_CHANNEL;
  printDoc["id"] = 6;
  printDoc["teamId"] = teamId;

  output = "";
  serializeJson(printDoc, output);
  Serial.println(output);
  Serial.println();
  SerialBT.println(output);

  // led 7
  printDoc["color"] = "white";
  printDoc["pin"] = LED7_PIN;
  printDoc["pwm"] = false;
  printDoc["channel"] = LED7_CHANNEL;
  printDoc["id"] = 7;
  printDoc["teamId"] = teamId;

  output = "";
  serializeJson(printDoc, output);
  Serial.println(output);
  Serial.println();
  SerialBT.println(output);
}

void getValue(StaticJsonDocument<1500> readDoc)
{
  StaticJsonDocument<1500> printDoc;
  int id = readDoc["id"];
  if (id == 1)
  {
    int value = 0;
    value = ledcRead(LED1_CHANNEL);
    printDoc["id"] = 1;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 2)
  {
    int value = 0;
    value = ledcRead(LED2_CHANNEL);
    printDoc["id"] = 2;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 3)
  {
    int value = 0;
    value = ledcRead(LED3_CHANNEL);
    printDoc["id"] = 3;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 4)
  {
    int value = 0;
    value = digitalRead(LED4_PIN);
    printDoc["id"] = 4;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 5)
  {
    int value = 0;
    value = digitalRead(LED5_PIN);
    printDoc["id"] = 5;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 6)
  {
    int value = 0;
    value = digitalRead(LED6_PIN);
    printDoc["id"] = 6;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 7)
  {
    int value = 0;
    value = digitalRead(LED7_PIN);
    printDoc["id"] = 7;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
}

void setValue(StaticJsonDocument<1500> readDoc)
{
  StaticJsonDocument<1500> printDoc;
  int id = readDoc["id"];
  if (id == 1)
  {
    float value = readDoc["value"];
    setLedPWM(LED1_CHANNEL, value);
    printDoc["id"] = 1;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 2)
  {
    float value = readDoc["value"];
    setLedPWM(LED2_CHANNEL, value);
    printDoc["id"] = 2;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 3)
  {
    float value = readDoc["value"];
    setLedPWM(LED3_CHANNEL, value);
    printDoc["id"] = 3;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 4)
  {
    int value = readDoc["value"];
    setLedNoPWM(LED4_PIN, value);
    printDoc["id"] = 4;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 5)
  {
    int value = readDoc["value"];
    setLedNoPWM(LED5_PIN, value);
    printDoc["id"] = 5;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 6)
  {
    int value = readDoc["value"];
    setLedNoPWM(LED6_PIN, value);
    printDoc["id"] = 6;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 7)
  {
    int value = readDoc["value"];
    setLedNoPWM(LED7_PIN, value);
    printDoc["id"] = 7;
    printDoc["value"] = value;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
}

void blink(StaticJsonDocument<1500> readDoc)
{
  StaticJsonDocument<1500> printDoc;
  int id = readDoc["id"];
  if (id == 1)
  {
    float frequency = readDoc["frequency"];
    int number = readDoc["number"];
    blinkLedPWM(LED1_CHANNEL, frequency, number);
    printDoc["id"] = id;
    printDoc["value"] = 0;
    printDoc["blink_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 2)
  {
    float frequency = readDoc["frequency"];
    int number = readDoc["number"];
    blinkLedPWM(LED2_CHANNEL, frequency, number);
    printDoc["id"] = id;
    printDoc["value"] = 0;
    printDoc["blink_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 3)
  {
    float frequency = readDoc["frequency"];
    int number = readDoc["number"];
    blinkLedPWM(LED3_CHANNEL, frequency, number);
    printDoc["id"] = id;
    printDoc["value"] = 0;
    printDoc["blink_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 4)
  {
    float frequency = readDoc["frequency"];
    int number = readDoc["number"];
    blinkLedNoPWM(LED4_PIN, frequency, number);
    printDoc["id"] = id;
    printDoc["value"] = 0;
    printDoc["blink_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 5)
  {
    float frequency = readDoc["frequency"];
    int number = readDoc["number"];
    blinkLedNoPWM(LED5_PIN, frequency, number);
    printDoc["id"] = id;
    printDoc["value"] = 0;
    printDoc["blink_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 6)
  {
    float frequency = readDoc["frequency"];
    int number = readDoc["number"];
    blinkLedNoPWM(LED6_PIN, frequency, number);
    printDoc["id"] = id;
    printDoc["value"] = 0;
    printDoc["blink_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 7)
  {
    float frequency = readDoc["frequency"];
    int number = readDoc["number"];
    blinkLedNoPWM(LED7_PIN, frequency, number);
    printDoc["id"] = id;
    printDoc["value"] = 0;
    printDoc["blink_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
}

void sweep(StaticJsonDocument<1500> readDoc)
{
  StaticJsonDocument<1500> printDoc;
  int id = readDoc["id"];
  if (id == 1)
  {
    int duration = readDoc["duration"];
    int number = readDoc["number"];
    sweepLed(LED1_CHANNEL, duration, number);
    printDoc["id"] = 1;
    printDoc["value"] = 0;
    printDoc["sweep_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 2)
  {
    int duration = readDoc["duration"];
    int number = readDoc["number"];
    sweepLed(LED2_CHANNEL, duration, number);
    printDoc["id"] = 2;
    printDoc["value"] = 0;
    printDoc["sweep_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
  if (id == 3)
  {
    int duration = readDoc["duration"];
    int number = readDoc["number"];
    sweepLed(LED3_CHANNEL, duration, number);
    printDoc["id"] = 3;
    printDoc["value"] = 0;
    printDoc["sweep_number"] = number;
    printDoc["teamId"] = teamId;

    String output = "";
    serializeJson(printDoc, output);
    Serial.println(output);
    Serial.println();
    SerialBT.println(output);
  }
}

void LED_Project(StaticJsonDocument<1500> readDoc)
{
  String action = readDoc["action"];
  if (action == "getLEDs")
  {
    getLEDS(readDoc);
  }
  if (action == "getValue")
  {
    getValue(readDoc);
  }
  if (action == "setValue")
  {
    setValue(readDoc);
  }
  if (action == "blink")
  {
    blink(readDoc);
  }
  if (action == "sweep")
  {
    sweep(readDoc);
  }
}

void receivedData()
{
  if (SerialBT.available())
  {
    inputData = SerialBT.readStringUntil('\n');
  }
  Serial.println(inputData);
  StaticJsonDocument<1500> readDoc;
  DeserializationError err = deserializeJson(readDoc, inputData);
  if (err)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.f_str());
  }
  else
  {
    LED_Project(readDoc);
  }
  inputData = "";
}

void setup()
{
  Serial.begin(115200);

  // Initialize BTC
  SerialBT.begin(btcServerName); // Bluetooth device name

  // Initialize the LED pins
  
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);
  pinMode(LED6_PIN, OUTPUT);
  pinMode(LED7_PIN, OUTPUT);

  // Initialize the LED channels for PWM control
  ledcSetup(LED1_CHANNEL, 5000, 8);
  ledcSetup(LED2_CHANNEL, 5000, 8);
  ledcSetup(LED3_CHANNEL, 5000, 8);

  ledcAttachPin(LED1_PIN, LED1_CHANNEL);
  ledcAttachPin(LED2_PIN, LED2_CHANNEL);
  ledcAttachPin(LED3_PIN, LED3_CHANNEL);

  Serial.println("\nThe device started, now you can pair it with bluetooth!\n");
}

void loop()
{
  // Check available Bluetooth data and perform read from the app
  if (SerialBT.available())
  {
    Serial.println("\nConnected\n");
    receivedData();
  }
}