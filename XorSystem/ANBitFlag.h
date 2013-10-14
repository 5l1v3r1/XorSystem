//
//  ANBitFlag.h
//  XorSystem
//
//  Created by Alex Nichol on 10/14/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#ifndef __XorSystem__ANBitFlag__
#define __XorSystem__ANBitFlag__

#include <ostream>
#include <exception>

class ANBitFlagDivideByZero : std::exception {
};

class ANBitFlag {
private:
    bool flag;
public:
    ANBitFlag(int number);
    ANBitFlag(const ANBitFlag& aFlag);
    virtual bool getValue() const;
    
    virtual ANBitFlag & operator=(const ANBitFlag & wrapper);
    virtual bool operator==(const ANBitFlag & wrapper) const;
    virtual bool operator!=(const ANBitFlag & wrapper) const;
    virtual bool operator<(const ANBitFlag & wrapper) const;
    virtual bool operator>(const ANBitFlag & wrapper) const;
    
    virtual ANBitFlag & operator+=(const ANBitFlag & wrapper);
    virtual ANBitFlag & operator*=(const ANBitFlag & wrapper);
    virtual ANBitFlag & operator-=(const ANBitFlag & wrapper);
    virtual ANBitFlag & operator/=(const ANBitFlag & wrapper);
    friend ANBitFlag operator+(const ANBitFlag & w1, const ANBitFlag & w2);
    friend ANBitFlag operator*(const ANBitFlag & w1, const ANBitFlag & w2);
    friend ANBitFlag operator-(const ANBitFlag & w1, const ANBitFlag & w2);
    friend ANBitFlag operator/(const ANBitFlag & w1, const ANBitFlag & w2);
};

std::ostream & operator<<(std::ostream & stream, const ANBitFlag & wrapper);

ANBitFlag operator+(const ANBitFlag & w1, const ANBitFlag & w2);
ANBitFlag operator*(const ANBitFlag & w1, const ANBitFlag & w2);
ANBitFlag operator-(const ANBitFlag & w1, const ANBitFlag & w2);
ANBitFlag operator/(const ANBitFlag & w1, const ANBitFlag & w2);

#endif /* defined(__XorSystem__ANBitFlag__) */
