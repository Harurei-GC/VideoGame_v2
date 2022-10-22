#pragma once
#include "components/Component.h"
#include "SDL.h"

namespace components
{
	class SpriteComponent :public Component
	{
	public:
		// drawOrderが低いほど後方に位置する
		SpriteComponent(actors::Actor* owner, int drawOrder = 100);
		~SpriteComponent();

		virtual void Draw(SDL_Renderer* renderer);
		virtual void SetTexture(SDL_Texture* texture);

		int GetDrawOrder() const{ return mDrawOrder; }
		int GetTexHeight() const{ return mTexHeight; }
		int GetTexWidth() const { return mTexWidth; }
		void SetRenderColorAlpha(int alpha) { mAlpha = alpha; }
	protected:
		SDL_Texture* mTexture;
		int mDrawOrder;
		int mTexWidth;
		int mTexHeight;
		Uint8 mAlpha;
	};
}
