// AndreaNovati_SoundProgrammingAssignment.cpp : This file contains function  'main'

#include "pch.h"
#include <iostream>
#include <string>
#include <SoundWrap.h>

#define FILENAME_MAX 255
using namespace std;
using namespace SoundWrapper;

bool lib_loaded;
int max_channels = 0;
bool exitCommand;
string absolute_path;
SoundWrap *SWS;

void printInitFirst() {
	cout << "\n **** INIT FIRST ****\n";
}

void printError() {
	cout << "\n**** An error occured! ****\n";
}

void printOk() {
	cout << "\nCommand Done.\n";
}

void printNotImplemented() {
	cout << "\n**** NOT YET DEVELOPED ****\n";
}

void printHelp() {
	cout << "SoundWrap Setup:\n";
	cout << "1) Init Library\n";
	cout << "2) Load a new resource\n";
	cout << "3) Load a new resource as Stream\n";
	cout << "\nResource management:\n";
	cout << "4) Play\n";
	cout << "5) Play and loop\n";
	cout << "6) Pause\n";
	cout << "7) Stop\n";
	cout << "8) Set Pan\n";
	cout << "9) Set Volume\n";
	cout << "H) Help\n";
	cout << "F) Exit\n";
}

void Init() {
	if (lib_loaded)
	{
		cout << "SoundWrap is already initialised.";
		return;
	}

	char c_absolute_path[FILENAME_MAX];

	GetCurrentDir(c_absolute_path, FILENAME_MAX);

	if (absolute_path.empty())
	{
		absolute_path = std::string(c_absolute_path);
		absolute_path += "\\sounds\\";
	}

	cout << "Insert absolute path [" << absolute_path.c_str() << "]: ";
	
	cin.ignore();
	string new_absolute_path;
	getline(cin, new_absolute_path);
	
	if (!new_absolute_path.empty()) 
	{
		absolute_path = new_absolute_path;
	}

	if (max_channels == 0) 
	{
		max_channels = 8;
	}

	cout << "How many channels ? [" << max_channels << "]: ";
	string new_max_channels;
	getline(cin, new_max_channels);

	if (!new_max_channels.empty()) {
		max_channels = atoi(new_max_channels.c_str());
	}

	SWS = SoundWrap::Init(absolute_path, max_channels);

	if (SWS ==  NULL) 
	{
		printError();
	}
	else 
	{
		lib_loaded = true;
		SWS->Info();
		printOk();
	}
}

void Load() 
{
	cout << "\nInsert audio resource file name: ";
	cin.ignore();
	string new_resource_file_name;
	getline(cin, new_resource_file_name);

	int result = SWS->Load(absolute_path + new_resource_file_name);
	
	if (result < 0)
		printError();
	else 
	{
		cout << "Resource ID: " << result << "\n";
		printOk();
	}
}
void LoadStreaming()
{
	cout << "\nInsert audio resource file name: ";
	cin.ignore();
	string new_resource_file_name;
	getline(cin, new_resource_file_name);

	int result = SWS->LoadStreaming(absolute_path + new_resource_file_name);

	if (result < 0)
		printError();
	else
	{
		cout << "Resource ID: " << result << "\n";
		printOk();
	}
}
void Play()
{
	cout << "Resource ID: ";
	cin.ignore();
	string new_resource_id;
	getline(cin, new_resource_id);
	int resource_id;

	if (!new_resource_id.empty()) {
		resource_id = atoi(new_resource_id.c_str());
	}

	cout << "Channel [1-" << max_channels  << "]: ";
	string new_channels;
	getline(cin, new_channels);
	int channel=-1;
	if (!new_channels.empty()) {
		channel = atoi(new_channels.c_str());
	}

	if (channel<0 )
		printError();

	int result = SWS->Play(resource_id, channel);
	if (result < 0)
		printError();
	else
		printOk();
}

void PlayLoop()
{
	cout << "Resource ID: ";
	cin.ignore();
	string new_resource_id;
	getline(cin, new_resource_id);
	int resource_id;

	if (!new_resource_id.empty()) {
		resource_id = atoi(new_resource_id.c_str());
	}

	cout << "Channel [1-" << max_channels << "]: ";
	string new_channels;
	getline(cin, new_channels);
	int channel;
	if (!new_channels.empty()) {
		channel = atoi(new_channels.c_str());
	}

	int result = SWS->PlayLoop(resource_id, channel);
	if (result < 0)
		printError();
	else
		printOk();
}


void Pause()
{
	cout << "Resource ID: ";
	cin.ignore();
	string new_resource_id;
	getline(cin, new_resource_id);
	int resource_id;

	if (!new_resource_id.empty()) {
		resource_id = atoi(new_resource_id.c_str());
	}

	int result = SWS->Pause(resource_id);

	if (result < 0)
		printError();
	else
		printOk();
}

void Stop()
{
	cout << "Resource ID: ";
	cin.ignore();
	string new_resource_id;
	getline(cin, new_resource_id);
	int resource_id;

	if (!new_resource_id.empty()) {
		resource_id = atoi(new_resource_id.c_str());
	}


	int result = SWS->Stop(resource_id);

	if (result < 0)
		printError();
	else
		printOk();
}


void SetPan()
{
	cout << "Resource ID: ";
	cin.ignore();
	string new_resource_id;
	getline(cin, new_resource_id);
	int resource_id;

	if (!new_resource_id.empty()) {
		resource_id = atoi(new_resource_id.c_str());
	}


	cout << "Pan: ";
	string new_pan;
	getline(cin, new_pan);
	float pan;
	if (!new_pan.empty()) {
		pan = atof(new_pan.c_str());
	}

	int result = SWS->SetPan(resource_id, pan);

	if (result < 0)
		printError();
	else
		printOk();
}



void SetVolume()
{
	cout << "Resource ID: ";
	cin.ignore();
	string new_resource_id;
	getline(cin, new_resource_id);
	int resource_id;

	if (!new_resource_id.empty()) {
		resource_id = atoi(new_resource_id.c_str());
	}


	cout << "Volume: ";
	string new_volume;
	getline(cin, new_volume);
	float volume;
	if (!new_volume.empty()) {
		volume = atof(new_volume.c_str());
	}

	int result = SWS->SetVolume(resource_id, volume);

	if (result < 0)
		printError();
	else
		printOk();
}



int main()
{
    cout << "Master Computer Game Development 2018/2019 - Sound Programming Assignment by Andrea Novati <nova> - v.0.1\n\n"; 
	
	printHelp();

	char command;

	while (!exitCommand) {
		cout << "\nSoundWrap> ";
		cin >> command;

		switch (command) {
		case 49: {
			cout << "Init Library\n";
			Init();
			break;
		}
		
		case 50: {
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}
			cout << "Load a new resource\n";
			Load();
			break;
		}
		case 51: {
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}

			cout << "Load a new resource as Stream\n";
			LoadStreaming();
			break;
		}
		case 52: {
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}
			cout << "Play\n";
			Play();
			break;
		}
		case 53: {
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}

			cout << "Play and loop\n";
			PlayLoop();
			break;
		}
		case 54: {
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}
			cout << "Pause\n";
			Pause();
			break;
		}
		case 55: {	
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}
			cout << "Stop\n";
			Stop();
			break;
		}
		case 56: {
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}
			cout << "Set Pan\n";
			SetPan();
			break;
		}
		case 57: {
			if (!lib_loaded)
			{
				printInitFirst();
				break;
			}
			cout << "Set Volume\n";
			SetVolume();
			break;
		}
		case 104:
		case 72:
		case 63: {
			printHelp();
			break;
		}
		case 70: 
		case 102: {
			cout << "EXIT\n";
			SWS->Close();
			exitCommand = true;

			break;
		}
		default: {
			cout << "Invalid command\n";
		}
		}
	}

}

