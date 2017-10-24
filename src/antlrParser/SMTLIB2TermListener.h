/*
 * SMTLIB2TermListener.h
 *
 *  Created on: 23 Oct 2017
 *      Author: osboxes
 */

#ifndef SMTLIB2TERMLISTENER_H_
#define SMTLIB2TERMLISTENER_H_

#include <vector>
#include "antlr4-runtime.h"
#include "SMTLIB2Lexer.h"
#include "SMTLIB2Parser.h"
#include "SMTLIB2ParserBaseVisitor.h"
#include "SMTLIB2ParserBaseListener.h"
using namespace antlrcpptest;
using namespace antlr4;

class SMTLIB2TermListener : public SMTLIB2ParserBaseListener {
    public:
	std::vector<std::vector<std::pair<std::string, int>>> smtTokens;

    void enterTerm(SMTLIB2Parser::TermContext *ctx) override {
    	/* "\nvisit TermContext\n" */
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



#endif /* SMTLIB2TERMLISTENER_H_ */
