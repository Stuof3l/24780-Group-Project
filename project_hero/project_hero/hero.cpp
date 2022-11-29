#include "hero.h"
#include <cmath>
#include <chrono>
hero::hero() {
	health = 100;
	heroX = 0;
	heroY = 450;
	horizontal_speed = 0;
	vertical_speed = 0;
	on_ground = true;
	png[0].Decode("data/knight-coped.png");
	png[1].Decode("data/knight-coped-fliped.png");
	acceleration = 10;
	maxSpeed = 50;
	flip = false;
	gravity = 9.8;
	jumpCounter = 0;
	h = png[0].hei / 3;
	w = png[0].wid / 3;

}
double hero::GetX() const {
	return heroX;
}
double hero::Get_vertical_speed() const {
	return vertical_speed;
}
void hero::Reset() {
	health = 100;
	heroX = 0;
	heroY = 0;
	horizontal_speed = 0;
	vertical_speed = 0;
	on_ground = true;
}

void hero::Set_Position(const double x, const double y) 
{
	heroX = x;
	heroY = y;
}

void hero::Draw() {
	double x = heroX;
	double y = heroY;
	int h = png[0].hei/3;
	int w = png[0].wid/3;
	if (flip) {
		squareTextureMap(png[1], x, y, h, w);
		}
	else {
		squareTextureMap(png[0], x, y, h, w);
	}
}

void hero::Set_vertical_speed(const double v) {
	vertical_speed = v;
}


void hero::Jump() {
	on_ground = false;
	vertical_speed = 150;
}

void hero::update(Level1& l1, int key) {
	//FsPollDevice();
	//auto key = FsInkey();
	int friction = 1;
	if (FSKEY_D == key)
	{
		horizontal_speed = std::min(horizontal_speed + acceleration, maxSpeed);
		//std::cout << "1"<<std::endl;
		
	}
	else if (FSKEY_A == key)
	{
		horizontal_speed = std::max(horizontal_speed - acceleration, -maxSpeed);
		//std::cout << "2" << std::endl;
	}
	else if (FSKEY_SPACE == key) {
		if (jumpCounter < 2) {
			Jump();
			jumpCounter += 1;
		}
		else {
			if (on_ground) {
				jumpCounter = 0;
			}
		}
	}
	else if (horizontal_speed >= friction && on_ground) {
		horizontal_speed -= friction;
	}
	else if (horizontal_speed <= -friction && on_ground) {
		horizontal_speed += friction;
	}
	
	if (on_ground) {
		vertical_speed = 0;
		heroY = 450;
	}
	else {
		vertical_speed -= gravity;
		heroY -= vertical_speed * 0.1;
		// modify here when obstacle class finished  on_gound = hero.checkObstacle()
		if (heroY > 450) {
			on_ground = true;
		}
	}
	heroX += horizontal_speed * 0.1;
	if (horizontal_speed < 0 && flip == false) {
		flip = true;
	}
	else if ( horizontal_speed> 0 && flip == true) {
		flip = false;
	}
}


std::array<int, 4> hero:: Get_hitbox() {
	std::array<int, 4> hitbox = { heroX, heroY, h,w };
	return hitbox;
}