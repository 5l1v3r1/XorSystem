//
//  ANDoubleWrapper.h
//  XorSystem
//
//  Created by Alex Nichol on 10/14/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#ifndef __XorSystem__ANDoubleWrapper__
#define __XorSystem__ANDoubleWrapper__

#include <math.h>
#include <ostream>

#define kSignificantFigures 0.00000001

class ANDoubleWrapper {
private:
    double value;
public:
    ANDoubleWrapper(double aValue);
    ANDoubleWrapper(const ANDoubleWrapper & wrapper);
    virtual double getValue() const;
    
    virtual ANDoubleWrapper & operator=(const ANDoubleWrapper & wrapper);
    virtual bool operator==(const ANDoubleWrapper & wrapper) const;
    virtual bool operator!=(const ANDoubleWrapper & wrapper) const;
    virtual bool operator<(const ANDoubleWrapper & wrapper) const;
    virtual bool operator>(const ANDoubleWrapper & wrapper) const;
    
    virtual ANDoubleWrapper & operator+=(const ANDoubleWrapper & wrapper);
    virtual ANDoubleWrapper & operator*=(const ANDoubleWrapper & wrapper);
    virtual ANDoubleWrapper & operator-=(const ANDoubleWrapper & wrapper);
    virtual ANDoubleWrapper & operator/=(const ANDoubleWrapper & wrapper);
    friend ANDoubleWrapper operator+(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);
    friend ANDoubleWrapper operator*(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);
    friend ANDoubleWrapper operator-(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);
    friend ANDoubleWrapper operator/(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);
};

std::ostream & operator<<(std::ostream & stream, const ANDoubleWrapper & wrapper);

ANDoubleWrapper operator+(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);
ANDoubleWrapper operator*(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);
ANDoubleWrapper operator-(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);
ANDoubleWrapper operator/(const ANDoubleWrapper & w1, const ANDoubleWrapper & w2);

#endif /* defined(__XorSystem__ANDoubleWrapper__) */
