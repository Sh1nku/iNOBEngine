#include "cef_manager.h"

bool CEF_INITIALIZED = false;

void CEF_INIT(int argc, char** argv) {
	// Init GUI, HOLY FUCKING SHIT; THIS NEEDS TO BE AS EARLY IN THE APPLICATION AS POSSIBLE, OR ELSE IT WILL SPAWN MULTIPLE WINDOWS USING THE ACTUAL MAIN FUNCTION, WHAT A FUCKING USELESS FEATURE
	//https://www.magpcss.org/ceforum/viewtopic.php?f=6&t=11977

	//And of course for some reason they have literally changed the constructor depending on platform, so on windows you cannot pass the arguments that are actually needed for it to coordinate multiple processes
	//Somehow it actually still works though, it manages to get the arguments to the child processes from somewhere. If it ever stops working, enable settings.single_process before CefInitialize
#ifdef _WIN32
	CefMainArgs args;
#else
	CefMainArgs args(argc, argv);
#endif
	{
		int exit_code = CefExecuteProcess(args, nullptr, nullptr);
		if (exit_code >= 0) {
			// The sub-process terminated, exit now.
			exit(exit_code);
		}
	}
	CEF_INITIALIZED = true;
}