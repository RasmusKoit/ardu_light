# Arduino RGB LED Controller with HSV Color Model

This project uses an Arduino Nano to control an RGB LED with potentiometers for hue and saturation adjustments, and buttons to toggle the LED state and adjust brightness. The HSB (Hue, Saturation, Value) color model is used to generate colors.

## Components

- Arduino Board
- RGB LED
- White LED
- Potentiometer x2
- Push Button x2
- Resistors
- Breadboard and Jumper Wires

## Pin Configuration

- `A0`: Hue Potentiometer
- `A1`: Saturation Potentiometer
- `10`: Red LED Pin
- `9`: Green LED Pin
- `8`: Blue LED Pin
- `7`: White LED Pin
- `5`: Button 1 (Toggle LEDs)
- `4`: Button 2 (Adjust Brightness)

## Installation

1. Connect the components as per the circuit diagram.
2. Upload the provided Arduino code to your Arduino board.

## Usage

- **Potentiometers**:
  - The potentiometer connected to `A0` adjusts the hue.
  - The potentiometer connected to `A1` adjusts the saturation.
- **Buttons**:
  - The button connected to `Pin 5` toggles the LED on and off.
  - The button connected to `Pin 4` adjusts the brightness in increments of 0.125 (12.5%).

## Code Explanation

### Global Variables

- **Pin Definitions**: Constants for the pin numbers.
- **Reading Arrays**: Arrays to store potentiometer readings for averaging.
- **Brightness**: A float to store the current brightness level.
- **Button States**: Variables to track button press states and debounce.

### Setup Function

- Initializes pins as inputs or outputs.
- Sets up the serial communication for debugging.
- Initializes the reading arrays.

### Loop Function

- Reads potentiometer values and updates running totals for averaging.
- Maps the averaged potentiometer readings to hue and saturation values.
- Handles button presses for toggling LED state and adjusting brightness.
- Converts HSV values to RGB and sets the LED color.

### HSV to RGB Conversion

- Converts HSV color values to RGB using standard conversion formulas.
- Adjusts LED brightness and sets the color using PWM.

### Set Color Function

- Adjusts RGB values based on brightness.
- Inverts the RGB values for common anode LED.
- Writes the adjusted values to the LED pins.

### Invert Value Function

- Inverts an 8-bit value (0-255).

## License

This project is open-source and available under the MIT License. Feel free to modify and distribute as needed.
