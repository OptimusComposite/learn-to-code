// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

int i = 0;

int main() {
	int i = 42;
	int *p = &i;
	*p = *p * *p;
	cout << i << " " << p << endl;
	return 0;
}

