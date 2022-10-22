﻿#include "components/SpriteComponent.h"
#include "actors/Actor.h"
#include "scenes/Scene.h"


namespace components
{
	SpriteComponent::SpriteComponent(actors::Actor* owner, int drawOrder)
		:Component(owner)
		,mTexture(nullptr)
		,mTexHeight(0)
		,mTexWidth(0)
		,mDrawOrder(drawOrder)
		,mAlpha(255)
	{
		mOwner->GetScene()->AddSprite(this);
	}

	SpriteComponent::~SpriteComponent()
	{
		mOwner->GetScene()->RemoveSprite(this);
	}

	void SpriteComponent::Draw(SDL_Renderer* renderer)
	{
		if (mTexture)
		{
			SDL_SetTextureAlphaMod(mTexture, mAlpha);
			SDL_Rect r;
			r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
			r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
			// 座標は左上基準
			r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
			r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

			// 描画（角度をラジアンから度へ、時計回りから反時計回りに変換する必要があります。）
			SDL_RenderCopyEx(renderer,
				mTexture,
				nullptr,
				&r,
				-math::ToDegrees(mOwner->GetRotation()),
				nullptr,
				SDL_FLIP_NONE);
		}
	}

	void SpriteComponent::SetTexture(SDL_Texture* texture)
	{
		mTexture = texture;
		SDL_SetTextureAlphaMod(mTexture, mAlpha);
		SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
	}
}
