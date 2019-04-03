#include <iostream>
#include <strstream>
#include <string>
#include <antlr4-runtime.h>

#include "generated/ExpressionLexer.h"
#include "generated/ExpressionParser.h"
#include "ErrorListener.h"
#include "EvalVisitor.h"
#include "PrintVisitor.h"

int main()
{
    while (std::cin) {
        std::cout << "> ";
        std::string input;
        if (!std::getline(std::cin, input)) {
            break;
        }

        // Wire up lexer and parser
        antlr4::ANTLRInputStream inputStream(input);
        ExpressionLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        ExpressionParser parser(&tokens);

        // Configure error handling
        ErrorListener errorListener;
        lexer.removeErrorListeners();
        parser.removeErrorListeners();
        parser.addErrorListener(&errorListener);

        try {
            // Parse the expression
            tokens.fill();
            ExpressionParser::MainContext* tree = parser.main();
            PrintVisitor printVisitor;
            std::cout << printVisitor.visitMain(tree).as<std::string>() << std::endl;
            EvalVisitor evalVisitor;
            std::cout << evalVisitor.visitMain(tree).as<double>() << std::endl;
        } catch (std::exception & ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }

    std::cout << std::endl;

    return 0;
}
