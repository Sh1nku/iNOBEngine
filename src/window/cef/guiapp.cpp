#include "guiapp.h"
#include "guiv8handler.h"
#include <iostream>

GUIApp::GUIApp() {}

CefRefPtr<CefRenderProcessHandler> GUIApp::GetRenderProcessHandler()
{
    return this;
}

CefRefPtr<CefBrowserProcessHandler> GUIApp::GetBrowserProcessHandler()
{
    return this;
}

void GUIApp::OnContextInitialized()
{
}

void GUIApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    std::cout << "Created context" << std::endl;
    CefRefPtr<CefV8Handler> handler = new GUIV8Handler();
    object->SetValue("__sendMessage",
        CefV8Value::CreateFunction("__sendMessage", handler),
        V8_PROPERTY_ATTRIBUTE_NONE);

}

void GUIApp::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
}
