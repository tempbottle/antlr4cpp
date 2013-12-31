﻿#pragma once

#include "ATNType.h"
#include <string>
#include <vector>
#include <map>

#include "Declarations.h"


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
                namespace atn {

                    class ATN {
                    public:
                        static const int INVALID_ALT_NUMBER = 0;

                        const std::vector<ATNState*> states;

                        /// <summary>
                        /// Each subrule/rule is a decision point and we must track them so we
                        ///  can go back later and build DFA predictors for them.  This includes
                        ///  all the rules, subrules, optional blocks, ()+, ()* etc...
                        /// </summary>
                        const std::vector<DecisionState*> decisionToState;

                        /// <summary>
                        /// Maps from rule index to starting state number.
                        /// </summary>
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: public RuleStartState[] ruleToStartState;
                        RuleStartState *ruleToStartState;

                        /// <summary>
                        /// Maps from rule index to stop state number.
                        /// </summary>
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: public RuleStopState[] ruleToStopState;
                        RuleStopState *ruleToStopState;

                        std::map<std::wstring, TokensStartState*> *const modeNameToStartState;
                        
                        /// <summary>
                        /// The type of the ATN.
                        /// </summary>
                        const ATNType grammarType;

                        /// <summary>
                        /// The maximum value for any symbol recognized by a transition in the ATN.
                        /// </summary>
                        const int maxTokenType;

                        /// <summary>
                        /// For lexer ATNs, this maps the rule index to the resulting token type.
                        /// For parser ATNs, this maps the rule index to the generated bypass token
                        /// type if the
                        /// <seealso cref="ATNDeserializationOptions#isGenerateRuleBypassTransitions"/>
                        /// deserialization option was specified; otherwise, this is {@code null}.
                        /// </summary>
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: public int[] ruleToTokenType;
                        int *ruleToTokenType;

                        /// <summary>
                        /// For lexer ATNs, this maps the rule index to the action which should be
                        /// executed following a match.
                        /// <p/>
                        /// This is {@code null} for parser ATNs.
                        /// </summary>
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: public int[] ruleToActionIndex;
                        int *ruleToActionIndex;

                        const std::vector<TokensStartState*> modeToStartState;

                        /// <summary>
                        /// Used for runtime deserialization of ATNs from strings </summary>
                        ATN(ATNType grammarType, int maxTokenType);

                        /// <summary>
                        /// Compute the set of valid tokens that can occur starting in state {@code s}.
                        ///  If {@code ctx} is null, the set of tokens will not include what can follow
                        ///  the rule surrounding {@code s}. In other words, the set will be
                        ///  restricted to tokens reachable staying within {@code s}'s rule.
                        /// </summary>
                        virtual misc::IntervalSet *nextTokens(ATNState *s, RuleContext *ctx);

                        /// <summary>
                        /// Compute the set of valid tokens that can occur starting in {@code s} and
                        /// staying in same rule. <seealso cref="Token#EPSILON"/> is in set if we reach end of
                        /// rule.
                        /// </summary>
                        virtual misc::IntervalSet *nextTokens(ATNState *s);

                        virtual void addState(ATNState *state);

                        virtual void removeState(ATNState *state);

                        virtual int defineDecisionState(DecisionState *s);

                        virtual DecisionState *getDecisionState(int decision);

                        virtual int getNumberOfDecisions();

                        /// <summary>
                        /// Computes the set of input symbols which could follow ATN state number
                        /// {@code stateNumber} in the specified full {@code context}. This method
                        /// considers the complete parser context, but does not evaluate semantic
                        /// predicates (i.e. all predicates encountered during the calculation are
                        /// assumed true). If a path in the ATN exists from the starting state to the
                        /// <seealso cref="RuleStopState"/> of the outermost context without matching any
                        /// symbols, <seealso cref="Token#EOF"/> is added to the returned set.
                        /// <p/>
                        /// If {@code context} is {@code null}, it is treated as
                        /// <seealso cref="ParserRuleContext#EMPTY"/>.
                        /// </summary>
                        /// <param name="stateNumber"> the ATN state number </param>
                        /// <param name="context"> the full parse context </param>
                        /// <returns> The set of potentially valid input symbols which could follow the
                        /// specified state in the specified context. </returns>
                        /// <exception cref="IllegalArgumentException"> if the ATN does not contain a state with
                        /// number {@code stateNumber} </exception>
                        virtual misc::IntervalSet *getExpectedTokens(int stateNumber, RuleContext *context);
                    };

                }
            }
        }
    }
}
