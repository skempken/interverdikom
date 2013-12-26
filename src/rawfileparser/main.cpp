/*
 * Main-Methode - Delegation ins Klassenframework
*/

#include "ParserApplication.h"

int main(int argc, char **argv) {
	// Let the application class handle the call
	ParserApplication app;
	return app.handleCall(argc,argv);
}
