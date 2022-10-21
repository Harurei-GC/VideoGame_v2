#include "data/KeyData.h"

namespace data
{
	KeyData::KeyData()
	{
		mUpKey.Setter(SDL_SCANCODE_W);
		mDownKey.Setter(SDL_SCANCODE_S);
		mRightKey.Setter(SDL_SCANCODE_D);
		mLeftKey.Setter(SDL_SCANCODE_A);
		mResetKey.Setter(SDL_SCANCODE_R);
	}

	KeyData::~KeyData()
	{

	}


}