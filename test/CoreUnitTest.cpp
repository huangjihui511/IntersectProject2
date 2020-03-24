#include "pch.h"
#include "CppUnitTest.h"
#include "../core/core.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreUnitTest
{
	TEST_CLASS(CoreUnitTest)
	{
	public:
		//普通直线相交
		TEST_METHOD(TestMethod1)
		{
			Core core;
			core.addGeomrtie("L 0 0 1 1");
			core.addGeomrtie("L 0 1 2 1");
			core.intersect();

			set<Point>::iterator it = core.intersections.begin();
			Assert::AreEqual((int)core.intersections.size(), 1);
			Assert::AreEqual(it->first, 1.0);
			Assert::AreEqual(it->second, 1.0);
		}
		//两直线平行
		TEST_METHOD(TestMethod2)
		{
			Core core;
			core.addGeomrtie("L 0 0 1 1");
			core.addGeomrtie("L -1 0 0 1");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 0);
		}
		//直线斜率为无穷
		TEST_METHOD(TestMethod3)
		{
			Core core;
			core.addGeomrtie("L 0 0 1 1");
			core.addGeomrtie("L 1 0 1 2");
			core.intersect();
			set<Point>::iterator it = core.intersections.begin();
			Assert::AreEqual((int)core.intersections.size(), 1);
			Assert::AreEqual(it->first, 1.0);
			Assert::AreEqual(it->second, 1.0);
		}
		//两圆相离
		TEST_METHOD(TestMethod4)
		{
			Core core;
			core.addGeomrtie("C 0 0 1");
			core.addGeomrtie("C 3 3 2");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 0);
		}
		//两圆嵌套
		TEST_METHOD(TestMethod5)
		{
			Core core;
			core.addGeomrtie("C 0 0 3");
			core.addGeomrtie("C 0 0 2");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 0);
		}
		//两圆相切
		TEST_METHOD(TestMethod6)
		{
			Core core;
			core.addGeomrtie("C 0 0 2");
			core.addGeomrtie("C 1 0 1");
			core.intersect();
			set<Point>::iterator it = core.intersections.begin();
			Assert::AreEqual((int)core.intersections.size(), 1);
			Assert::AreEqual(it->first, 2.0);
			Assert::AreEqual(it->second, 0.0);
		}
		//两圆相交于两点
		TEST_METHOD(TestMethod7)
		{
			Core core;
			core.addGeomrtie("C 0 0 2");
			core.addGeomrtie("C 2 0 2");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 2);
		}
		//圆与直线相离
		TEST_METHOD(TestMethod8)
		{
			Core core;
			core.addGeomrtie("C 0 0 1");
			core.addGeomrtie("L 2 0 2 1");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 0);
		}
		//圆与直线相切
		TEST_METHOD(TestMethod9)
		{
			Core core;
			core.addGeomrtie("C 0 0 1");
			core.addGeomrtie("L 1 0 1 1");
			core.intersect();
			set<Point>::iterator it = core.intersections.begin();
			Assert::AreEqual((int)core.intersections.size(), 1);
			Assert::AreEqual(it->first, 1.0);
			Assert::AreEqual(it->second, 0.0);
		}
		//圆与直线相交于两点
		TEST_METHOD(TestMethod10)
		{
			Core core;
			core.addGeomrtie("C 0 0 1");
			core.addGeomrtie("L 0 0 0 1");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 2);
		}
		//作业样例
		TEST_METHOD(TestMethod11)
		{
			Core core;
			core.addGeomrtie("S -1 3 2 -1");
			core.addGeomrtie("L -2 2 3 0");
			core.addGeomrtie("R -3 0 4 2");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 1);
		}
		TEST_METHOD(TestMethod12)
		{
			Core core;
			core.addGeomrtie("C 3 3 3");
			core.addGeomrtie("S 2 4 3 2");
			core.addGeomrtie("L -1 4 5 2");
			core.addGeomrtie("R 2 5 -1 2");
			core.intersect();
			Assert::AreEqual((int)core.intersections.size(), 5);
		}
		TEST_METHOD(TestMethod13)
		{
			Assert::AreEqual(checkRange("L 0 0 100000 0"), 1);
			Assert::AreEqual(checkRange("L 0 0 -100000 0"), 1);
			Assert::AreEqual(checkRange("L 0 0 100001 0"), 1);
			Assert::AreEqual(checkRange("L 0 0 -100001 0"), 1);
		}

	};
}
