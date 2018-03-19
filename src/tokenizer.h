#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <string>
#include <regex>
#include <iostream>

#include "token.h"
#include "expresso.h"


class Tokenizer{
public:
    Tokenizer() = delete;
    Tokenizer (std::string expression, Expresso& expresso);
};

#endif /* tokenize_hpp */
