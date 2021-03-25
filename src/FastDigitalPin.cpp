#include "FastDigitalPin.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void determine_pinData(uint8_t pinNumber, pinData* data) {
    data->pinBitMask = digitalPinToBitMask(pinNumber);
    data->pinPort = digitalPinToPort(pinNumber);
    data->pinReg = portModeRegister(data->pinPort);
    data->pinOut = portOutputRegister(data->pinPort);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FastPinMode(pinData pin, uint8_t mode) {
    if (mode == INPUT) {
        *pin.pinReg &= ~pin.pinBitMask;
        *pin.pinOut &= ~pin.pinBitMask;
    }
    else if (mode == INPUT_PULLUP) {
        *pin.pinReg &= ~pin.pinBitMask;
        *pin.pinOut |= pin.pinBitMask;
    }
    else {
        *pin.pinReg |= pin.pinBitMask;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t FastDigitalRead(pinData pin) {
    if (*portInputRegister(pin.pinPort) & (pin.pinBitMask)) {
        return HIGH;
    }

    return LOW;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FastDigitalWrite(pinData pin, uint8_t val) {
    if (val == LOW) {
        *pin.pinOut &= ~pin.pinBitMask;
    }
    else {
        *pin.pinOut |= pin.pinBitMask;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
