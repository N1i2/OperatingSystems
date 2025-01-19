#include <iostream>

int main(int argc, char* argv[])
{
	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);

	std::cout << now->tm_mday << "." << now->tm_mon + 1 << "." << now->tm_year + 1900 << " (" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << ")" << std::endl;

	return 0;
}