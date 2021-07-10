#include "cef_manager.h"
#include "guiapp.h"
#include <iostream>
#include <SDL.h>
#include "../../io/resources.h"

bool CEF_INITIALIZED = false;
CefRefPtr<GUIRenderHandler> GUIrenderHandler = nullptr;
CefRefPtr<CefBrowser> GUIbrowser = nullptr;
CefRefPtr<GUIBrowserClient> GUIbrowserClient = nullptr;

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
		CefRefPtr<GUIApp> cef_app(new GUIApp());
		int exit_code = CefExecuteProcess(args, cef_app.get(), nullptr);
		if (exit_code >= 0) {
			// The sub-process terminated, exit now.
			std::cout << "Terminate child process" << std::endl;
			exit(exit_code);
		}

		{
			CefMainArgs args;
			CefSettings settings;
			std::ostringstream ss;
			ss << SDL_GetBasePath() << "locales/";
			CefString(&settings.locales_dir_path) = ss.str();
			CefString(&settings.resources_dir_path) = SDL_GetBasePath();
			settings.no_sandbox = true;
			settings.windowless_rendering_enabled = true;
			//This causes UI thread not to exist, and instead be in main thread
			settings.multi_threaded_message_loop = false;
			//settings.single_process = true;
			CefInitialize(args, settings, cef_app.get(), nullptr);
		}
	}
	CEF_INITIALIZED = true;
}

void CEF_CLOSE()
{
	if (CEF_INITIALIZED) {
		CEF_INITIALIZED = false;
		GUIbrowser->GetHost()->CloseBrowser(true);
		GUIbrowserClient = nullptr;
		GUIrenderHandler = nullptr;

		CefDoMessageLoopWork();

		GUIbrowser = nullptr;
		CefShutdown();
	}
}