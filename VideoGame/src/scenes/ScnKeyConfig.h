#pragma once
#include "scenes/Scene.h"
#include "data/KeyData.h"

#define DEBUG_SCNKEYCONFIG_H_

namespace data { class KeyData; }

namespace scenes
{
	class ScnKeyConfig : public Scene
	{
	public:
		ScnKeyConfig(game::Game* game);
		~ScnKeyConfig();

		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;
	private:

		data::KeyData* mKeyData;	// キー配置を記憶するクラス
		data::KeyType mKTypeCursor;	// 現在カーソルを合わせているコマンド
		SG_Scancode* mKSelecting;	// 現在更新中のキー
		SDL_Scancode wasSelectedCmd;// 前フレームで選択されたコマンド
		bool mKeyUpdating;	// キーボタンの更新中か
		float keyLockTime;	// キー入力を受け付けない時間
		bool wasPushedEtr;	// 直前のフレームでEnterキーが押されていたか
		bool wasPushedQ;
		bool wasPushedEsc;

		/* Update Functinos */
		void SwitchKeyUpdate();
		SG_Scancode* RegistKType();
		void IsKeyAlreadyUsed(SDL_Scancode& code);
		void CannotUpdateKey(bool& wasPushed);
		void KeyUpdating(const uint8_t* keyState);
		void NotKeyUpdating(const uint8_t* keyState);
		void RenewCursor(SDL_Scancode* key, data::KeyType type, std::string cmdName);
		/* End of Update Functions */

#ifdef DEBUG_SCNKEYCONFIG_H_
		void PrintRgsteredKey();	// カーネル上で現在のキー設定を表示
#endif
	};
}
