//
//  main.cpp
//  regex
//
//  Created by Oluwapelumi on 5/4/17.
//  Copyright © 2017 Oluwapelumi. All rights reserved.
//

#include <iostream>
#include <string>
#include <regex>
#include "Tokenizer.hpp"


int main(int argc, const char * argv[]) {
    // Nameless object:)
    //Tokenizer {"2 + 55 - 6.775 / sin ( 90 ) * 76 * cos0"};
    //Tokenizer {"5+((1+2)*4)-3^2^3"};
    //Tokenizer {"(5)+((1+2)*4)-3^2^2*2"};
    Tokenizer {"2 + sin(90)"};
    return 0;
}
