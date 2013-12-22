﻿#pragma once

#include "RuleContext.h"
#include "tree/ParseTree.h"
#include "Token.h"
#include "RecognitionException.h"
#include "tree/ParseTreeListener.h"
#include "tree/TerminalNode.h"
#include "tree/ErrorNode.h"
#include "misc/Interval.h"
#include "Parser.h"
#include <string>
#include <vector>
#include <algorithm>

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

                using org::antlr::v4::runtime::misc::Interval;
                using org::antlr::v4::runtime::misc::Nullable;
                using org::antlr::v4::runtime::tree::ErrorNode;
                using org::antlr::v4::runtime::tree::ErrorNodeImpl;
                using org::antlr::v4::runtime::tree::ParseTree;
                using org::antlr::v4::runtime::tree::ParseTreeListener;
                using org::antlr::v4::runtime::tree::TerminalNode;
                using org::antlr::v4::runtime::tree::TerminalNodeImpl;
                using org::antlr::v4::runtime::tree::pattern::RuleTagToken;


                /// <summary>
                /// A rule invocation record for parsing.
                /// 
                ///  Contains all of the information about the current rule not stored in the
                ///  RuleContext. It handles parse tree children list, Any ATN state
                ///  tracing, and the default values available for rule indications:
                ///  start, stop, rule index, current alt number, current
                ///  ATN state.
                /// 
                ///  Subclasses made for each rule and grammar track the parameters,
                ///  return values, locals, and labels specific to that rule. These
                ///  are the objects that are returned from rules.
                /// 
                ///  Note text is not an actual field of a rule return value; it is computed
                ///  from start and stop using the input stream's toString() method.  I
                ///  could add a ctor to this so that we can pass in and store the input
                ///  stream, but I'm not sure we want to do that.  It would seem to be undefined
                ///  to get the .text property anyway if the rule matches tokens from multiple
                ///  input streams.
                /// 
                ///  I do not use getters for fields of objects that are used simply to
                ///  group values such as this aggregate.  The getters/setters are there to
                ///  satisfy the superclass interface.
                /// </summary>
                class ParserRuleContext : public RuleContext {
                    /// <summary>
                    /// If we are debugging or building a parse tree for a visitor,
                    ///  we need to track all of the tokens and rule invocations associated
                    ///  with this rule's context. This is empty for parsing w/o tree constr.
                    ///  operation because we don't the need to track the details about
                    ///  how we parse this rule.
                    /// </summary>
                public:
                    std::vector<ParseTree*> children;

                    /// <summary>
                    /// For debugging/tracing purposes, we want to track all of the nodes in
                    ///  the ATN traversed by the parser for a particular rule.
                    ///  This list indicates the sequence of ATN nodes used to match
                    ///  the elements of the children list. This list does not include
                    ///  ATN nodes and other rules used to match rule invocations. It
                    ///  traces the rule invocation node itself but nothing inside that
                    ///  other rule's ATN submachine.
                    /// 
                    ///  There is NOT a one-to-one correspondence between the children and
                    ///  states list. There are typically many nodes in the ATN traversed
                    ///  for each element in the children list. For example, for a rule
                    ///  invocation there is the invoking state and the following state.
                    /// 
                    ///  The parser setState() method updates field s and adds it to this list
                    ///  if we are debugging/tracing.
                    ///    
                    ///  This does not trace states visited during prediction.
                    /// </summary>
                //	public List<Integer> states;

                    Token *start, *stop;

                    /// <summary>
                    /// The exception that forced this rule to return. If the rule successfully
                    /// completed, this is {@code null}.
                    /// </summary>
                    RecognitionException *exception;

                    ParserRuleContext();

                    /// <summary>
                    /// COPY a ctx (I'm deliberately not using copy constructor) </summary>
                    virtual void copyFrom(ParserRuleContext *ctx);

                    ParserRuleContext(ParserRuleContext *parent, int invokingStateNumber);

                    // Double dispatch methods for listeners

                    virtual void enterRule(ParseTreeListener *listener);
                    virtual void exitRule(ParseTreeListener *listener);

                    /// <summary>
                    /// Does not set parent link; other add methods do that </summary>
                    virtual TerminalNode *addChild(TerminalNode *t);

                    virtual RuleContext *addChild(RuleContext *ruleInvocation);

                    /// <summary>
                    /// Used by enterOuterAlt to toss out a RuleContext previously added as
                    ///  we entered a rule. If we have # label, we will need to remove
                    ///  generic ruleContext object.
                    /// </summary>
                    virtual void removeLastChild();

                //	public void trace(int s) {
                //		if ( states==null ) states = new ArrayList<Integer>();
                //		states.add(s);
                //	}

                    virtual TerminalNode *addChild(Token *matchedToken);

                    virtual ErrorNode *addErrorNode(Token *badToken);

                    virtual ParserRuleContext *getParent() override;

                    virtual ParseTree *getChild(int i) override;

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
                    template<typename T> where T : org.antlr.v4.runtime.tree.ParseTree
                    virtual T getChild(Class *ctxType, int i);

                    virtual TerminalNode *getToken(int ttype, int i);

                    virtual std::vector<TerminalNode*> getTokens(int ttype);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
                    template<typename T> where T : ParserRuleContext
                    virtual T getRuleContext(Class *ctxType, int i);

//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
                    template<typename T> where T : ParserRuleContext
                    virtual std::vector<T> getRuleContexts(Class *ctxType);

                    virtual int getChildCount() override;
                    virtual Interval *getSourceInterval() override;

                    virtual Token *getStart();
                    virtual Token *getStop();

                    /// <summary>
                    /// Used for rule context info debugging during parse-time, not so much for ATN debugging </summary>
                    virtual std::wstring toInfoString(Parser *recognizer);
                };

            }
        }
    }
}