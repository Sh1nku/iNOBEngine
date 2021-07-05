#include "guibrowserclient.h"
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