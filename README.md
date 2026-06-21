# Vibration Motor Speed Controller (Arduino)

Control the speed of a vibration motor with an Arduino through the Serial Monitor. The user enters a PWM value from 0–255 to adjust vibration intensity in real time.

## Features

- Motor speed control via PWM signal (`analogWrite`) on digital pin 9.
- Serial command input: type a number `0–255` and press Enter.
- Automatic value clamping to the valid range `[0, 255]`.
- Real-time feedback showing current speed and the corresponding percentage.
- A 50 ms timeout mechanism that lets it work even when the Serial Monitor does not send a Newline character.

## Hardware Requirements

| Component | Description |
|---|---|
| Arduino (Uno/Nano…) | Main controller board |
| Vibration motor | The motor being driven |
| Transistor / MOSFET | Amplifies current to drive the motor (the motor should not be connected directly to an Arduino pin) |
| Flyback diode | Protects the circuit from inductive voltage spikes |
| External power supply | Powers the motor if needed |

> **Note:** The default PWM pin is **D9**. You can change it via the `MOTOR_PIN` constant in the code.

## Wiring (suggested)

```
Arduino D9 ──[R]──> Gate/Base of MOSFET/Transistor
Motor (+) ──────────> Power +
Motor (−) ──────────> Drain/Collector
Source/Emitter ─────> GND shared with Arduino
Flyback diode in parallel with the motor (cathode toward Power +)
```

## Installation & Usage

1. Open `dieu_khien_vibration_motor.ino` in the Arduino IDE.
2. Select the correct board and COM port.
3. Upload the code to the Arduino.
4. Open the **Serial Monitor** and set the baud rate to **9600**.
5. Enter a number from `0` to `255` and press Enter.

### Example

```
150
>> Toc do: 150/255 (58%)
```

- `0` → motor off
- `255` → maximum speed

## Configuration

| Parameter | Default | Meaning |
|---|---|---|
| `MOTOR_PIN` | `9` | PWM pin controlling the motor |
| `TIMEOUT` | `50` ms | Wait time before processing the buffer when no Newline is received |
| Baud rate | `9600` | Serial communication speed |

## How It Works

The code reads characters from Serial one at a time into a string buffer. The buffer is processed when a newline character (`\n`/`\r`) is received, or when more than 50 ms pass without a new character (handling the case where the Serial Monitor does not send a Newline). After processing, the string is converted to an integer, clamped to `[0, 255]`, and written to the PWM pin with `analogWrite`.

## Project Structure

```
.
├── dieu_khien_vibration_motor.ino
└── README.md
```

## License

MIT
