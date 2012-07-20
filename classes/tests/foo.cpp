#include <iostream>

int main(void)
{
	char buf[80];
	//std::cin >> buf;
	std::cin.getline(buf, sizeof(buf));
	std::cout << "{" << buf << "}\n";
	return 0;
}
