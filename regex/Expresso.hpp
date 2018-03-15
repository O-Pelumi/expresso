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
    struct ExpressoNode {
        Token token;
        ExpressoNode* left;
        ExpressoNode* right;
        
        explicit ExpressoNode(Token tok) : left(nullptr), right(nullptr) {
            std::swap(tok, token);
        }
        
        void setLAndR(ExpressoNode *lhs, ExpressoNode *rhs) {
            left = lhs;
            right = rhs;
        }
        
        double eveluate() {
            if (token.isOperand())
                return token.getOperand();
            
            double val = std::numeric_limits<double>::infinity();
            if (!left || !right)
                return val;
            
            switch (token.getOperation()) {
                case OPP::ADD:
                    val = left->eveluate() + right->eveluate();
                    break;
                case OPP::SUB:
                    val = left->eveluate() - right->eveluate();
                    break;
                case OPP::MUL:
                    val = left->eveluate() * right->eveluate();
                    break;
                case OPP::DIV:
                    val = left->eveluate() / right->eveluate();
                    break;
                case OPP::POW:
                    val = pow(left->eveluate(), right->eveluate());
                    break;
                case OPP::NOP:
                case OPP::LB:
                case OPP::RB:
                case OPP::SIN:
                case OPP::COS:
                case OPP::TAN:
                    break;
            }
            
            return val;
        }
    };
    
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
