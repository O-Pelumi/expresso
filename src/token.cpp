//
//  token.cpp
//  regex
//
//  Created by Oluwapelumi on 5/4/17.
//  Copyright © 2017 Oluwapelumi. All rights reserved.
//

#include "token.h"

Token::Token() : operand(0.0), operation(OPP::NOP)
{
}

Token::Token(double operand) : operand(operand), operation(OPP::NOP)
{
}

Token::Token(OPP operation) : operand(0.0), operation(operation)
{
}

bool Token::isOperand()
{
    return operation == OPP::NOP;
}

double Token::getOperand()
{
    assert(operation == OPP::NOP);
    return operand;
}

OPP Token::getOperation()
{
    assert(operation != OPP::NOP);
    return operation;
}

std::tuple<OPP, bool> Token::asciiToOperator(const char* opp)
{
//#warning The message expects all operations to be in lower case for now
    std::tuple<OPP, bool> ret;
    
    if (!std::strcmp(opp, "+")) {
        ret = {OPP::ADD, true};
    } else if (!std::strcmp(opp, "-")) {
        ret = {OPP::SUB, true};
    } else if (!std::strcmp(opp, "*")) {
        ret = {OPP::MUL, true};
    } else if (!std::strcmp(opp, "/")) {
        ret = {OPP::DIV, true};
    } else if (!std::strcmp(opp, "sin")) {
        ret = {OPP::SIN, true};
    } else if (!std::strcmp(opp, "cos")) {
        ret = {OPP::COS, true};
    } else if (!std::strcmp(opp, "tan")) {
        ret = {OPP::TAN, true};
    } else if (!std::strcmp(opp, "(")) {
        ret = {OPP::LB, true};
    } else if (!std::strcmp(opp, ")")) {
        ret = {OPP::RB, true};
    } else if (!std::strcmp(opp, "^")) {
        ret = {OPP::POW, true};
    } else {
        ret = {OPP::NOP, false};
    }
    
    return ret;
}

std::ostream& operator<<(std::ostream& stream, OPP opp)
{
    // Intentionally not including default
    switch (opp) {
        case OPP::NOP:
            stream << "NOP";
            break;
        case OPP::LB:
            stream << "(";
            break;
        case OPP::RB:
            stream << ")";
            break;
        case OPP::ADD:
            stream << "+";
            break;
        case OPP::MUL:
            stream << "*";
            break;
        case OPP::DIV:
            stream << "/";
            break;
        case OPP::SUB:
            stream << "-";
            break;
        case OPP::SIN:
            stream << "SIN";
            break;
        case OPP::COS:
            stream << "COS";
            break;
        case OPP::TAN:
            stream << "TAN";
            break;
        case OPP::POW:
            stream << "^";
            break;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Token token)
{
    if (token.isOperand())
        stream << token.getOperand();
    else
        token.getOperation();
    return stream;
}
