#include <iostream>
#include <strstream>
#include <string>
#include <antlr4-runtime.h>

#include "generated/ExpressionLexer.h"
#include "generated/ExpressionParser.h"
#include "generated/ExpressionVisitor.h"

class MyExpressionVisitor : public ExpressionVisitor
{
public:
    antlrcpp::Any visitMain(ExpressionParser::MainContext *ctx)
    {
        return visit(ctx->expr());
    }

    antlrcpp::Any visitLiteralExpr(ExpressionParser::LiteralExprContext *ctx)
    {
        return std::atof(ctx->LITERAL()->getText().c_str());
    }

    antlrcpp::Any visitAdditiveExpr(ExpressionParser::AdditiveExprContext *ctx)
    {
        const auto left = visit(ctx->expr(0)).as<double>();
        const auto right = visit(ctx->expr(1)).as<double>();

        if (ctx->op->getType() == ExpressionParser::ADD) {
            return left + right;
        }

        return left - right;
    }

    antlrcpp::Any visitMultiplicativeExpr(ExpressionParser::MultiplicativeExprContext *ctx)
    {
        const auto left = visit(ctx->expr(0)).as<double>();
        const auto right = visit(ctx->expr(1)).as<double>();

        if (ctx->op->getType() == ExpressionParser::MUL) {
            return left * right;
        }

        return left / right;
    }

    antlrcpp::Any visitBracketedExpr(ExpressionParser::BracketedExprContext *ctx)
    {
        return visit(ctx->expr());
    }
};

class MyParserErrorListener: public antlr4::BaseErrorListener
{
    void syntaxError(
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
        if (!std::getline(std::cin, input)) {
            break;
        }
        
        antlr4::ANTLRInputStream inputStream(input);
        ExpressionLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);
        MyParserErrorListener errorListner;

        tokens.fill();
        ExpressionParser parser(&tokens);
        parser.removeErrorListeners();
        parser.addErrorListener(&errorListner);

        try {
            ExpressionParser::MainContext* tree = parser.main();
            MyExpressionVisitor visitor;
            std::cout << visitor.visitMain(tree).as<double>() << std::endl;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << std::endl;

    return 0;
}
