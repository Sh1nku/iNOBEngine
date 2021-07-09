#include "guibrowserclient.h"
#include "guiv8handler.h"
#include <iostream>

GUIBrowserClient::GUIBrowserClient(CefRefPtr<CefRenderHandler> ptr) : handler(ptr) {
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
     
    std::wcout << "Javascript error, line " << line << "\n    " << message.c_str() << "\n";
    return true;
}

bool GUIBrowserClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    std::cout << "Recieved javascript message: " << message->GetName().ToString() << std::endl;
    for (int i = 0; i < message->GetArgumentList()->GetSize(); i++) {
        std::cout << "    " << message->GetArgumentList()->GetString(i).ToString() << std::endl;
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