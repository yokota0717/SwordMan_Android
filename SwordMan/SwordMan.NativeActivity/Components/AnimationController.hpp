﻿//----------------------------------------------------
//!@file	AnimationController.hpp
//!@brief	アニメーションコントローラーを作成します
//!@author	日比野　真聖
//!@date	2018/9/17
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../Utility/Vec.hpp"
#include "../ResourceManager/ResourceManager.hpp"
#include "../Components/BasicComponents.hpp"
#include "../../Components/ComponentDatas/PlayerData.hpp"
#include "../../Class/TouchInput.hpp"
#include "../Components/Renderer.hpp"
#include "../Utility/Counter.hpp"


namespace ECS
{
	//------------------------------------------------------------------------
	//コンストラクタ
	//デフォルト
	//AnimationController();
	//
	//引数
	//AnimationController( 切り替えるフレーム時間,チップ枚数 );
	//------------------------------------------------------------------------
	class AnimationController : public Component
	{
	public:
		AnimationController()
		{
			widthAnim = AnimationData();
			heightAnim = AnimationData();
			widthAnim.frameTime = 60;
			widthAnim.chipSize = 1;
		}
		AnimationController(const int frameTime, const int chipNumber)
		{
			widthAnim = AnimationData();
			heightAnim = AnimationData();
			widthAnim.frameTime = frameTime;
			widthAnim.chipSize = chipNumber;
			widthAnim.offsetAnim = 0;
		}
		void	Initialize() override
		{
			animationID = 0;
			widthAnim.baseData.isAnimation = true;
			heightAnim.baseData.isAnimation = false;
		}
		void	Update() override
		{
			Animation();
		}
		void	Draw2D() override
		{
			if (entity->HasComponent<ECS::AnimationDraw>())
			{
				entity->GetComponent<ECS::AnimationDraw>().SetIndex(animationID);
			}
		}
	private:
		void	Draw3D() override {}
	private:
		//アニメーションを行う
		void Animation()
		{
			if (!widthAnim.baseData.isAnimation) { return; }
			if (widthAnim.frameTime == 0) { return; }

			int widthCurrentTime = widthAnim.baseData.animationCnt.GetCurrentCount();
			int heightCurrentTime = heightAnim.baseData.animationCnt.GetCurrentCount();
			
			widthAnim.baseData.animationNumber
				= widthCurrentTime / widthAnim.frameTime % widthAnim.chipSize;
			widthAnim.baseData.animationCnt.Add();
			
			//横のみのアニメーション
			animationID = widthAnim.baseData.animationNumber;

			if (!heightAnim.baseData.isAnimation) { return; }
			if (heightAnim.frameTime == 0) { return; }
			heightAnim.baseData.animationNumber
				= heightCurrentTime / heightAnim.frameTime % heightAnim.chipSize;
			heightAnim.baseData.animationCnt.Add();

			//横 + 縦のアニメーション
			animationID = widthAnim.baseData.animationNumber + widthAnim.chipSize * heightAnim.baseData.animationNumber;
		}
	public:
		//横のアニメーションをセット
		//引数1: frameTime フレーム時間
		//引数2: widthChipNumber 横の画像チップ数
		//引数3: offsetAnimNumber アニメーション番号のオフセット
		void SetWidthAnimation(const int frameTime,const int chipSize, const int offsetAnimNumber = 0)
		{
			widthAnim.frameTime = frameTime;
			widthAnim.chipSize = chipSize;
			widthAnim.offsetAnim = offsetAnimNumber;
		}
		//縦のアニメーションをセット
		//引数1: frameTime フレーム時間
		//引数2: widthChipNumber 縦の画像チップ数
		//引数3: offsetAnimNumber アニメーション番号のオフセット
		void SetHeightAnimation(const int frameTime, const int chipSize, const int offsetAnimNumber = 0)
		{
			heightAnim.frameTime = frameTime;
			heightAnim.chipSize = chipSize;
			heightAnim.offsetAnim = offsetAnimNumber;
		}
		//横のアニメーションを行うか設定
		void SetIsWidthAnimation(bool isWidthAnim)
		{
			widthAnim.baseData.isAnimation = isWidthAnim;
			if (!widthAnim.baseData.isAnimation)
			{
				widthAnim = AnimationData();
			}
		}
		//縦のアニメーションを行うか設定
		void SetIsHeightAnimation(bool isHeightAnim)
		{
			heightAnim.baseData.isAnimation = isHeightAnim;
			if (!heightAnim.baseData.isAnimation)
			{
				heightAnim = AnimationData();
			}
		}
	private:
		struct BaseData
		{
			int animationNumber;	//アニメーション番号
			Counter animationCnt;	//アニメーションカウント
			bool isAnimation;		//アニメーションを行うか
		};
		//アニメーションデータ
		struct AnimationData
		{
			BaseData	baseData;	//基本データ
			int frameTime;			//切り替えるフレーム時間
			int chipSize;			//チップサイズ
			int offsetAnim;			//開始するアニメーション番号のオフセット
		};
	private:
		int		animationID;
		AnimationData widthAnim;
		AnimationData heightAnim;
	};
}