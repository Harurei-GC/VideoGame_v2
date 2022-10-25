#pragma once
#include "scenes/Scene.h"
#include "data/KeyData.h"


namespace data { class KeyData; }

namespace scenes
{

	struct KeyCursorColor
	{
		int UP = RED;
		int DOWN = BLUE;
		int RIGHT = BLUE;
		int LEFT = BLUE;
		int RESET = BLUE;
	};

	class ScnKeyConfig : public Scene
	{
	public:
		ScnKeyConfig(game::Game* game);
		~ScnKeyConfig();

		void ProcessInput()override;
		void UpdateGame()override;
		void GenerateOutput()override;
	private:

		KeyCursorColor keyCC;		// 選択中のキーの表示色を記憶する構造体
		data::KeyData* mKeyData;	// キー配置を記憶するクラス
		data::KeyType mKTypeCursor;	// 現在カーソルを合わせているコマンド
		SG_Scancode* mKSelecting;	// 現在更新中のキー
		SDL_Scancode wasSelectedCmd;// 前フレームで選択されたコマンド
		bool mKeyUpdating;	// キーボタンの更新中か
		float keyLockTime;	// キー入力を受け付けない時間
		bool wasPushedEtr;	// 直前のフレームでEnterキーが押されていたか
		bool wasPushedQ;
		bool wasPushedEsc;
		bool cannotUpdateKey;

		/* Update Functinos */
		void SwitchKeyUpdate();
		void ResetKeyCursorColor(KeyCursorColor* kcc);
		SG_Scancode* RegistKType();
		void IsKeyAlreadyUsed(SDL_Scancode& code);
		void CannotUpdateKey(bool& wasPushed);
		void KeyUpdating(const uint8_t* keyState);
		void NotKeyUpdating(const uint8_t* keyState);
		void RenewCursor(SDL_Scancode* key, data::KeyType type, std::string cmdName);
		/* End of Update Functions */

		/* Generate Update Functions */
		/* End of Generate Update Functions */

#ifdef DEBUG_SCNKEYCONFIG_H_
		void PrintRgsteredKey();	// カーネル上で現在のキー設定を表示
#endif
	};
}
