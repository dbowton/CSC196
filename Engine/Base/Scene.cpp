#include "Scene.h"
#include "Actor.h"
#include <algorithm>

namespace dwb
{
	void Scene::Update(float dt)
	{
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();

		std::for_each(actors.begin(), actors.end(), [dt](auto& actor) {actor->Update(dt); });

		for (size_t i = 0; i < actors.size(); i++)
		{
			for (size_t j = i + 1; j < actors.size(); j++)
			{
				if (actors[i]->destroy || actors[j]->destroy) continue;

				dwb::Vector2 dir = actors[i]->transform.position - actors[j]->transform.position;
				float distance = dir.Length();
				if (distance < actors[i]->GetRadius() + actors[j]->GetRadius())
				{
					actors[i]->onCollision(actors[j].get());
					actors[j]->onCollision(actors[i].get());
				}
			}

		}

		auto iter = actors.begin();
		while (iter != actors.end())
		{
			if ((*iter)->destroy)
			{
				iter = actors.erase(iter);
			}
			else 
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		std::for_each(actors.begin(), actors.end(), [graphics](auto& actor) mutable {actor->Draw(graphics); });
	}

	void Scene::addActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;
		actor->Initialize();

		newActors.push_back(std::move(actor));
	}
	
	void Scene::removeActor(Actor* actor)
	{
		
	}
	
	void Scene::removeAllActors()
	{
		actors.clear();
	}
}