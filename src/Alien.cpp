#include "Alien.h"
#include "Game.h"

#include "Sprite.h"
#include "Sound.h"
#include "Collider.h"
#include "Minion.h"
#include "Bullet.h"
#include "PenguinBody.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	hp = 10;
	speed = Vec2();
	Alien::nMinions = nMinions;

	state = RESTING;
	restTime = 1 + (rand()%11)/10;

	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
	associated.AddComponent(new Collider(associated));

	alienCount++;
}

Alien::~Alien() {
	minionArray.clear();

	alienCount--;
}

void Alien::Start() {
	for(int i = 0; i < nMinions; i++) {
		GameObject* go = new GameObject();
		go->AddComponent(new Minion(*go, associated, i*(360/nMinions)));
		minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(go));
	}
}

void Alien::Damage(int damage) {
	hp -= damage;
	if(hp < 1) {
		associated.RequestDelete();
		GameObject* go = new GameObject();
		go->AddComponent(new Sprite(*go, "assets/img/aliendeath.png", 4, 0.15, false, 1.5));
		Sound* sound = new Sound(*go, "assets/audio/boom.wav");
		sound->Play();
		go->AddComponent(sound);
		go->box.SetCenter(associated.box.GetCenter());
		go->rotation = rand()%360;
		Game::GetInstance().GetCurrentState().AddObject(go);
	}
}

void Alien::Update(float dt) {
	associated.rotation -= 60*dt;

	if(PenguinBody::player) {
		if(state == RESTING) {
			restTimer.Update(dt);
			if(restTimer.Get() > restTime) {
				state = MOVING;
				restTimer.Restart();
				restTime = 1 + (rand()%11)/10;
				destination = PenguinBody::player->GetPlayerCenter();
			}
		}
		else if(state == MOVING) {
			Vec2 pos = associated.box.GetCenter();
			Vec2 dest = destination;

			float cos = pos.GetCos(dest);
			if(cos != cos)
				cos = 0;
			float sin = pos.GetSin(dest);
			if(sin != sin)
				sin = 0;
			speed = Vec2(500*cos, 500*sin);
			if((pos.x+speed.x*dt > dest.x && dest.x > pos.x) || (pos.x+speed.x*dt < dest.x && dest.x < pos.x))
				pos.x = dest.x;
			else
				pos.x += speed.x*dt;
			if((pos.y+speed.y*dt > dest.y && dest.y > pos.y) || (pos.y+speed.y*dt < dest.y && dest.y < pos.y))
				pos.y = dest.y;
			else
				pos.y += speed.y*dt;
			associated.box.SetCenter(pos);
			
			if(pos.x == dest.x && pos.y == dest.y) {
				state = RESTING;
				destination = PenguinBody::player->GetPlayerCenter();
				if(!minionArray.empty()) {
					int nearestMinion = 0;
					float minionDS = minionArray[0].lock()->box.GetCenter().GetDS(destination);
					for(unsigned i = 1; i < minionArray.size(); i++) {
						if(minionArray[i].lock()->box.GetCenter().GetDS(destination) < minionDS) {
							nearestMinion = i;
							minionDS = minionArray[i].lock()->box.GetCenter().GetDS(destination);
						}
					}
					Minion* m = (Minion*) minionArray[nearestMinion].lock()->GetComponent("Minion");
					m->Shoot(destination);
				}
			}
		}
	}
}

void Alien::Render() {

}

void Alien::NotifyCollision(GameObject& other) {
	Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
	if(bullet)
		if(!bullet->IsOwner("Alien"))
			Damage(bullet->GetDamage());
}

bool Alien::Is(std::string type) {
	return (type == "Alien");
}
