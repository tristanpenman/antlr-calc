#include <iostream>
#include <sstream>
#include <string>
#include <antlr4-runtime.h>

#include "generated/ExpressionLexer.h"
#include "generated/ExpressionParser.h"

int main() {
    const std::string input("1.2 * (1.5 + 2) * -1");
    antlr4::ANTLRInputStream inputStream(input);
    ExpressionLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();
    ExpressionParser parser(&tokens);
    ExpressionParser::MainContext* tree = parser.main();
    std::cout << tree->toStringTree() << std::endl;
    return 0;
}
