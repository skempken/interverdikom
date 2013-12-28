#include "ParserApplication.h"

#include "GetPot.h"
#include "ContainerFormatParser.h"
#include "AVIParser.h"
#include "MOVParser.h"
#include "WMVParser.h"
#include "ASFObject.h"

#include <iostream>
#include <fstream>

using namespace std;

ParserApplication::ParserApplication() {}

ParserApplication::~ParserApplication() {}

int ParserApplication::handleCall(int argc, char **argv)
{
	GetPot commandLine(argc, argv);
	
	if (commandLine.search(2, "-h", "--help"))
	{
		printUsage(argv[0]);
		return 1;
	}
	
	bool dumpVideo = commandLine.search(6, "-vid", "-video", "-v", "--vid", "--video", "--v")
				|| !commandLine.search(6, "-no-vid", "-no-video", "-no-v", "--no-vid", "--no-video", "--no-v");
	bool dumpAudio = commandLine.search(6, "-aud", "-audio", "-a", "--aud", "--audio", "--a")
				&& !commandLine.search(6, "-no-aud", "-no-audio", "-no-a", "--no-aud", "--no-audio", "--no-a");
	bool dumpTimeIndex = commandLine.search(6, "-ti", "-time-index", "--ti", "--time-index")
				&& !commandLine.search(6, "-no-ti", "-no-time-index", "--no-ti", "--no-time-index");
		
	if (argc < 2)
	{
		cout << "Error: No input file specified. Try -h for help." << endl;
		return 1;
	}
	
	ifstream video_file;
	video_file.open(argv[1],ios::binary);
	if (!video_file.good()) // File doesn't exist or is size 0
	{
		cout << "Bad input file." << endl;
		return 0;
	}
	
	// Construct parser object for the given file
	string file_name(argv[1]);
	ContainerFormatParser *parser = ContainerFormatParser::getParserForFile(video_file);
	if (parser == 0)
	{
		cout << "No parser for file, exiting." << endl;
		exit(0);
	}
	
	cout << "Parsing... ";
	cout.flush();
	
	// Extract data
	parser->setDumpTimeIndex(dumpTimeIndex);
	parser->parseFile(video_file);	
	
	cout << "writing output files... ";
	cout.flush();
	
	// Construct Output file names
	string vfname = commandLine.follow(strcat(argv[1], ".video"), 4, "-vo","--vo", "--vo", "--video-output");
	string afname = commandLine.follow(strcat(argv[1], ".audio"), 4, "-vo","--vo", "--vo", "--video-output");
	
	// Construct Output file streams
	ofstream vids_output;
	ofstream auds_output;
	
	if (dumpVideo)
		vids_output.open(vfname.c_str());
	
	if (dumpAudio)
		auds_output.open(afname.c_str());
	
	parser->writeOutputFiles(vids_output, auds_output); // Write data to file
	
	// Close streams
	vids_output.close();
	auds_output.close();
	
	cout << "finished." << endl;
	
	return 0;
}

void ParserApplication::printUsage(const char * programName)
{
	cout << "Usage: " << endl
		<< programName << " <input file> [--video | --no-video] [--audio | --no-audio]" << endl
		<< "\t\t[--time-index | --no-time-index]" << endl
		<< "\t\t[--output-video <output file>] [--output-audio <output file>]" << endl
		<< endl
		<< "<input file>\t\tThe video file from which stream data should\n\t\t\tbe extracted." << endl
		<< "-v, --video\t\tExtract video stream data. (default: on)" << endl
		<< "-no-v, --no-video\tDo not extract video stream data." << endl
		<< "-a, --audio\t\tExtract audio stream data. (default: off)" << endl
		<< "-no-a, --no-audio\tDo not extract audio stream data." << endl
		<< "-ti, --time-index\tCreate output file with time index. (default: off)" << endl
		<< "-no-ti, --no-time-index\tDo not create output file with time index." << endl
		<< "-ov, --output-video\tTarget file for video stream data.\n\t\t\t(default: \"<input file>.video\")" << endl
		<< "-oa, --output-audio\tTarget file for audio stream data.\n\t\t\t(default: \"<input file>.audio\")" << endl;
}
