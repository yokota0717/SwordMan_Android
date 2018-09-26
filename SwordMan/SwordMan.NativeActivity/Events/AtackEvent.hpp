﻿//----------------------------------------------------
//!@file	AttackEvent.hpp
//!@brief	当たり判定イベントを作成します
//!@author	日比野　真聖
//!@date	2018/9/16
//----------------------------------------------------
#pragma 
#include "../ECS/ECS.hpp"
#include "../GameController/GameController.h"
#include "../Collision/Collision.hpp"
#include "../Components/BasicComponents.hpp"
#include "../System/System.hpp"
#include "../../Components/HealthCounter.hpp"


namespace Event
{
	class CollisionEvent
	{
	public:
		static void AttackCollisionToEnemy()
		{
			const auto& attackCollisions = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Wepon);
			const auto& enemys = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
			for (const auto& attackCollision : attackCollisions)
			{
				for (const auto& enemy : enemys)
				{
					if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(*attackCollision, *enemy))
					{
						enemy->Destroy();
						break;
					}
				}
			}
		}

		static void PlayerToEnemy()
		{
			const auto& players = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Player);
			const auto& enemys = ECS::EcsSystem().GetManager().GetEntitiesByGroup(ENTITY_GROUP::Enemy);
			for (const auto& player : players)
			{
				for (const auto& enemy : enemys)
				{
					if (Collision::BoxAndBox<ECS::HitBase, ECS::HitBase>(*player, *enemy))
					{
						player->GetComponent<ECS::Think>().ChangeMotion(PlayerData::State::Damage);
						break;
					}
				}
			}
		}
	};
}