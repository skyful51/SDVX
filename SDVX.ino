#include <Keyboard.h>
#include <Joystick.h>

struct ButtonMapping {
    int buttonPin;
    int key;
};

ButtonMapping buttonMappings[] = {
    {2, 'A'},  // 버튼 1
    {3, 'B'},  // 버튼 2
    {4, 'C'},  // 버튼 3
    {5, 'D'},  // 버튼 4
    {6, 'E'},  // 버튼 5
    {7, 'F'},  // 버튼 6
    {8, 'G'}   // 버튼 7
};

struct EncoderMapping {
    int encoderPinA;
    int encoderPinB;
    int joystickAxis;
};

EncoderMapping encoderMappings[] = {
    {9, 10, JOYSTICK_X},  // 엔코더 1
    {11, 12, JOYSTICK_Y}  // 엔코더 2
};

Joystick_ joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   sizeof(buttonMappings) / sizeof(buttonMappings[0]),
                   sizeof(encoderMappings) / sizeof(encoderMappings[0]));

void setup() {
    for (int i = 0; i < sizeof(buttonMappings) / sizeof(buttonMappings[0]); i++) {
        pinMode(buttonMappings[i].buttonPin, INPUT);
    }

    for (int i = 0; i < sizeof(encoderMappings) / sizeof(encoderMappings[0]); i++) {
        pinMode(encoderMappings[i].encoderPinA, INPUT);
        pinMode(encoderMappings[i].encoderPinB, INPUT);
    }

    Keyboard.begin();
    joystick.begin();
}

void pressButton(int buttonPin, int key) {
    int buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
        Keyboard.press(key);
    } else {
        Keyboard.release(key);
    }
}

void updateJoystickAxis(int encoderPinA, int encoderPinB, int joystickAxis) {
    int encoderStateA = digitalRead(encoderPinA);
    int encoderStateB = digitalRead(encoderPinB);

    if (encoderStateA == HIGH && encoderStateB == LOW) {
        joystick.setAxis(joystickAxis, -127);
    } else if (encoderStateA == LOW && encoderStateB == HIGH) {
        joystick.setAxis(joystickAxis, 127);
    } else {
        joystick.setAxis(joystickAxis, 0);
    }
}

void loop() {
    for (int i = 0; i < sizeof(buttonMappings) / sizeof(buttonMappings[0]); i++) {
        pressButton(buttonMappings[i].buttonPin, buttonMappings[i].key);
    }

    for (int i = 0; i < sizeof(encoderMappings) / sizeof(encoderMappings[0]); i++) {
        updateJoystickAxis(encoderMappings[i].encoderPinA, encoderMappings[i].encoderPinB, encoderMappings[i].joystickAxis);
    }

    joystick.sendState();
    delay(10);
}