//
//  Expresso.cpp
//  regex
//
//  Created by Oluwapelumi on 3/1/18.
//  Copyright © 2018 Oluwapelumi. All rights reserved.
//

#include "Expresso.hpp"
#include "cassert"


struct Expresso::ExpressoNode {
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
        if (!left)
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
                val = std::sin(left->eveluate() * RAD2DEG);
                break;
            case OPP::COS:
                val = std::cos(left->eveluate() * RAD2DEG);
                break;
            case OPP::TAN:
                val = std::tan(left->eveluate() * RAD2DEG);
                break;
        }
        
        return val;
    }
};




Expresso::Expresso() : nodeStack(0)
{
    
}

int Expresso::precedenceLevel(OPP opp)
{
    int level;
    switch (opp) {
        case OPP::NOP:
            level = 0;
            break;
        case OPP::RB:
            level = 1;
            break;
        case OPP::ADD:
        case OPP::SUB:
            level = 2;
            break;
        case OPP::MUL:
        case OPP::DIV:
            level = 3;
            break;
        case OPP::POW:
            level = 4;
            break;
        case OPP::SIN:
        case OPP::COS:
        case OPP::TAN:
            level = 5;
            break;
        case OPP::LB:
            level = 6;
            break;
    }
    return level;
}

/*
 *@note     I choose not to catch exceptions here for performance reason as this
 *          function will obviously be called multiple times in the process of
 *          building an expression tree, for example, 2(^3) will not be caught,
 *          it is the responsibility of the calling function to handle to such
 *          inputs
 */
int Expresso::precedence(OPP top, OPP newTop)
{
    int precedence;
    
    if (newTop == OPP::LB || top == OPP::LB || newTop == OPP::POW) {    // We can always stack Left brackets and power
        precedence = 1;
    } else {
        precedence = precedenceLevel(newTop) - precedenceLevel(top);
    }
    if (precedence < 0) {
        std::cout << newTop << " is of lesser precedence to " << top << std::endl;
    } else if (precedence > 0) {
        std::cout << newTop << " is of higher precedence to " << top << std::endl;
    } else {
        std::cout << newTop << " is of equal precedence to " << top << std::endl;
    }
    return precedence;
}

void Expresso::visitToken(Token token)
{
    if (token.isOperand()) {
        // keep temporarily in vector
        nodeStack.push_back(new ExpressoNode(std::move(token)));
        return;
    }
    
    OPP newOperator = token.getOperation();
    
    while (operatorStack.size() && precedence(operatorStack.back()->token.getOperation(), newOperator) < 1) {
        updateTree();
    }
    
    if (newOperator == OPP::RB) {
        // pop LB after evaluation if token.getOperation() is RB
        OPP lb = operatorStack.back()->token.getOperation();
        std::cout << " assert(operatorStack.back() == (-" << lb  << "-) )" << std::endl;
        assert(lb == OPP::LB);
        operatorStack.pop_back();
        return;
    }
    
    operatorStack.push_back(new ExpressoNode(std::move(token)));
}

void Expresso::updateTree()
{
    std::cout << __FUNCTION__ << std::endl;
    // Create tree here
    ExpressoNode *node = operatorStack.back();
    operatorStack.pop_back();
    
    // Unary Corner Case
    if (node->token.isUnary()) {
        // Sometimes-unary operations like + and - are only unary in two cases
        // 1. This is the  easy one when the very first token is  + or -, e.g. -2 * 5
        // 2. The second case is a bracket preceeding token, e.g. 2 + (-2)
        // 3. Or even more interesting is the case of -(-(-2))
        // sin(90)*2, -90*2^2+1
        auto opp =  node->token.getOperation();
        if (opp != OPP::ADD && opp != OPP::SUB) {
            ExpressoNode *lhs = nodeStack.back();
            nodeStack.pop_back();
            node->left = lhs;
            nodeStack.push_back(node);
            printf("Handled Unary");
            return;
        }
        
    }
    
    assert(nodeStack.size() > 1);
    
    ExpressoNode *rhs = nodeStack.back();
    nodeStack.pop_back();
    
    ExpressoNode *lhs = nodeStack.back();
    nodeStack.pop_back();
    
    node->setLAndR(lhs, rhs);
    nodeStack.push_back(node);
}

void Expresso::evaluate()
{
    // Lazy tree update
    while (operatorStack.size()) {
        updateTree();
    }
    
    assert(nodeStack.size() == 1);  // That's the root
    std::cout << "Expression result = " << nodeStack.back()->eveluate() << std::endl;
}
