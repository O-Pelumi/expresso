//
//  token.hpp
//  regex
//
//  Created by Oluwapelumi on 5/4/17.
//  Copyright © 2017 Oluwapelumi. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <string>
#include <tuple>
#include <cassert>
#include <iostream>

enum class OPP {
    NOP,
    LB,
    RB,
    ADD,
    MUL,
    DIV,
    SUB,
    SIN,
    COS,
    TAN,
    POW
};

class Token {
private:
    double operand;
    OPP operation;
public:
    Token();
    explicit Token (double operand);
    explicit Token (OPP operation);
    bool isUnary();
    bool isOperand();
    
    double getOperand();
    OPP getOperation();
    static std::tuple<OPP, bool> asciiToOperator(const char* opp);
    
};


std::ostream& operator<<(std::ostream& stream, OPP opp);
std::ostream& operator<<(std::ostream& stream, Token token);

#endif /* token_hpp */
