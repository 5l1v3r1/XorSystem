//
//  ANDoubleWrapper.cpp
//  XorSystem
//
//  Created by Alex Nichol on 10/14/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#include "ANDoubleWrapper.h"

ANDoubleWrapper::ANDoubleWrapper(double _value) {
    this->value = _value;
}

ANDoubleWrapper::ANDoubleWrapper(const ANDoubleWrapper & wrapper) {
    this->value = wrapper.value;
}

double ANDoubleWrapper::getValue() const {
    return this->value;
}

bool ANDoubleWrapper::operator==(const ANDoubleWrapper & wrapper) const {
    return fabs(wrapper.value - this->value) < kSignificantFigures;
}

bool ANDoubleWrapper::operator!=(const ANDoubleWrapper & wrapper) const {
    return !(*this == wrapper);
}

bool ANDoubleWrapper::operator<(const ANDoubleWrapper & wrapper) const {
    if (wrapper == *this) return false;
    return this->value < wrapper.value;
}

bool ANDoubleWrapper::operator>(const ANDoubleWrapper & wrapper) const {
    if (wrapper == *this) return false;
    return this->value > wrapper.value;
}

ANDoubleWrapper & ANDoubleWrapper::operator=(const ANDoubleWrapper & wrapper) {
    this->value = wrapper.getValue();
    return *this;
}

ANDoubleWrapper & ANDoubleWrapper::operator+=(const ANDoubleWrapper & wrapper) {
    value += wrapper.getValue();
    return *this;
}

ANDoubleWrapper & ANDoubleWrapper::operator*=(const ANDoubleWrapper & wrapper) {
    value *= wrapper.getValue();
    return *this;
}

ANDoubleWrapper & ANDoubleWrapper::operator-=(const ANDoubleWrapper & wrapper) {
    value -= wrapper.getValue();
    return *this;
}

ANDoubleWrapper & ANDoubleWrapper::operator/=(const ANDoubleWrapper & wrapper) {
    value /= wrapper.getValue();
    return *this;
}

ANDoubleWrapper operator+(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2) {
    return ANDoubleWrapper(w1.getValue() + w2.getValue());
}

ANDoubleWrapper operator*(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2) {
    return ANDoubleWrapper(w1.getValue() * w2.getValue());
}

ANDoubleWrapper operator-(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2) {
    return ANDoubleWrapper(w1.getValue() - w2.getValue());
}

ANDoubleWrapper operator/(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2) {
    return ANDoubleWrapper(w1.getValue() / w2.getValue());
}

std::ostream & operator<<(std::ostream & stream, const ANDoubleWrapper & wrapper) {
    return (stream << wrapper.getValue());
}
