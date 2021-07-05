#include "guirenderhandler.h"
#include "../../io/texture.h"
#include "../window.h"

GUIRenderHandler::GUIRenderHandler()
{
    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    GLuint textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempSurface->w, tempSurface->h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tempSurface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    texture = new Texture(textureHandle, tempSurface->w, tempSurface->h, tempSurface->format->BytesPerPixel);
    SDL_FreeSurface(tempSurface);
}

bool GUIRenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) {
    rect = CefRect(0, 0, Window::SCREEN_WIDTH, Window::SCREEN_HEIGHT);
    return true;
}

void GUIRenderHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int w, int h) {
    if (texture)
    {
        SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        SDL_LockSurface(tempSurface);
        memcpy(tempSurface->pixels, buffer, w * h * 4);
        SDL_UnlockSurface(tempSurface);
        glBindTexture(GL_TEXTURE_2D, texture->GetID());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempSurface->w, tempSurface->h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, tempSurface->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(tempSurface);
    }
}