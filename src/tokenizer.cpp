#include "tokenizer.h"

Tokenizer::Tokenizer (std::string expression, Expresso& expresso)
{
    // I might want to change ? to * later on if I decide to pick 6.77.5
    // as a single token rather than three (3) different tokens - 6.77, . and 5
    std::regex pattern("(\\d+(\\.\\d+)?)|[\\+-/*^\\(\\)]|(sin)|(cos)|(tan)");
    
    auto words_begin = std::sregex_iterator(expression.begin(), expression.end(), pattern);
    auto words_end = std::sregex_iterator();
    // std::cout << "found " << std::distance(words_begin, words_end) << " words\n";
    
    while (words_begin != words_end) {
        std::smatch match = *words_begin;
        
        bool isNumeric = std::regex_match(match.str(), std::regex("\\d+(\\.\\d+)*"));
        if (isNumeric) {
            expresso.visitToken(Token(atof(match.str().c_str())));            
        } else {
            auto [opp, success] = Token::asciiToOperator(match.str().c_str());
            if (success) {
                expresso.visitToken(Token(opp));
            } else {
                // maybe throw exception
                std::cout << "Unknown Operator: " << match.str() << std::endl;
                std::cout << "Position: " << match.position() << std::endl;
                std::cout << "Length: " << match.length() << std::endl;
                printf("Error parsing input");
                break;
            }
        }
        words_begin++;
    }

    std::cout << std::endl;
}
