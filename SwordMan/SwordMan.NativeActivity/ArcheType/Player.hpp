﻿//----------------------------------------------------
//!@file	Player.hpp
//!@brief	プレイヤーの原型を作成します
//!@author	日比野　真聖
//!@date	2018/9/14
//----------------------------------------------------
#pragma once
#include "../ECS/ECS.hpp"
#include "../Components/Collider.hpp"
#include "../Components/Renderer.hpp"
#include "../GameController/GameController.h"
#include "../Components/Jump.hpp"
#include "../Components/Think.hpp"
#include "../Components/Behavior.hpp"
#include "../Components/AnimationController.hpp"
#include "../Components/EntityHealthState.hpp"
#include "../Components/CorrectionPosition.hpp"
#include "../Components/OutsideOfScreen.hpp"
#include "../Components/SideHitBase.hpp"
#include "../Components/PlayerDash.hpp"
#include "../Components/PlayerAddComponent.hpp"


namespace ECS
{
	class PlayerArcheType : public IArcheType<const Vec2&,const Vec2&>
	{
	public:
		ECS::Entity* operator()(const Vec2& pos,const Vec2& size)
		{
			ECS::Entity*	entity = &ECS::EcsSystem::GetManager().AddEntityAddTag("player");
			entity->AddComponent<Position>(pos);
			entity->AddComponent<Rotation>();
			entity->AddComponent<HitBase>(size.x, size.y).SetOffset(16.0f, 0.0f);
			entity->AddComponent<Physics>().SetGravity(9.8f / 60 / 60 * 32 * 5);
			entity->AddComponent<EntityHealthState>(3);
			entity->AddComponent<Direction>();
			entity->AddComponent<AnimationDraw>("player");
			entity->AddComponent<AnimationController>(20, 2);
			entity->AddComponent<PlayerDash>().SetIsMove(true);
			entity->GetComponent<PlayerDash>().SetAddSpeed(0.02f);
			entity->GetComponent<PlayerDash>().SetTargetPos(Vec2(300,pos.y));
			entity->AddComponent<PlayerAddComponent>();
			entity->AddGroup(ENTITY_GROUP::Player);
			return entity;
		}
	};
}