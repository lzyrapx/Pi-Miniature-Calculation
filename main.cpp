#if defined(_MSC_VER) && (_MSC_VER <= 1600) // _MSC_VER是微软的预编译控制,指的是Microsoft的C编译器的版本
// do something
#endif

#ifdef _MSC_VER
#pragma warning(disable:4996)   // 消除_CRT_SECURE_NO_DEPRECATE警告
#endif

#include <chrono> // 标准模板库中与时间有关的头文件
#include <iostream>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "BigFloat.h"

using namespace std;

void output_to_file(const char *path, const std::string &str) // 向文件输出string
{

	FILE *file = fopen(path, "wb");
	if (file == NULL) throw "Error! Cannot Create File";

	fwrite(str.c_str(), 1, str.size(), file);
	fclose(file);
}

double time_clock() // running time
{
#if USE_CHRONO
	auto ratio_object = std::chrono::high_resolution_clock::period();
	double ratio = (double)ratio_object.num / ratio_object.den;
	return std::chrono::high_resolution_clock::now().time_since_epoch().count() * ratio;
#else
	return (double)clock() / CLOCKS_PER_SEC;
#endif
}

// Binary Splitting recursion for the Chudnovsky Formula.
void calc(BigFloat &P, BigFloat &Q, BigFloat &R, uint32_t a, uint32_t b, size_t p) // p 是精度
{	
	// https://en.wikipedia.org/wiki/Chudnovsky_algorithm

	if (b - a == 1)
	{
		//  P = (545140134*b + 13591409)*(2b-1)*(6b-5)*(6b-1) (-1)^b
		P = BigFloat(b).mul(545140134);
		P = P.add(BigFloat(13591409));
		P = P.mul(2 * b - 1);
		P = P.mul(6 * b - 5);
		P = P.mul(6 * b - 1);
		if (b % 2 == 1) {
			P.negate();
		}
		//  Q = 10939058860032000 * b^3
		Q = BigFloat(b);
		Q = Q.mul(Q).mul(Q).mul(26726400).mul(409297880);

		//  R = (2b-1)*(6b-5)*(6b-1)
		R = BigFloat(2 * b - 1);
		R = R.mul(6 * b - 5);
		R = R.mul(6 * b - 1);
		return;
	}

	uint32_t m = (a + b) / 2;

	BigFloat P0, Q0, R0, P1, Q1, R1;
	calc(P0, Q0, R0, a, m, p);
	calc(P1, Q1, R1, m, b, p);

	P = P0.mul(Q1, p).add(P1.mul(R0, p), p);
	Q = Q0.mul(Q1, p);
	R = R0.mul(R1, p);
}
void Pi(int digits)
{
	//第一个 3 不计算
	digits++;
	int  p = (digits + 8) / 9;
	int terms = (int)(p * 0.6346230241342037371474889163921741077188431452678) + 1;

	// limit exceeded
	if ((int)terms != terms)
	{
		throw "limit exceeded!";
	}
	std::cout << "Computing Pi ..." << '\n' << '\n';

	// https://en.wikipedia.org/wiki/Chudnovsky_algorithm

	double time0 = time_clock();
	cout << "Summing Series... " << terms << " terms" << '\n';
	BigFloat P, Q, R;
	calc(P, Q, R, 0, (uint32_t)terms, p);

	P = Q.mul(13591409).add(P, p);
	Q = Q.mul(4270934400);
	P = Q.div(P, p);

	// 牛顿迭代计算开平方的倒数
	Q = invsqrt(10005, p);

	cout << "Final Multiply... " << '\n';
	P = P.mul(Q, p);

	double time1 = time_clock();
	cout << "Time elapsed = " << time1 - time0 << "s" << '\n' << '\n';

	output_to_file("pi.txt", P.to_string(digits));
	//cout << P.to_string(digits) << endl;
}
int main(int argc, char const *argv[])
{
	int digits = 100; // N digits of Pi.
	//BigFloat a = 1.12312312412331241;
	//BigFloat b = 1.21312312423432;
	//BigFloat multi = a.add(b);
	//cout << multi.to_string(1000);
	Pi(digits);
	system("pause");
	return 0;
}
