//
//  main.cpp
//  XorSystem
//
//  Created by Alex Nichol on 10/14/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#include <iostream>
#include "ANMatrix.h"
#include "ANBitFlag.h"

using namespace std;

int main(int argc, const char * argv[]) {
    const ANBitFlag flags[] = {1, 1, 1, 0, 0, 1, 1, 0, 0};
    ANMatrix<ANBitFlag> matrix(flags, 3, 3);
    std::cout << "Inverse of matrix: " << matrix.invert().toMATLABString() << std::endl;
    std::cout << "Identity: " << (matrix.invert() * matrix).toMATLABString() << std::endl;
    
    return 0;
}

