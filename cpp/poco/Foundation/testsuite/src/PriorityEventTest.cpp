//
// PriorityEventTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/PriorityEventTest.cpp#2 $
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


#include "PriorityEventTest.h"
#include "DummyDelegate.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/PriorityDelegate.h"
#include "Poco/PriorityExpire.h"
#include "Poco/Thread.h"
#include "Poco/Exception.h"


using namespace Poco;


#define LARGEINC 100


PriorityEventTest::PriorityEventTest(const std::string& name): CppUnit::TestCase(name)
{
}


PriorityEventTest::~PriorityEventTest()
{
}

void PriorityEventTest::testNoDelegate()
{
	int tmp = 0;
	EventArgs args;

	assert (_count == 0);
	Simple.notify(this, tmp);
	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.notify(this, tmp);
	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimpleNoSender, 0);
	Simple -= priorityDelegate(this, &PriorityEventTest::onSimpleNoSender, 0);
	Simple.notify(this, tmp);
	assert (_count == 0);
	
	ConstSimple += priorityDelegate(this, &PriorityEventTest::onConstSimple, 0);
	ConstSimple -= priorityDelegate(this, &PriorityEventTest::onConstSimple, 0);
	ConstSimple.notify(this, tmp);
	assert (_count == 0);
	
	//Note: passing &args will not work due to &
	EventArgs* pArgs = &args;
	Complex += priorityDelegate(this, &PriorityEventTest::onComplex, 0);
	Complex -= priorityDelegate(this, &PriorityEventTest::onComplex, 0);
	Complex.notify(this, pArgs);
	assert (_count == 0);

	Complex2 += priorityDelegate(this, &PriorityEventTest::onComplex2, 0);
	Complex2 -= priorityDelegate(this, &PriorityEventTest::onComplex2, 0);
	Complex2.notify(this, args);
	assert (_count == 0);

	const EventArgs* pCArgs = &args;
	ConstComplex += priorityDelegate(this, &PriorityEventTest::onConstComplex, 0);
	ConstComplex -= priorityDelegate(this, &PriorityEventTest::onConstComplex, 0);
	ConstComplex.notify(this, pCArgs);
	assert (_count == 0);

	Const2Complex += priorityDelegate(this, &PriorityEventTest::onConst2Complex, 0);
	Const2Complex -= priorityDelegate(this, &PriorityEventTest::onConst2Complex, 0);
	Const2Complex.notify(this, pArgs);
	assert (_count == 0);

	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple, 0);
	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple, 0);
	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple, 1);
	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple2, 2);
	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple3, 3);
	
	Simple.notify(this, tmp);
	assert (_count == 4);
	Simple -= priorityDelegate(PriorityEventTest::onStaticSimple, 0);
}

void PriorityEventTest::testSingleDelegate()
{
	int tmp = 0;
	EventArgs args;

	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	// unregistering with a different priority --> different observer, is ignored
	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 3);
	Simple.notify(this, tmp);
	assert (_count == 1);
	
	ConstSimple += priorityDelegate(this, &PriorityEventTest::onConstSimple, 0);
	ConstSimple -= priorityDelegate(this, &PriorityEventTest::onConstSimple, 3);
	ConstSimple.notify(this, tmp);
	assert (_count == 2);
	
	EventArgs* pArgs = &args;
	Complex += priorityDelegate(this, &PriorityEventTest::onComplex, 0);
	Complex -= priorityDelegate(this, &PriorityEventTest::onComplex, 3);
	Complex.notify(this, pArgs);
	assert (_count == 3);

	Complex2 += priorityDelegate(this, &PriorityEventTest::onComplex2, 0);
	Complex2 -= priorityDelegate(this, &PriorityEventTest::onComplex2, 3);
	Complex2.notify(this, args);
	assert (_count == 4);

	const EventArgs* pCArgs = &args;
	ConstComplex += priorityDelegate(this, &PriorityEventTest::onConstComplex, 0);
	ConstComplex -= priorityDelegate(this, &PriorityEventTest::onConstComplex, 3);
	ConstComplex.notify(this, pCArgs);
	assert (_count == 5);

	Const2Complex += priorityDelegate(this, &PriorityEventTest::onConst2Complex, 0);
	Const2Complex -= priorityDelegate(this, &PriorityEventTest::onConst2Complex, 3);
	Const2Complex.notify(this, pArgs);
	assert (_count == 6);
	// check if 2nd notify also works
	Const2Complex.notify(this, pArgs);
	assert (_count == 7);
	
}

void PriorityEventTest::testDuplicateRegister()
{
	int tmp = 0;
	
	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.notify(this, tmp);
	assert (_count == 2);
	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.notify(this, tmp);
	assert (_count == 3);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimpleOther, 1);
	Simple.notify(this, tmp);
	assert (_count == 4 + LARGEINC);
	Simple -= priorityDelegate(this, &PriorityEventTest::onSimpleOther, 1);
	Simple.notify(this, tmp);
	assert (_count == 5 + LARGEINC);
}

void PriorityEventTest::testDuplicateUnregister()
{
	// duplicate unregister shouldn't give an error,
	int tmp = 0;
	
	assert (_count == 0);

	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 0); // should work
	Simple.notify(this, tmp);
	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.notify(this, tmp);
	assert (_count == 1);

	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.notify(this, tmp);
	assert (_count == 1);

	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.notify(this, tmp);
	assert (_count == 1);
}


void PriorityEventTest::testDisabling()
{
	int tmp = 0;
	
	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.disable();
	Simple.notify(this, tmp);
	assert (_count == 0);
	Simple.enable();
	Simple.notify(this, tmp);
	assert (_count == 1);

	// unregister should also work with disabled event
	Simple.disable();
	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 0);
	Simple.enable();
	Simple.notify(this, tmp);
	assert (_count == 1);
}

void PriorityEventTest::testPriorityOrder()
{
	DummyDelegate o1;
	DummyDelegate o2;

	assert (_count == 0);

	Simple += PriorityDelegate<DummyDelegate, int>(&o2, &DummyDelegate::onSimple2, 1);
	Simple += PriorityDelegate<DummyDelegate, int>(&o1, &DummyDelegate::onSimple, 0);

	int tmp = 0;
	Simple.notify(this, tmp);
	assert (tmp == 2);

	Simple -= PriorityDelegate<DummyDelegate, int>(&o1, &DummyDelegate::onSimple, 0);
	Simple -= PriorityDelegate<DummyDelegate, int>(&o2, &DummyDelegate::onSimple2, 1);
	
	// now try with the wrong order
	Simple += PriorityDelegate<DummyDelegate, int>(&o2, &DummyDelegate::onSimple2, 0);
	Simple += PriorityDelegate<DummyDelegate, int>(&o1, &DummyDelegate::onSimple, 1);

	try
	{
		tmp = 0;
		Simple.notify(this, tmp);
		failmsg ("Notify should not work");
	}
	catch (Poco::InvalidArgumentException&)
	{
	}

	Simple -= PriorityDelegate<DummyDelegate, int>(&o2, &DummyDelegate::onSimple2, 0);
	Simple -= PriorityDelegate<DummyDelegate, int>(&o1, &DummyDelegate::onSimple, 1);
}

void PriorityEventTest::testPriorityOrderExpire()
{
	// expire must not break order!
	DummyDelegate o1;
	DummyDelegate o2;

	assert (_count == 0);

	Simple += priorityDelegate(&o2, &DummyDelegate::onSimple2, 1, 500000);
	Simple += priorityDelegate(&o1, &DummyDelegate::onSimple, 0, 500000);
	int tmp = 0;
	Simple.notify(this, tmp);
	assert (tmp == 2);

	// both ways of unregistering should work
	Simple -= priorityDelegate(&o1, &DummyDelegate::onSimple, 0, 500000);
	Simple -= priorityDelegate(&o2, &DummyDelegate::onSimple2, 1);
	Simple.notify(this, tmp);
	assert (tmp == 2);
	
	// now start mixing of expire and non expire
	tmp = 0;
	Simple += priorityDelegate(&o2, &DummyDelegate::onSimple2, 1, 500000);
	Simple += priorityDelegate(&o1, &DummyDelegate::onSimple, 0);
	
	Simple.notify(this, tmp);
	assert (tmp == 2);

	Simple -= priorityDelegate(&o2, &DummyDelegate::onSimple2, 1);
	// it is not forbidden to unregister a non expiring event with an expire decorator (it is just stupid ;-))
	Simple -= priorityDelegate(&o1, &DummyDelegate::onSimple, 0, 500000);
	Simple.notify(this, tmp);
	assert (tmp == 2);

	// now try with the wrong order
	Simple += priorityDelegate(&o2, &DummyDelegate::onSimple2, 0, 500000);
	Simple += priorityDelegate(&o1, &DummyDelegate::onSimple, 1);

	try
	{
		tmp = 0;
		Simple.notify(this, tmp);
		failmsg ("Notify should not work");
	}
	catch (Poco::InvalidArgumentException&)
	{
	}

	Simple -= priorityDelegate(&o2, &DummyDelegate::onSimple2, 0, 500000);
	Simple -= priorityDelegate(&o1, &DummyDelegate::onSimple, 1);

}

void PriorityEventTest::testExpire()
{
	int tmp = 0;
	
	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 1, 500);
	Simple.notify(this, tmp);
	assert (_count == 1);
	Poco::Thread::sleep(700);
	Simple.notify(this, tmp);
	assert (_count == 1);
	Simple -= priorityDelegate(this, &PriorityEventTest::onSimple, 1, 500);

	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple, 1, 500);
	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple2, 1, 500);
	Simple += priorityDelegate(&PriorityEventTest::onStaticSimple3, 1, 500);
	Simple.notify(this, tmp);
	assert (_count == 3);
	Poco::Thread::sleep(700);
	Simple.notify(this, tmp);
	assert (_count == 3);
}


void PriorityEventTest::testExpireReRegister()
{
	int tmp = 0;
	
	assert (_count == 0);

	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 1, 500);
	Simple.notify(this, tmp);
	assert (_count == 1);
	Poco::Thread::sleep(200);
	Simple.notify(this, tmp);
	assert (_count == 2);
	// renew registration
	Simple += priorityDelegate(this, &PriorityEventTest::onSimple, 1, 600);
	Poco::Thread::sleep(400);
	Simple.notify(this, tmp);
	assert (_count == 3);
	Poco::Thread::sleep(300);
	Simple.notify(this, tmp);
	assert (_count == 3);
}


void PriorityEventTest::testReturnParams()
{
	DummyDelegate o1;
	Simple += priorityDelegate(&o1, &DummyDelegate::onSimple, 0);

	int tmp = 0;
	Simple.notify(this, tmp);
	assert (tmp == 1);
}

void PriorityEventTest::testOverwriteDelegate()
{
	DummyDelegate o1;
	Simple += priorityDelegate(&o1, &DummyDelegate::onSimple, 0);
	Simple += priorityDelegate(&o1, &DummyDelegate::onSimple2, 0);

	int tmp = 0; // onsimple requires 0 as input
	Simple.notify(this, tmp);
	assert (tmp == 2);
}

void PriorityEventTest::testAsyncNotify()
{
	Poco::PriorityEvent<int >* pSimple= new Poco::PriorityEvent<int>();
	(*pSimple) += priorityDelegate(this, &PriorityEventTest::onAsync, 0);
	assert (_count == 0);
	int tmp = 0;
	Poco::ActiveResult<int>retArg = pSimple->notifyAsync(this, tmp);
	delete pSimple; // must work even when the event got deleted!
	pSimple = NULL;
	assert (_count == 0);
	retArg.wait();
	assert (retArg.data() == tmp);
	assert (_count == LARGEINC);
	
}


void PriorityEventTest::onStaticSimple(const void* pSender, int& i)
{
	PriorityEventTest* p = const_cast<PriorityEventTest*>(reinterpret_cast<const PriorityEventTest*>(pSender));
	p->_count++;
}


void PriorityEventTest::onStaticSimple2(void* pSender, int& i)
{
	PriorityEventTest* p = reinterpret_cast<PriorityEventTest*>(pSender);
	p->_count++;
}


void PriorityEventTest::onStaticSimple3(int& i)
{
}


void PriorityEventTest::onSimpleNoSender(int& i)
{
	_count++;
}


void PriorityEventTest::onSimple(const void* pSender, int& i)
{
	_count++;
}

void PriorityEventTest::onSimpleOther(const void* pSender, int& i)
{
	_count += LARGEINC ;
}

void PriorityEventTest::onConstSimple(const void* pSender, const int& i)
{
	_count++;
}

void PriorityEventTest::onComplex(const void* pSender, Poco::EventArgs* & i)
{
	_count++;
}

void PriorityEventTest::onComplex2(const void* pSender, Poco::EventArgs & i)
{
	_count++;
}

void PriorityEventTest::onConstComplex(const void* pSender, const Poco::EventArgs*& i)
{
	_count++;
}

void PriorityEventTest::onConst2Complex(const void* pSender, const Poco::EventArgs * const & i)
{
	_count++;
}

void PriorityEventTest::onAsync(const void* pSender, int& i)
{
	Poco::Thread::sleep(700);
	_count += LARGEINC ;
}

int PriorityEventTest::getCount() const
{
	return _count;
}

void PriorityEventTest::setUp()
{
	_count = 0;
	// must clear events, otherwise repeating test executions will fail
	// because tests are only created once, only setup is called before 
	// each test run
	Simple.clear();
	ConstSimple.clear();
	Complex.clear();
	Complex2.clear();
	ConstComplex.clear();
	Const2Complex.clear();
}


void PriorityEventTest::tearDown()
{
}


CppUnit::Test* PriorityEventTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("PriorityEventTest");

	CppUnit_addTest(pSuite, PriorityEventTest, testNoDelegate);
	CppUnit_addTest(pSuite, PriorityEventTest, testSingleDelegate);
	CppUnit_addTest(pSuite, PriorityEventTest, testReturnParams);
	CppUnit_addTest(pSuite, PriorityEventTest, testDuplicateRegister);
	CppUnit_addTest(pSuite, PriorityEventTest, testDuplicateUnregister);
	CppUnit_addTest(pSuite, PriorityEventTest, testDisabling);
	CppUnit_addTest(pSuite, PriorityEventTest, testPriorityOrder);
	CppUnit_addTest(pSuite, PriorityEventTest, testPriorityOrderExpire);
	CppUnit_addTest(pSuite, PriorityEventTest, testExpire);
	CppUnit_addTest(pSuite, PriorityEventTest, testExpireReRegister);
	CppUnit_addTest(pSuite, PriorityEventTest, testOverwriteDelegate);
	CppUnit_addTest(pSuite, PriorityEventTest, testAsyncNotify);
	return pSuite;
}
