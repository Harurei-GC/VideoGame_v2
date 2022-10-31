#include "scenes/ScnKeyConfig.h"
#include "game/Game.h"
#include <iostream>

namespace scenes
{
	ScnKeyConfig::ScnKeyConfig(game::Game* game)
		:Scene(game)
		,mKeyUpdating(false)
		,mKTypeCursor(data::KeyType::UP)
		,keyLockTime(0.0f)
		,wasPushedEtr(false)
		,wasPushedQ(false)
		,wasPushedEsc(false)
		,cannotUpdateKey(false)
		,mKSelecting(nullptr)
		,wasSelectedCmd(SDL_SCANCODE_UNKNOWN)
	{
		mKeyData = game->GetKeyData();
		ReadTextFile("assets/KeyConfig.txt");
	}

	ScnKeyConfig::~ScnKeyConfig()
	{

	}

	void ScnKeyConfig::ProcessInput()
	{
		Scene::ProcessInput();

		if (!mKeyUpdating)
		{
			const uint8_t* keyState = SDL_GetKeyboardState(NULL);
			if (keyState[SDL_SCANCODE_ESCAPE])
			{
				mIsRunning = false;
				mGame->SetQuitGame(true);
			}
			if (keyState[SDL_SCANCODE_Q])
			{
				mIsRunning = false;
			}

		}
	}


	void ScnKeyConfig::UpdateGame()
	{
		Scene::UpdateGame();

		const uint8_t* keyState = SDL_GetKeyboardState(NULL);

		if (keyState[SDL_SCANCODE_RETURN])
		{
			SwitchKeyUpdate();
		}
		else
		{// このフレームでエンターキーを押さなかった場合
			wasPushedEtr = false;
		}

		if (mKeyUpdating)// キーのアップデート中の処理（排他的）
		{
			KeyUpdating(keyState);
		}
		else// アップデートしていないとき
		{
			NotKeyUpdating(keyState);
		}
	}

	void ScnKeyConfig::GenerateOutput()
	{
		int tex = 50;
		int row = 0;
		// @todo デバッグモード（カーネル）と比較して挙動が一緒か確認
		// @todo 選択中のものに色を付ける
		SDL_SetRenderDrawColor(mGame->gameRenderer, 220, 220, 220, 255);
		SDL_RenderClear(mGame->gameRenderer);

		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row++);	// 対応するキー
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row++);	// 選択中に
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row++);	// Qキーで完了
		RenderText(FONT_PixelMplus, BLACK, "", 100, 100 + tex * row++);			//
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row);	// Up
		RenderText(FONT_BBBOcelot_Regular, keyCC.UP,
			SDL_GetScancodeName(mKeyData->GetUpKey().Getter()), 350, 100 + tex * row++);
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row);	// Down
		RenderText(FONT_BBBOcelot_Regular, keyCC.DOWN,
			SDL_GetScancodeName(mKeyData->GetDownKey().Getter()), 350, 100 + tex * row++);
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row);	// Right
		RenderText(FONT_BBBOcelot_Regular, keyCC.RIGHT,
			SDL_GetScancodeName(mKeyData->GetRightKey().Getter()), 350, 100 + tex * row++);
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row);	// Left
		RenderText(FONT_BBBOcelot_Regular, keyCC.LEFT,
			SDL_GetScancodeName(mKeyData->GetLeftKey().Getter()), 350, 100 + tex * row++);
		DispSentenceFromFile(FONT_PixelMplus, BLACK, 100, 100 + tex * row);	// Reset
		RenderText(FONT_BBBOcelot_Regular, keyCC.RESET,
			SDL_GetScancodeName(mKeyData->GetResetKey().Getter()), 350, 100 + tex * row++);

		if (mKeyUpdating)
		{
			RenderText(FONT_PixelMplus, BLACK, "使いたいキーを押してください", 100, 100 + tex * row++);
			if (cannotUpdateKey)
			{
				RenderText(FONT_PixelMplus, RED, "このキーは使えません", 100, 100 + tex * row++);
			}
		}

		SDL_RenderPresent(mGame->gameRenderer);
		bufCount = 0;
	}

	

	/* Update Functions */

	void ScnKeyConfig::SwitchKeyUpdate()
	{// エンターで、キーのアップデートON|OFF
		if (!wasPushedEtr)
		{// 前回のフレームでエンターキーを押していない
		 // ＝押し始めの場合、処理実行
			wasPushedEtr = true;	// 次回以降のフレームで、連続してEnterキー入力ができないようにする

			mKeyUpdating = !mKeyUpdating;

			if (mKeyUpdating)// キーのアップデート時に限り実行
			{
				// KeyData内のコマンドを選択し登録
				mKSelecting = RegistKType();
				// 「このキーは使えません」表示の解除
				cannotUpdateKey = false;				
			}
		}
	}


	void ScnKeyConfig::ResetKeyCursorColor(KeyCursorColor* kcc)
	{
		kcc->UP = BLUE;
		kcc->DOWN = BLUE;
		kcc->RIGHT = BLUE;
		kcc->LEFT = BLUE;
		kcc->RESET = BLUE;
	}

	SG_Scancode* ScnKeyConfig::RegistKType()
	{
		// 現在のmKeyTypeに対応するKeyData::mKeyのGetterを返す
		switch (mKTypeCursor)
		{
		case data::KeyType::UP:
			return mKeyData->GetPtrUpKey();
		case data::KeyType::DOWN:
			return mKeyData->GetPtrDownKey();
		case data::KeyType::RIGHT:
			return mKeyData->GetPtrRightKey();
		case data::KeyType::LEFT:
			return mKeyData->GetPtrLeftKey();
		case data::KeyType::RESET:
			return mKeyData->GetPtrResetKey();
		default:
			return nullptr;
		}
	}

	void ScnKeyConfig::KeyUpdating(const uint8_t* keyState)
	{
		for (int i = static_cast<int>(SDL_SCANCODE_A); i <= static_cast<int>(SDL_SCANCODE_UP); i++)// メインで使うであろうキーまで。詳細はSDL_Scancode参照
		{
			SDL_Scancode code = static_cast<SDL_Scancode>(i);

			if (keyState[code])// i番目のキーが押されていれば
			{
				// 予約されているキーの場合、更新できない
				if (code == SDL_SCANCODE_RETURN)
				{
					if (wasPushedEtr) { break; }
					CannotUpdateKey(wasPushedEtr);
					break;
				}
				else if (code == SDL_SCANCODE_Q)
				{
					if (wasPushedQ) { break; }
					CannotUpdateKey(wasPushedQ);
					break;
				}
				else if (code == SDL_SCANCODE_ESCAPE)
				{
					if (wasPushedEsc) { break; }
					CannotUpdateKey(wasPushedEsc);
					break;
				}

				// キー更新
				IsKeyAlreadyUsed(code);					// キーの被りがないか、ある場合はキー更新
				mKSelecting->Setter(code);				// 新しいキーをKeyDataに登録
				wasSelectedCmd = mKSelecting->Getter();	// このフレームで押したキーを記憶（次フレーム以降の連続入力防止）
				mKSelecting = nullptr;					// ポインタ解放
				mKeyUpdating = false;					// アップデート解除
#ifdef DEBUG_SCNKEYCONFIG_H_
				// @todo SDL_GetKeyNameの挙動確認　ASCIIが返っているが、このプログラムファイルはUTF-8。変換できているのか。
				std::cout << SDL_GetScancodeName(wasSelectedCmd) << " key was registered" << std::endl;
				PrintRgsteredKey();						// ここで他のキーの現在値を出力
#endif
				break;
			}
			else // i番目が押されていないとき
			{
				if (code == SDL_SCANCODE_RETURN) { wasPushedEtr = false; }
				else if (code == SDL_SCANCODE_Q) { wasPushedQ = false; }
				else if (code == SDL_SCANCODE_ESCAPE) { wasPushedEsc = false; }
			}
		}
	}

	void ScnKeyConfig::IsKeyAlreadyUsed(SDL_Scancode& code)
	{
		SDL_Scancode UpKey = mKeyData->GetUpKey().Getter();
		SDL_Scancode DownKey = mKeyData->GetDownKey().Getter();
		SDL_Scancode RightKey = mKeyData->GetRightKey().Getter();
		SDL_Scancode LeftKey = mKeyData->GetLeftKey().Getter();
		SDL_Scancode ResetKey = mKeyData->GetResetKey().Getter();

		// もし登録するキーが既に他のコマンドに使用されていたら
		// 他のコマンドのキーにselectingキーを登録
		if (code == UpKey) { 
			mKeyData->GetPtrUpKey()->Setter(mKSelecting->Getter());
		}
		else if (code == DownKey)
		{
			mKeyData->GetPtrDownKey()->Setter(mKSelecting->Getter());
		}
		else if (code == RightKey)
		{
			mKeyData->GetPtrRightKey()->Setter(mKSelecting->Getter());
		}
		else if (code == LeftKey)
		{
			mKeyData->GetPtrLeftKey()->Setter(mKSelecting->Getter());
		}
		else if (code == ResetKey)
		{
			mKeyData->GetPtrResetKey()->Setter(mKSelecting->Getter());
		}
	}

	void ScnKeyConfig::CannotUpdateKey(bool& wasPushed)
	{
		wasPushed = true;
		cannotUpdateKey = true;
		// 引き続きアップデート中となる
	}

	void ScnKeyConfig::NotKeyUpdating(const uint8_t* keyState)
	{
		// 前フレームで押されたキーが、このフレームで押されていなければ
		if (!keyState[wasSelectedCmd])
		{
			wasSelectedCmd = SDL_SCANCODE_UNKNOWN;
		}

		SDL_Scancode UpKey = mKeyData->GetUpKey().Getter();
		SDL_Scancode DownKey = mKeyData->GetDownKey().Getter();
		SDL_Scancode RightKey = mKeyData->GetRightKey().Getter();
		SDL_Scancode LeftKey = mKeyData->GetLeftKey().Getter();
		SDL_Scancode ResetKey = mKeyData->GetResetKey().Getter();

		// KeyDataで登録されているキーが押されたら、
		// かつ前フレームから連続で押されていなければ、
		// KeyTypeSelect状態に移行
		if (keyState[UpKey] && (UpKey != wasSelectedCmd))
		{
			RenewCursor(&UpKey, data::KeyType::UP, "Up");
			ResetKeyCursorColor(&keyCC);
			keyCC.UP = RED;
		}
		else if (keyState[DownKey] && (DownKey != wasSelectedCmd))
		{
			RenewCursor(&DownKey, data::KeyType::DOWN, "Down");
			ResetKeyCursorColor(&keyCC);
			keyCC.DOWN = RED;
		}
		else if (keyState[RightKey] && (RightKey != wasSelectedCmd))
		{
			RenewCursor(&RightKey, data::KeyType::RIGHT, "Right");
			ResetKeyCursorColor(&keyCC);
			keyCC.RIGHT = RED;
		}
		else if (keyState[LeftKey] && (LeftKey != wasSelectedCmd))
		{
			RenewCursor(&LeftKey, data::KeyType::LEFT, "Left");
			ResetKeyCursorColor(&keyCC);
			keyCC.LEFT = RED;
		}
		else if (keyState[ResetKey] && (ResetKey != wasSelectedCmd))
		{
			RenewCursor(&ResetKey, data::KeyType::RESET, "Reset");
			ResetKeyCursorColor(&keyCC);
			keyCC.RESET = RED;
		}
	}

	void ScnKeyConfig::RenewCursor(SDL_Scancode* key, data::KeyType type, std::string cmdName)
	{
		mKTypeCursor = type;
		wasSelectedCmd = *key;

	}

	/* End of Update Functinos */


	/* Generate Update Funtions */


	/* End of Generate Update Functions */

#ifdef DEBUG_SCNKEYCONFIG_H_
	void ScnKeyConfig::PrintRgsteredKey()
	{
		std::cout << "Now Key Config Settings: " << std::endl;
		std::cout << "Up Key: " << SDL_GetKeyName(mKeyData->GetUpKey().Getter()) << std::endl;
		std::cout << "Down Key: " << SDL_GetKeyName(mKeyData->GetDownKey().Getter()) << std::endl;
		std::cout << "Right Key: " << SDL_GetKeyName(mKeyData->GetRightKey().Getter()) << std::endl;
		std::cout << "Left Key: " << SDL_GetKeyName(mKeyData->GetLeftKey().Getter()) << std::endl;
		std::cout << "Reset Key: " << SDL_GetKeyName(mKeyData->GetResetKey().Getter()) << std::endl;
		std::cout << std::endl;
	}
#endif
}
