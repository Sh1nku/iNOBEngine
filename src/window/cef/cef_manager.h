#pragma once
#include <cstdlib>
#include <include/wrapper/cef_helpers.h>
#include <include/cef_app.h>
#include "guiapp.h"
#include "guirenderhandler.h"
#include "guibrowserclient.h"

extern bool CEF_INITIALIZED;
extern CefRefPtr<GUIRenderHandler> GUIrenderHandler;
extern CefRefPtr<CefBrowser> GUIbrowser;
extern CefRefPtr<GUIBrowserClient> GUIbrowserClient;

void CEF_INIT(int argc, char** argv);
void CEF_CLOSE();