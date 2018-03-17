//
//  Expresso.hpp
//  regex
//
//  Created by Oluwapelumi on 3/1/18.
//  Copyright © 2018 Oluwapelumi. All rights reserved.
//

#ifndef Expresso_hpp
#define Expresso_hpp

#include <stdio.h>
#include <cmath>

#include <vector>
#include "Token.hpp"

class Expresso {
    constexpr static double RAD2DEG = (22.0/7.0)/180.0;
    struct ExpressoNode;
    
    std::vector<ExpressoNode*> nodeStack;
    std::vector<ExpressoNode*> operatorStack;
    
    static int precedenceLevel(OPP opp);
    static int precedence(OPP lhs, OPP rhs);
    
    void updateTree();
    
public:
    Expresso();
    void visitToken(Token tok);
    void evaluate();
};

#endif /* Expresso_hpp */
