#include <iostream>
#include <strstream>
#include <string>
#include <antlr4-runtime.h>

#include "generated/ExpressionLexer.h"
#include "generated/ExpressionParser.h"

class MyParserErrorListener: public antlr4::BaseErrorListener
{
    virtual void syntaxError(
        antlr4::Recognizer * recognizer,
        antlr4::Token * offendingSymbol,
        size_t line,
        size_t charPositionInLine,
        const std::string & msg,
        std::exception_ptr e
    ) {
        std::ostrstream s;
        s << "Line(" << line << ":" << charPositionInLine << ") Error(" << msg << ")";
        throw std::invalid_argument(s.str());
    }
};

int main()
{
    while (std::cin) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);
        
        antlr4::ANTLRInputStream inputStream(input);
        ExpressionLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        MyParserErrorListener errorListner;

        tokens.fill();
        ExpressionParser parser(&tokens);
        parser.removeErrorListeners();
        parser.addErrorListener(&errorListner);
        try {
            antlr4::tree::ParseTree* tree = parser.main();
            std::cout << tree->toStringTree() << std::endl;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
