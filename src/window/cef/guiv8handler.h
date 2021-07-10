#pragma once
#include <include/cef_v8.h>
#include <include/wrapper/cef_helpers.h>


class GUIV8Handler : public CefV8Handler {
public:
    GUIV8Handler();

    virtual bool Execute(const CefString& name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList& arguments,
        CefRefPtr<CefV8Value>& retval,
        CefString& exception) override;

    // Provide the reference counting implementation for this class.
    IMPLEMENT_REFCOUNTING(GUIV8Handler);
};