/*
 * SMTLIB26ScriptListener.h
 *
 *  Created on: 23 Oct 2017
 *      Author: osboxes
 */

#ifndef SMTLIB26SCRIPTLISTENER_H_
#define SMTLIB26SCRIPTLISTENER_H_

#include <vector>
#include "antlr4-runtime.h"
#include "SMTLIB26Lexer.h"
#include "SMTLIB26Parser.h"
#include "SMTLIB26ParserBaseVisitor.h"
#include "SMTLIB26ParserBaseListener.h"
using namespace antlrcpptest;
using namespace antlr4;

class SMTLIB26ScriptListener : public SMTLIB26ParserBaseListener {
    public:
	std::vector<std::vector<std::pair<std::string, int>>> smtTokens;

    void enterCommand(SMTLIB26Parser::CommandContext *ctx) override {
    	/* "\nvisit CommandContext\n" */
        std::vector<tree::ParseTree*> children = ctx->children;
        std::vector<std::pair<std::string, int>> lineTokens;
        for (const auto& child : children) {
            visit(child, lineTokens);
        }
        smtTokens.push_back(lineTokens);
    }

    private:
    void visit(tree::ParseTree* node, std::vector<std::pair<std::string, int>> &lineTokens) {
        if (node->children.size() == 0) {
            auto tmp = dynamic_cast<tree::TerminalNodeImpl*>(node);
            lineTokens.push_back(std::make_pair(tmp->toStringTree(), tmp->getSymbol()->getType()));
        }
        else {
            std::vector<tree::ParseTree*> children = node->children;
            for (const auto& child : children) {
                visit(child, lineTokens);
            }
        }
    }
};



#endif /* SMTLIB26SCRIPTLISTENER_H_ */
