#include "pch.h"
#include "CppUnitTest.h"
#include "../PR-10.3/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int spec = 0;
			int k = 0;
			int N = 1;
			int i = 0;
			int fiz = 3;
			int ikurs = 3;
			Note* p = new Note[N];
			p[i].prizvim = "Кан";
			p[i].nomer = 3;
			p[i].day = 4;
			p[i].month = 5;
			p[i].year = 5;
			int n = BinSearch(p, N, fiz);
			Assert::AreEqual(n, 0);
		}
	};
}
