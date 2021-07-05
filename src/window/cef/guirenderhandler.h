#pragma once

#include <include/cef_app.h>
#include <include/cef_client.h>
#include <include/cef_render_handler.h>
#include <include/cef_life_span_handler.h>
#include <include/cef_load_handler.h>
#include <include/wrapper/cef_helpers.h>
#include <SDL.h>
#include <gl/GL.h>

class Texture;
class RenderSystem;

class GUIRenderHandler : public CefRenderHandler {
public:
    friend class RenderSystem;
    GUIRenderHandler();
    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;
    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int w, int h) override;

private:
    Texture* texture = nullptr;

    IMPLEMENT_REFCOUNTING(GUIRenderHandler);
};