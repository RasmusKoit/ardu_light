#include <Arduino.h>

const int huePotPin = A0;
const int saturationPotPin = A1;
const int redLedPin = 10;
const int greenLedPin = 9;
const int blueLedPin = 8;
const int whiteLedPin = 7;
const int button1Pin = 5;
const int button2Pin = 4;

const int numReadings = 20;
int hueReadings[numReadings];
int saturationReadings[numReadings];
int readingIndex = 0;
int totalHue = 0;
int totalSaturation = 0;

float brightness = 1.0;
unsigned long lastButtonPress1 = 0;
unsigned long lastButtonPress2 = 0;
bool button1Pressed = false;

void setColor(int, int, int, int);
int invertValue(int);
void hsvToRGB(int, float, float);

void setup()
{
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(whiteLedPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  Serial.begin(9600);

  for (int i = 0; i < numReadings; i++)
  {
    hueReadings[i] = 0;
    saturationReadings[i] = 0;
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(10);

  totalHue -= hueReadings[readingIndex];
  totalSaturation -= saturationReadings[readingIndex];

  hueReadings[readingIndex] = analogRead(huePotPin);
  saturationReadings[readingIndex] = analogRead(saturationPotPin);

  totalHue += hueReadings[readingIndex];
  totalSaturation += saturationReadings[readingIndex];

  readingIndex = (readingIndex + 1) % numReadings;

    // Calculate the average
  int huePotRead = totalHue / numReadings;
  int saturationPotRead = totalSaturation / numReadings;

  int hueValue = map(huePotRead, 0, 1023, 1, 360);
  float saturationValue = map(saturationPotRead, 0, 1023, 1, 360);

  // add small delay to prevent flickering

  if (digitalRead(button1Pin) == LOW && millis() - lastButtonPress1 > 500)
  {
    lastButtonPress1 = millis();
    button1Pressed = !button1Pressed;
  }

  if (digitalRead(button2Pin) == LOW && millis() - lastButtonPress2 > 500)
  {
    lastButtonPress2 = millis();
    // change the brightness in increments of 0.1
    brightness = brightness + 0.125;
    if (brightness > 1.0)
    {
      brightness = 0.125;
    }
  }

  if (button1Pressed)
  {
    setColor(0, 0, 0, 0);
    analogWrite(whiteLedPin, 0);
  }
  else
  {
    hsvToRGB(hueValue, saturationValue, brightness);
    analogWrite(whiteLedPin, brightness * 255);
  }
}

void hsvToRGB(int hue, float saturation, float brightness)
{
  // Convert HSV to RGB

  int red, green, blue;
  saturation = saturation / 360.0;
  if (saturation == 0)
  {
    red = green = blue = brightness * 255;
  }
  else
  {
    // double sectorPos = hue / 60.0;
    // int sectorNumber = (int)(floor(sectorPos));
    double sectorPos = hue / 60.0;
    int sectorNumber = (int)sectorPos;
    double fractionalSector = sectorPos - sectorNumber;

    // Calculate values for the three axes of the color
    double p = brightness * (1.0 - saturation);
    double q = brightness * (1.0 - (saturation * fractionalSector));
    double t = brightness * (1.0 - (saturation * (1 - fractionalSector)));

    p *= 255;
    q *= 255;
    t *= 255;
    brightness *= 255;
    // Assign the fractional values to the correct axes
    switch (sectorNumber)
    {
    case 0:
      red = brightness, green = t, blue = p;
      break;
    case 1:
      red = q, green = brightness, blue = p;
      break;
    case 2:
      red = p, green = brightness, blue = t;
      break;
    case 3:
      red = p, green = q, blue = brightness;
      break;
    case 4:
      red = t, green = p, blue = brightness;
      break;
    case 5:
      red = brightness, green = p, blue = q;
      break;
    case 6:
      red = 0, green = 0, blue = 0, brightness = 0;
      break;
    }
    setColor(red, green, blue, brightness);
    Serial.println("Hue: " + String(hue) + " Saturation: " + String(saturation) + " Brightness: " + String(brightness) + " Red: " + String(red) + " Green: " + String(green) + " Blue: " + String(blue) + " White: " + String(brightness) + " Sector: " + String(sectorNumber) + " Fractional: " + String(fractionalSector) + " P: " + String(p) + " Q: " + String(q) + " T: " + String(t));
  }
}
// put function definitions here:
void setColor(int red, int green, int blue, int brightness)
{

  // Invert the brightness for common anode LED

  // Adjust the RGB values based on the brightness
  red = map(red, 0, 255, 0, brightness);
  green = map(green, 0, 255, 0, brightness);
  blue = map(blue, 0, 255, 0, brightness);

  // Invert the RGB values for common anode LED
  red = invertValue(red);
  green = invertValue(green);
  blue = invertValue(blue);

  analogWrite(redLedPin, red);
  analogWrite(greenLedPin, green);
  analogWrite(blueLedPin, blue);
}

int invertValue(int value)
{
  return 255 - value;
}