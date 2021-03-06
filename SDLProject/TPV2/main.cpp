//#include <iostream>
//
//#include "StarWars.h"
//
//using namespace std;
//
//
//
//int main(int argc, char **argv) {
//	try {
//		StarWars g;
//		g.start();
//	} catch (std::string &e) { // catch errors thrown as strings
//		cerr << e << endl;
//	} catch (const std::exception &e) { // catch other exceptions
//		cerr << e.what();
//	} catch (...) {
//		cerr << "Caught and exception of unknown type ..";
//	}
//
//	return 0;
//}
#include <iostream>

#include "StarWars.h"
#include "Networking.h"

using namespace std;



void server(int port) {
	cout << "bruh\n";
	Networking net;
	net.server(port);
}

void client(char* host, int port, const char* name) {
	try {
		StarWars g = StarWars(host, port, name);
		g.start();
	}
	catch (std::string& e) { // catch errors thrown as strings
		cerr << e << endl;
	}
	catch (const std::exception& e) { // catch other exceptions
		cerr << e.what();
	}
	catch (...)
	{
		cerr << "whoops";
	}
	cerr << SDL_GetError();
}


int main(int argc, char** argv) {
	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(atoi(argv[2])); // start in server mode
	}
	else if (argc == 4 && strcmp(argv[1], "client") == 0) {
		client(argv[2], atoi(argv[3]), "Anonymus"); // start in client mode
	}
	else if (argc == 5 && strcmp(argv[1], "client") == 0)
	{
		char* name=new char[11];
		strcpy_s(name, 11,argv[4]);
		if (strlen(name) > 10)
		{
			cout << "Name is too long";
			return 1;
		}
		client(argv[2], atoi(argv[3]), name);
	}
	else {
		cout << "Usage: " << endl;
		cout << "  " << argv[0] << " client host port " << endl;
		cout << "  " << argv[0] << " server port " << endl;
		cout << endl;
		cout << "Example:" << endl;
		cout << "  " << argv[0] << " server 2000" << endl;
		cout << "  " << argv[0] << " client localhost 2000" << endl;
	}

	return 0;
}
