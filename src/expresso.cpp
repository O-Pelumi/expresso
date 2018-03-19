
#include <cassert>
#include "tokenizer.h"

#include "expresso.h"



struct Expresso::ExpressoNode {
    Token token;
    ExpressoNode* left;
    ExpressoNode* right;
    bool isUnary;
    
    explicit ExpressoNode(Token tok) : left(nullptr), right(nullptr) {
        std::swap(tok, token);
    }
    
    ExpressoNode(Token tok, bool ifUnary) : left(nullptr), right(nullptr), isUnary(ifUnary) {
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




Expresso::Expresso(std::string expression) : nodeStack(0)
{
    Tokenizer {expression, *this};
}

Expresso::~Expresso()
{
    for (auto node : operatorStack)
        delete node;
    for (auto node : nodeStack) {
        // recursively delete objects
        deleteNode(node);
    }
}

void Expresso::deleteNode(ExpressoNode* node)
{
    if (node->left)
        deleteNode(node->left);
    if (node->right)
        deleteNode(node->right);
    delete node;
}

bool Expresso::isUnary(OPP operation)
{
    if (operation == OPP::SIN || operation == OPP::COS || operation == OPP::TAN)
        return true;
    return false;
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
    // if (precedence < 0) {
    //     std::cout << newTop << " is of lesser precedence to " << top << std::endl;
    // } else if (precedence > 0) {
    //     std::cout << newTop << " is of higher precedence to " << top << std::endl;
    // } else {
    //     std::cout << newTop << " is of equal precedence to " << top << std::endl;
    // }
    return precedence;
}

void Expresso::visitToken(Token token)
{
    // Sometimes-unary operations like + and - are only unary in two cases
    // 1. This first is when the very first token is  + or -, e.g. -2 * 5
    // 2. The second case is a bracket preceeding token, e.g. 2 + (-2), -(-(-2))
    // sin(90)*2, -90*2^2+1
    bool isUnary = false;
    
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
        // std::cout << " assert(operatorStack.back() == (-" << lb  << "-) )" << std::endl;
        assert(lb == OPP::LB);
        operatorStack.pop_back();
        return;
    } else if (Expresso::isUnary(newOperator)) {
        isUnary = true;
    } else if (newOperator == OPP::ADD || newOperator == OPP::SUB) {
        // It's important to note last token is not necessarily the back operatorStack
        // So how do I tell the difference between (2 + 3) and (+3)
        if (!nodeStack.size()) {
            isUnary = true;
        }
    }
    
    operatorStack.push_back(new ExpressoNode(std::move(token), isUnary));
}

void Expresso::updateTree()
{
    ExpressoNode *rhs = nullptr;
    ExpressoNode *lhs = nullptr;
    
    // Create tree here
    ExpressoNode *node = operatorStack.back();
    operatorStack.pop_back();
    
    // Unary Corner Case
    if (node->isUnary) {
        auto opp =  node->token.getOperation();
        if (opp == OPP::ADD || opp == OPP::SUB) {
            // it becomes 0 - value or 0 + value
            lhs = new ExpressoNode(Token(0.0));
        } else {
            ExpressoNode *lhs = nodeStack.back();
            nodeStack.pop_back();
            node->left = lhs;
            nodeStack.push_back(node);
            return;
        }
    }
    // Binary Operations down here
    // -x and +x are handled as binary (0 - x) and (0 + x)
    if (!node->isUnary)
        assert(nodeStack.size() > 1);
    
    rhs = nodeStack.back();
    nodeStack.pop_back();
    
    if (!lhs) {
        lhs = nodeStack.back();
        nodeStack.pop_back();
    }
    
    node->setLAndR(lhs, rhs);
    nodeStack.push_back(node);
}

double Expresso::evaluate()
{
    // Lazy tree update
    while (operatorStack.size()) {
        updateTree();
    }
    
    assert(nodeStack.size() == 1);  // That's the root
    return nodeStack.back()->eveluate();
}
