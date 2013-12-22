﻿#pragma once

#include "CharStream.h"
#include "misc/Interval.h"
#include <string>

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


                /// <summary>
                /// Vacuum all input from a <seealso cref="Reader"/>/<seealso cref="InputStream"/> and then treat it
                /// like a {@code char[]} buffer. Can also pass in a <seealso cref="String"/> or
                /// {@code char[]} to use.
                /// <p/>
                /// If you need encoding, pass in stream/reader with correct encoding.
                /// </summary>
                class ANTLRInputStream : public CharStream {
                public:
                    static const int READ_BUFFER_SIZE = 1024;
                       static const int INITIAL_BUFFER_SIZE = 1024;

                    /// <summary>
                    /// The data being scanned </summary>
                protected:
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: protected char[] data;
                    wchar_t *data;

                    /// <summary>
                    /// How many characters are actually in the buffer </summary>
                    int n;

                    /// <summary>
                    /// 0..n-1 index into string of next char </summary>
                    int p;

                    /// <summary>
                    /// What is name or source of this char stream? </summary>
                public:
                    std::wstring name;

                    ANTLRInputStream();

                    /// <summary>
                    /// Copy data in string to a local char array </summary>
                    ANTLRInputStream(const std::wstring &input);

                    /// <summary>
                    /// This is the preferred constructor for strings as no data is copied </summary>
                    ANTLRInputStream(wchar_t data[], int numberOfActualCharsInArray);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                    ANTLRInputStream(Reader *r) throw(IOException); //this(r, INITIAL_BUFFER_SIZE, READ_BUFFER_SIZE);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                    ANTLRInputStream(Reader *r, int initialSize) throw(IOException); //this(r, initialSize, READ_BUFFER_SIZE);

                    ANTLRInputStream(Reader *r, int initialSize, int readChunkSize) throw(IOException);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                    ANTLRInputStream(InputStream *input) throw(IOException); //this(new InputStreamReader(input), INITIAL_BUFFER_SIZE);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                    ANTLRInputStream(InputStream *input, int initialSize) throw(IOException); //this(new InputStreamReader(input), initialSize);

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
                    ANTLRInputStream(InputStream *input, int initialSize, int readChunkSize) throw(IOException); //this(new InputStreamReader(input), initialSize, readChunkSize);

                    virtual void load(Reader *r, int size, int readChunkSize) throw(IOException);

                    /// <summary>
                    /// Reset the stream so that it's in the same state it was
                    ///  when the object was created *except* the data array is not
                    ///  touched.
                    /// </summary>
                    virtual void reset();

                    virtual void consume() override;

                    virtual int LA(int i) override;

                    virtual int LT(int i);

                    /// <summary>
                    /// Return the current input symbol index 0..n where n indicates the
                    ///  last symbol has been read.  The index is the index of char to
                    ///  be returned from LA(1).
                    /// </summary>
                    virtual int index() override;

                    virtual int size() override;

                    /// <summary>
                    /// mark/release do nothing; we have entire buffer </summary>
                    virtual int mark() override;

                    virtual void release(int marker) override;

                    /// <summary>
                    /// consume() ahead until p==index; can't just set p=index as we must
                    ///  update line and charPositionInLine. If we seek backwards, just set p
                    /// </summary>
                    virtual void seek(int index) override;

                    virtual std::wstring getText(Interval *interval) override;

                    virtual std::wstring getSourceName() override;

                    virtual std::wstring toString() override;

                private:
                    void InitializeInstanceFields();
                };

            }
        }
    }
}
