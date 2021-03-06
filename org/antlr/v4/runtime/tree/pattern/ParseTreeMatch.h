﻿#pragma once


#include "MultiMap.h"
#include <string>
#include <vector>

#include "Declarations.h"

/*
 * [The "BSD license"]
 * Copyright (c) 2013 Terence Parr
 * Copyright (c) 2013 Sam Harwell
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

namespace org {
    namespace antlr {
        namespace v4 {
            namespace runtime {
                namespace tree {
                    namespace pattern {
                        /// <summary>
                        /// Represents the result of matching a <seealso cref="ParseTree"/> against a tree pattern.
                        /// </summary>
                        class ParseTreeMatch {
                            /// <summary>
                            /// This is the backing field for <seealso cref="#getTree()"/>.
                            /// </summary>
                        private:
                            ParseTree *const tree;

                            /// <summary>
                            /// This is the backing field for <seealso cref="#getPattern()"/>.
                            /// </summary>
                            ParseTreePattern *const pattern;

                            /// <summary>
                            /// This is the backing field for <seealso cref="#getLabels()"/>.
                            /// </summary>
                            misc::MultiMap<std::wstring, ParseTree*> *const labels;

                            /// <summary>
                            /// This is the backing field for <seealso cref="#getMismatchedNode()"/>.
                            /// </summary>
                            ParseTree *const mismatchedNode;

                            /// <summary>
                            /// Constructs a new instance of <seealso cref="ParseTreeMatch"/> from the specified
                            /// parse tree and pattern.
                            /// </summary>
                            /// <param name="tree"> The parse tree to match against the pattern. </param>
                            /// <param name="pattern"> The parse tree pattern. </param>
                            /// <param name="labels"> A mapping from label names to collections of
                            /// <seealso cref="ParseTree"/> objects located by the tree pattern matching process. </param>
                            /// <param name="mismatchedNode"> The first node which failed to match the tree
                            /// pattern during the matching process.
                            /// </param>
                            /// <exception cref="IllegalArgumentException"> if {@code tree} is {@code null} </exception>
                            /// <exception cref="IllegalArgumentException"> if {@code pattern} is {@code null} </exception>
                            /// <exception cref="IllegalArgumentException"> if {@code labels} is {@code null} </exception>
                        public:
                            ParseTreeMatch(ParseTree *tree, ParseTreePattern *pattern, misc::MultiMap<std::wstring, ParseTree*> *labels, ParseTree *mismatchedNode);

                            /// <summary>
                            /// Get the last node associated with a specific {@code label}.
                            /// <p/>
                            /// For example, for pattern {@code <id:ID>}, {@code get("id")} returns the
                            /// node matched for that {@code ID}. If more than one node
                            /// matched the specified label, only the last is returned. If there is
                            /// no node associated with the label, this returns {@code null}.
                            /// <p/>
                            /// Pattern tags like {@code <ID>} and {@code <expr>} without labels are
                            /// considered to be labeled with {@code ID} and {@code expr}, respectively.
                            /// </summary>
                            /// <param name="label"> The label to check.
                            /// </param>
                            /// <returns> The last <seealso cref="ParseTree"/> to match a tag with the specified
                            /// label, or {@code null} if no parse tree matched a tag with the label. </returns>
                            virtual ParseTree *get(const std::wstring &label);

                            /// <summary>
                            /// Return all nodes matching a rule or token tag with the specified label.
                            /// <p/>
                            /// If the {@code label} is the name of a parser rule or token in the
                            /// grammar, the resulting list will contain both the parse trees matching
                            /// rule or tags explicitly labeled with the label and the complete set of
                            /// parse trees matching the labeled and unlabeled tags in the pattern for
                            /// the parser rule or token. For example, if {@code label} is {@code "foo"},
                            /// the result will contain <em>all</em> of the following.
                            /// 
                            /// <ul>
                            /// <li>Parse tree nodes matching tags of the form {@code <foo:anyRuleName>} and
                            /// {@code <foo:AnyTokenName>}.</li>
                            /// <li>Parse tree nodes matching tags of the form {@code <anyLabel:foo>}.</li>
                            /// <li>Parse tree nodes matching tags of the form {@code <foo>}.</li>
                            /// </ul>
                            /// </summary>
                            /// <param name="label"> The label.
                            /// </param>
                            /// <returns> A collection of all <seealso cref="ParseTree"/> nodes matching tags with
                            /// the specified {@code label}. If no nodes matched the label, an empty list
                            /// is returned. </returns>
                            virtual std::vector<ParseTree*> getAll(const std::wstring &label);

                            /// <summary>
                            /// Return a mapping from label &rarr; [list of nodes].
                            /// <p/>
                            /// The map includes special entries corresponding to the names of rules and
                            /// tokens referenced in tags in the original pattern. For additional
                            /// information, see the description of <seealso cref="#getAll(String)"/>.
                            /// </summary>
                            /// <returns> A mapping from labels to parse tree nodes. If the parse tree
                            /// pattern did not contain any rule or token tags, this map will be empty. </returns>
                            virtual misc::MultiMap<std::wstring, ParseTree*> *getLabels();

                            /// <summary>
                            /// Get the node at which we first detected a mismatch.
                            /// </summary>
                            /// <returns> the node at which we first detected a mismatch, or {@code null}
                            /// if the match was successful. </returns>
                            virtual ParseTree *getMismatchedNode();

                            /// <summary>
                            /// Gets a value indicating whether the match operation succeeded.
                            /// </summary>
                            /// <returns> {@code true} if the match operation succeeded; otherwise,
                            /// {@code false}. </returns>
                            virtual bool succeeded();

                            /// <summary>
                            /// Get the tree pattern we are matching against.
                            /// </summary>
                            /// <returns> The tree pattern we are matching against. </returns>
                            virtual ParseTreePattern *getPattern();

                            /// <summary>
                            /// Get the parse tree we are trying to match to a pattern.
                            /// </summary>
                            /// <returns> The <seealso cref="ParseTree"/> we are trying to match to a pattern. </returns>
                            virtual ParseTree *getTree();

                            /// <summary>
                            /// {@inheritDoc}
                            /// </summary>
                            virtual std::wstring toString();
                        };

                    }
                }
            }
        }
    }
}
