﻿#include "ParserRuleContext.h"
#include "TerminalNodeImpl.h"
#include "ErrorNodeImpl.h"
#include "Interval.h"
#include "Parser.h"

#include <typeinfo>

/*
 * [The "BSD license"]
 *  Copyright (c) 2013 Terence Parr
 *  Copyright (c) 2013 Dan McLaughlin
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

namespace org {
    namespace antlr {
        namespace v4 {
            namespace runtime {
                
                ParserRuleContext::ParserRuleContext() {
                }

                void ParserRuleContext::copyFrom(ParserRuleContext *ctx) {
                    // from RuleContext
                    this->parent = ctx->parent;
                    this->invokingState = ctx->invokingState;

                    this->start = ctx->start;
                    this->stop = ctx->stop;
                }

                ParserRuleContext::ParserRuleContext(ParserRuleContext *parent, int invokingStateNumber) : RuleContext(parent, invokingStateNumber) {
                }

                void ParserRuleContext::enterRule(tree::ParseTreeListener *listener) {
                }

                void ParserRuleContext::exitRule(tree::ParseTreeListener *listener) {
                }

                tree::TerminalNode *ParserRuleContext::addChild(tree::TerminalNode *t) {
                    if (children.empty()) {
                        children = std::vector<ParseTree*>();
                    }
                    children.push_back(t);
                    return t;
                }

                RuleContext *ParserRuleContext::addChild(RuleContext *ruleInvocation) {
                    if (children.empty()) {
                        children = std::vector<ParseTree*>();
                    }
                    children.push_back(ruleInvocation);
                    return ruleInvocation;
                }

                void ParserRuleContext::removeLastChild() {
                    if (children.size() > 0) {
                        children.pop_back();
                    }
                }

                tree::TerminalNode *ParserRuleContext::addChild(Token *matchedToken) {
                    tree::TerminalNodeImpl *t = new tree::TerminalNodeImpl(matchedToken);
                    addChild(t);
                    t->parent = this;
                    return t;
                }

                tree::ErrorNode *ParserRuleContext::addErrorNode(Token *badToken) {
                    tree::ErrorNodeImpl *t = new tree::ErrorNodeImpl(badToken);
                    addChild(t);
                    t->parent = this;
                    return t;
                }

                /// <summary>
                /// Override to make type more specific </summary>
                ParserRuleContext *ParserRuleContext::getParent()
                {
                    return static_cast<ParserRuleContext*>(RuleContext::getParent());
                }

                tree::ParseTree *ParserRuleContext::getChild(int i) {
                    return children.size() > 0 && i >= 0 && i < children.size() ? children[i] : nullptr;
                }

                template<typename T>
                T ParserRuleContext::getChild(void *ctxType, int i) {
                    if (children.empty() || i < 0 || i >= children.size()) {
                        return nullptr;
                    }

                    int j = -1; // what element have we found with ctxType?
                    for (auto o : children) {
                        if (typeid(ctxType) == typeid(o)) {
                            j++;
                            if (j == i) {
                                return dynamic_cast<T>(o);
                            }
                        }
                    }
                    return nullptr;
                }

                tree::TerminalNode *ParserRuleContext::getToken(int ttype, int i) {
                    if (children.empty() || i < 0 || i >= children.size()) {
                        return nullptr;
                    }

                    int j = -1; // what token with ttype have we found?
                    for (auto o : children) {
                        if (dynamic_cast<tree::TerminalNode*>(o) != nullptr) {
                            tree::TerminalNode *tnode = static_cast<tree::TerminalNode*>(o);
                            Token *symbol = tnode->getSymbol();
                            if (symbol->getType() == ttype) {
                                j++;
                                if (j == i) {
                                    return tnode;
                                }
                            }
                        }
                    }

                    return nullptr;
                }

                // I think this should be changed to a pointer?
                std::vector<tree::TerminalNode*> ParserRuleContext::getTokens(int ttype) {
                    if (children.empty()) {
                        return std::vector<tree::TerminalNode*>();
                    }

                    std::vector<tree::TerminalNode*> tokens;
                    for (auto o : children) {
                        if (dynamic_cast<tree::TerminalNode*>(o) != nullptr) {
                            tree::TerminalNode *tnode = static_cast<tree::TerminalNode*>(o);
                            Token *symbol = tnode->getSymbol();
                            if (symbol->getType() == ttype) {
                                if (tokens.empty()) {
                                    tokens = std::vector<tree::TerminalNode*>();
                                }
                                tokens.push_back(tnode);
                            }
                        }
                    }

                    if (tokens.empty()) {
                        return std::vector<tree::TerminalNode*>();
                    }

                    return tokens;
                }


                template<typename T>
                T ParserRuleContext::getRuleContext(void *ctxType, int i) {
                    return getChild<T>(ctxType, i);
                }


                template<typename T>
                std::vector<T> ParserRuleContext::getRuleContexts(void *ctxType) {
                    if (children.empty()) {
                        return std::vector<T>();
                    }

                    std::vector<T> contexts;
                    for (auto o : children) {
                        if (typeid(ctxType) == typeid(o)) {
                            if (contexts.empty()) {
                                contexts = std::vector<T>();
                            }

                            contexts.push_back((ParserRuleContext*)(o));
                        }
                    }

                    if (contexts.empty()) {
                        return std::vector<T>();
                    }

                    return contexts;
                }

                int ParserRuleContext::getChildCount() {
                    return (int)children.size() > 0 ? (int)children.size() : 0;
                }

                misc::Interval *ParserRuleContext::getSourceInterval() {
                    if (start == nullptr || stop == nullptr) {
                        return misc::Interval::INVALID;
                    }
                    return misc::Interval::of(start->getTokenIndex(), stop->getTokenIndex());
                }

                Token *ParserRuleContext::getStart() {
                    return start;
                }

                Token *ParserRuleContext::getStop() {
                    return stop;
                }

                std::wstring ParserRuleContext::toInfoString(Parser *recognizer) {
                    std::vector<std::wstring> rules = recognizer->getRuleInvocationStack(this);
                    std::reverse(rules.begin(), rules.end());
#ifdef TODO
                    FIX UP THIS STRING
#endif
                    return std::wstring(L"ParserRuleContext") /*+ rules*/ + std::wstring(L"{") + std::wstring(L"start=") + std::to_wstring(start->getTokenIndex())  + std::wstring(L", stop=") + std::to_wstring(stop->getTokenIndex()) + L'}';
                }
            }
        }
    }
}
