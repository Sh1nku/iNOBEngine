#include "guiv8handler.h"
#include <iostream>

GUIV8Handler::GUIV8Handler() {
}

bool GUIV8Handler::Execute(const CefString& name,
     CefRefPtr<CefV8Value> object,
     const CefV8ValueList& arguments,
     CefRefPtr<CefV8Value>& retval,
     CefString& exception) {

    CefRefPtr<CefBrowser> browser = CefV8Context::GetCurrentContext()->GetBrowser();
    CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(name);
    for (int i = 0; i < arguments.size(); i++) {

        auto& argument = arguments.at(i);
        if (argument->IsString()) {
            message->GetArgumentList()->SetString(i, argument->GetStringValue());
        }
        else if (argument->IsInt()) {
            message->GetArgumentList()->SetInt(i, argument->GetIntValue());
        }
        else if (argument->IsBool()) {
            message->GetArgumentList()->SetBool(i, argument->GetBoolValue());
        }
        else {
            std::cout << "Unsupported Type" << std::endl;
            retval = CefV8Value::CreateBool(false);
            return false;
        }
        
    }
    browser->SendProcessMessage(PID_BROWSER, message);
    retval = CefV8Value::CreateBool(true);
    return true;
}