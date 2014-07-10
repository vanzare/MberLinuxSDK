//
// TextTestSuite.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/TextTestSuite.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "TextTestSuite.h"
#include "TextIteratorTest.h"
#include "TextBufferIteratorTest.h"
#include "TextConverterTest.h"
#include "StreamConverterTest.h"
#include "TextEncodingTest.h"
#include "UTF8StringTest.h"
#ifndef POCO_NO_WSTRING
#include "UnicodeConverterTest.h"
#endif

CppUnit::Test* TextTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TextTestSuite");

	pSuite->addTest(TextIteratorTest::suite());
	pSuite->addTest(TextBufferIteratorTest::suite());
	pSuite->addTest(TextConverterTest::suite());
	pSuite->addTest(StreamConverterTest::suite());
	pSuite->addTest(TextEncodingTest::suite());
	pSuite->addTest(UTF8StringTest::suite());
#ifndef POCO_NO_WSTRING
	pSuite->addTest(UnicodeConverterTest::suite());
#endif

	return pSuite;
}
