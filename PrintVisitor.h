#pragma once

#include <cstdlib>
#include "generated/ExpressionVisitor.h"

class PrintVisitor : public ExpressionVisitor
{
public:
    antlrcpp::Any visitMain(ExpressionParser::MainContext *ctx)
    {
        return visit(ctx->expr());
    }

    antlrcpp::Any visitLiteralExpr(ExpressionParser::LiteralExprContext *ctx)
    {
        return ctx->LITERAL()->getText();
    }

    antlrcpp::Any visitAdditiveExpr(ExpressionParser::AdditiveExprContext *ctx)
    {
        const auto left = visit(ctx->expr(0)).as<std::string>();
        const auto right = visit(ctx->expr(1)).as<std::string>();
        return left + ctx->op->getText() + right;
    }

    antlrcpp::Any visitMultiplicativeExpr(ExpressionParser::MultiplicativeExprContext *ctx)
    {
        const auto left = visit(ctx->expr(0)).as<std::string>();
        const auto right = visit(ctx->expr(1)).as<std::string>();
        return left + ctx->op->getText() + right;
    }

    antlrcpp::Any visitBracketedExpr(ExpressionParser::BracketedExprContext *ctx)
    {
        return std::string("(") + visit(ctx->expr()).as<std::string>() + std::string(")");
    }
};
