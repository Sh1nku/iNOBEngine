#pragma once

#include <include/cef_app.h>
#include <include/wrapper/cef_helpers.h>

class GUIApp : public CefApp, public CefRenderProcessHandler, CefBrowserProcessHandler {
public:
    GUIApp();

    // CefApp methods:
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

    void OnContextInitialized() override;

    // CefRendeProcessHandler methods:
    void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
    virtual void OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(GUIApp);
    DISALLOW_COPY_AND_ASSIGN(GUIApp);
};