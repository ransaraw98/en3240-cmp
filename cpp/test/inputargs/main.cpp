#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	cout << "You have entered " << argc
		<< " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		cout << argv[i] << "\n";

	//cout << stoul(argv[1],NULL,10);
	return 0;
}
