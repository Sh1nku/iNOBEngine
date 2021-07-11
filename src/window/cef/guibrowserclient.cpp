#include "guibrowserclient.h"
#include "guiv8handler.h"
#include <iostream>
#include "../../io/resources.h"
#include "../../manager.h"
#include "../../types/systems/rendersystem.h"

GUIBrowserClient::GUIBrowserClient(CefRefPtr<CefRenderHandler> ptr, RenderSystem* renderSystem) : handler(ptr), renderSystem(renderSystem) {
}

CefRefPtr<CefLifeSpanHandler> GUIBrowserClient::GetLifeSpanHandler() {
    return this;
}

CefRefPtr<CefLoadHandler> GUIBrowserClient::GetLoadHandler() {
    return this;
}

CefRefPtr<CefRenderHandler> GUIBrowserClient::GetRenderHandler() {
    return handler;
}

CefRefPtr<CefDisplayHandler> GUIBrowserClient::GetDisplayHandler() {
    return this;
}

// CefLifeSpanHandler methods.
void GUIBrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    // Must be executed on the UI thread.
    CEF_REQUIRE_UI_THREAD();

    browser_id = browser->GetIdentifier();
}

bool GUIBrowserClient::DoClose(CefRefPtr<CefBrowser> browser) {
    // Must be executed on the UI thread.
    CEF_REQUIRE_UI_THREAD();

    // Closing the main window requires special handling. See the DoClose()
    // documentation in the CEF header for a detailed description of this
    // process.
    if (browser->GetIdentifier() == browser_id)
    {
        // Set a flag to indicate that the window close should be allowed.
        closing = true;
    }

    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void GUIBrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
}

void GUIBrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
    std::cout << "OnLoadEnd(" << httpStatusCode << ")" << std::endl;

    std::ostringstream applicationPathString;
    applicationPathString << "window.__applicationPath = '" << Resources::gameDirAbsoulute << "';";
    frame->ExecuteJavaScript(applicationPathString.str(), frame->GetURL(), 0);
    static std::string create_fps_string =
    R"(
	        let fps = document.createElement('p');
	        fps.style.cssText = 'position:absolute;left:0;top:0;color:white;z-index:9999;margin:0;display:none';
	        fps.id = '__fps_counter';
	        document.body.appendChild(fps);
    )";
    frame->ExecuteJavaScript(create_fps_string, frame->GetURL(), 0);

    std::ostringstream fpsDisplayString;
    fpsDisplayString << "document.getElementById('__fps_counter').style.display='" << (renderSystem->GetShowFPS() ? "inline" : "none") << "';";
    frame->ExecuteJavaScript(fpsDisplayString.str(), frame->GetURL(), 0);

    loaded = true;
}

bool GUIBrowserClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode, const CefString& failedUrl, CefString& errorText)
{
    std::cout << "OnLoadError()" << std::endl;
    loaded = true;
    return true;
}

void GUIBrowserClient::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
{
    std::cout << "OnLoadingStateChange()" << std::endl;
}

bool GUIBrowserClient::OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line)
{
     
    std::wcout << message.c_str() << std::endl;
    return true;
}

bool GUIBrowserClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    std::cout << "Recieved javascript message: " << message->GetName().ToString() << std::endl;
    for (int i = 0; i < message->GetArgumentList()->GetSize(); i++) {
        std::cout << "    " << message->GetArgumentList()->GetString(i).ToString() << std::endl;
    }
    if (message->GetName().ToString().compare("__sendMessage") == 0) {
        Manager::GetInstance()->FireEvent(nullptr, message->GetArgumentList()->GetString(0), (void*)"data");
    }
    return false;
}

void GUIBrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
    std::cout << "OnLoadStart()" << std::endl;
}

bool GUIBrowserClient::closeAllowed() const
{
    return closing;
}

bool GUIBrowserClient::isLoaded() const
{
    return loaded;
}