#include "helper.h"
#include "dynamic.h"
#include <iostream>

int main()
{
	std::cout << dwb::sqr(5) << std::endl;

	dwb::point p1{ 10,10 };
	dwb::point p2{ 10,10 };
	dwb::point p3 = p1 + p2;

	std::cout << p3.x << " " << p3.y << std::endl;


	system("pause");
}
