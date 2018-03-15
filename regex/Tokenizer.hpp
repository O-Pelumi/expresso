//
//  tokenize.hpp
//  regex
//
//  Created by Oluwapelumi on 5/4/17.
//  Copyright © 2017 Oluwapelumi. All rights reserved.
//

#ifndef tokenize_hpp
#define tokenize_hpp

#include <stdio.h>
#include <string>
#include <regex>

#include <iostream>
#include "Token.hpp"
#include "Expresso.hpp"


class Tokenizer{
private:
    //std::vector<Token> tokens;
    Expresso expresso;
public:
    explicit Tokenizer (std::string expression);
};

#endif /* tokenize_hpp */
