
#ifndef EXPRESSO_H
#define EXPRESSO_H

#include <stdio.h>
#include <cmath>
#include <vector>

#include "token.h"

class Expresso {
    constexpr static double RAD2DEG = (22.0/7.0)/180.0;
    struct ExpressoNode;
    
    std::vector<ExpressoNode*> nodeStack;
    std::vector<ExpressoNode*> operatorStack;
    
    static bool isUnary(OPP operation);
    static int precedenceLevel(OPP opp);
    static int precedence(OPP lhs, OPP rhs);
    static void deleteNode(ExpressoNode*);
    
    void updateTree();
    
public:
    Expresso(std::string expression);
    Expresso() = delete;
    Expresso(Expresso&) = delete;
    void operator=(Expresso&) = delete;
    virtual ~Expresso();
    
    void visitToken(Token tok);
    double evaluate();
};

#endif /* Expresso_hpp */
