#include "rendersystem.h"
#include "../../io/resources.h"
#include "../../window/window.h"
#include "../component.h"
#include "../components/animation.h"
#include "../components/transform.h"

RenderSystem::RenderSystem() {
	mMap.insert({ Component::GetBitcode("Transform") | Component::GetBitcode("Animation"), std::make_unique<gameObject_map>() });

	window = new Window();
	window->Create();
	//Load textures that could not be loaded because glContext did not exist
	for (auto& texture : Resources::textureBacklog) {
		Texture* tempTex = Texture::LoadTexture(texture.first);
		memcpy(texture.second, tempTex, sizeof(Texture));
	}
	//Reload textures that were deleted from a previous context
	for (auto& texturePair : Resources::textures) {
		if (!glIsTexture(texturePair.second->GetID())) {
			Texture* tempTex = Texture::LoadTexture((std::string)texturePair.first);
			memcpy(texturePair.second.get(), tempTex, sizeof(Texture));
		}
	}
	Resources::textureBacklog.clear();
}

RenderSystem::~RenderSystem() {
	delete window;
}

void RenderSystem::Update(float dt) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 1.f, 1.f);
	//gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	for (auto& entry : *GetEntries(Component::GetBitcode("Animation") | Component::GetBitcode("Transform"))) {
		Animation* anim = (Animation*)entry.second->at(Component::GetBitcode("Animation"));
		Transform* transform = (Transform*)entry.second->at(Component::GetBitcode("Transform"));
		UI32 id = anim->currentClip->texture->GetID();
		b2Vec2& worldPos = transform->GetWorldPosition();
		Texture* tex = anim->currentClip->texture;
		AnimationCoords& coords = anim->currentClip->frames.at(anim->currentFrame).coords;

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, id);
		glTranslatef(worldPos.x, worldPos.y, -5);
		glRotatef(transform->GetWorldRotation() , 0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(coords.bottomLeft.x / tex->width,coords.bottomLeft.y / tex->height);
		glVertex3f(-.5f, -.5f, 0);
		glTexCoord2f(coords.bottomRight.x / tex->width, coords.bottomRight.y / tex->height);
		glVertex3f(.5f, -.5f, 0);
		glTexCoord2f(coords.topRight.x / tex->width, coords.topRight.y / tex->height);
		glVertex3f(.5f, .5f, 0);
		glTexCoord2f(coords.topLeft.x / tex->width, coords.topLeft.y / tex->height);
		glVertex3f(-.5f, .5f, 0);
		glEnd();
		glPopMatrix();
	}
	SDL_GL_SwapWindow(window->mWindow);
	
}