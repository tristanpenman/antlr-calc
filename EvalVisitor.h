#pragma once

#include <cstdlib>
#include "generated/ExpressionVisitor.h"

class EvalVisitor : public ExpressionVisitor
{
public:
    antlrcpp::Any visitMain(ExpressionParser::MainContext *ctx)
    {
        return visit(ctx->expr());
    }

    antlrcpp::Any visitLiteralExpr(ExpressionParser::LiteralExprContext *ctx)
    {
        // The LiteralExprContext type includes a function called LITERAL (based on the name of
        // the terminal in the grammar) that we can use to access the string associated with
        // that token
        return std::atof(ctx->LITERAL()->getText().c_str());
    }

    antlrcpp::Any visitAdditiveExpr(ExpressionParser::AdditiveExprContext *ctx)
    {
        // Evaluate the left sub-expression and cast the result to a double
        const auto left = visit(ctx->expr(0)).as<double>();

        // Evaluate the right sub-expression and cast the result to a double
        const auto right = visit(ctx->expr(1)).as<double>();

        // Add or substract, depending on which token was seen
        if (ctx->op->getType() == ExpressionParser::ADD) {
            return left + right;
        } else {
            return left - right;
        }
    }

    antlrcpp::Any visitMultiplicativeExpr(ExpressionParser::MultiplicativeExprContext *ctx)
    {
        // Evaluate the left sub-expression and cast the result to a double
        const auto left = visit(ctx->expr(0)).as<double>();

        // Evaluate the right sub-expression and cast the result to a double
        const auto right = visit(ctx->expr(1)).as<double>();

        // Multiply or divide, depending on which token was seen
        if (ctx->op->getType() == ExpressionParser::MUL) {
            return left * right;
        } else {
            return left / right;
        }
    }

    antlrcpp::Any visitBracketedExpr(ExpressionParser::BracketedExprContext *ctx)
    {
        return visit(ctx->expr());
    }
};