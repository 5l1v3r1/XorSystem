//
//  ANBitFlag.cpp
//  XorSystem
//
//  Created by Alex Nichol on 10/14/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#include "ANBitFlag.h"

ANBitFlag::ANBitFlag(int value) {
    this->flag = value != 0;
}

ANBitFlag::ANBitFlag(const ANBitFlag & wrapper) {
    this->flag = wrapper.getValue();
}

bool ANBitFlag::getValue() const {
    return this->flag;
}

bool ANBitFlag::operator==(const ANBitFlag & wrapper) const {
    return this->flag == wrapper.getValue();
}

bool ANBitFlag::operator!=(const ANBitFlag & wrapper) const {
    return !(*this == wrapper);
}

bool ANBitFlag::operator<(const ANBitFlag & wrapper) const {
    if (wrapper == *this) return false;
    return this->flag == 0 && wrapper.getValue() == 1;
}

bool ANBitFlag::operator>(const ANBitFlag & wrapper) const {
    if (wrapper == *this) return false;
    return this->flag == 1 && wrapper.getValue() == 0;
}

ANBitFlag & ANBitFlag::operator=(const ANBitFlag & wrapper) {
    this->flag = wrapper.getValue();
    return *this;
}

ANBitFlag & ANBitFlag::operator+=(const ANBitFlag & wrapper) {
    this->flag ^= wrapper.getValue();
    return *this;
}

ANBitFlag & ANBitFlag::operator*=(const ANBitFlag & wrapper) {
    this->flag = wrapper.getValue() == 1 && this->flag == 1;
    return *this;
}

ANBitFlag & ANBitFlag::operator-=(const ANBitFlag & wrapper) {
    return (*this -= wrapper);
}

ANBitFlag & ANBitFlag::operator/=(const ANBitFlag & wrapper) {
    if (!wrapper.getValue()) {
        throw new ANBitFlagDivideByZero();
    }
    return *this;
}

ANBitFlag operator+(const ANBitFlag & w1, const ANBitFlag & w2) {
    return ANBitFlag(w1.getValue() + w2.getValue());
}

ANBitFlag operator*(const ANBitFlag & w1, const ANBitFlag & w2) {
    return ANBitFlag(w1.getValue() * w2.getValue());
}

ANBitFlag operator-(const ANBitFlag & w1, const ANBitFlag & w2) {
    return ANBitFlag(w1.getValue() - w2.getValue());
}

ANBitFlag operator/(const ANBitFlag & w1, const ANBitFlag & w2) {
    return ANBitFlag(w1.getValue() / w2.getValue());
}

std::ostream & operator<<(std::ostream & stream, const ANBitFlag & wrapper) {
    return (stream << wrapper.getValue());
}