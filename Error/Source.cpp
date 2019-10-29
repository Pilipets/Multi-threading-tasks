#include <chrono>
#include <iostream>
#include <string>

#include <boost/process.hpp>

using namespace std;
namespace bp = boost::process;

template<class T>
bool bufferEmpty(std::basic_istream<T> &pipe)
{
	pipe.seekg(0, pipe.end);
	int length = pipe.tellg();
	cout << "length= " << length << endl;
	if (length < 0) return true; 

	pipe.seekg(0, pipe.beg);
	return false;
}
int main(int argc, char **argv)
{
	if (argc == 1)
	{
		bp::ipstream pout;
		bp::opstream pin;

		pin << "Message from main process" << endl;
		auto process = bp::child(std::string(argv[0]), "OPTIONAL", bp::std_in < pin, bp::std_out > pout, bp::std_err > stderr);

		/*while (process.running() || !bufferEmpty(pout)) {
			if (bufferEmpty(pout))
			{
				cout << "Waiting...\n";
				this_thread::sleep_for(std::chrono::milliseconds(500));
			}
			else {
				std::string s;
				std::getline(pout, s);
				cout << "Received message from additional thread: " << s << endl;
			}
		}*/
		//std::string s;
		//std::getline(pout, s);
		//cout << "Received message from additional thread: " << s << endl;
		this_thread::sleep_for(std::chrono::milliseconds(5000));
		cout << bufferEmpty(pout) << endl;
		process.wait();
		system("pause");
	}
	else {
		std::string s;
		std::getline(cin, s);
		cerr << "Received from Main process: " << s << endl;
		this_thread::sleep_for(std::chrono::milliseconds(3000));
		cout << "Message from Additional process" << endl;
		cerr << "Sent message 1 from additional process" << endl;
		this_thread::sleep_for(std::chrono::milliseconds(3000));
		cout << "Additional process finished" << endl;
		cerr << "Sent message 2 from additional process" << endl;
	}
	return 0;
}