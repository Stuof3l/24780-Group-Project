#include "hero.h"
#include <cmath>

hero::hero() {
	health = 100;
	heroX = 0;
	heroY = 0;
	horizontal_speed = 0;
	vertical_speed = 0;
	on_ground = true;
	png[0].Decode("data/knight-coped.png");
	png[1].Decode("data/knight-coped-fliped.png");
	acceleration = 10;
	maxSpeed = 50;
	flip = false;
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


void hero::update(Level1& l1) {
	FsPollDevice();
	auto key = FsInkey();
	if (FSKEY_D == key)
	{
		horizontal_speed = std::min(horizontal_speed + acceleration, maxSpeed);
		std::cout << "1"<<std::endl;
		
	}
	else if (FSKEY_A == key)
	{
		horizontal_speed = std::max(horizontal_speed - acceleration, -maxSpeed);
		std::cout << "2" << std::endl;
	}
	heroX += horizontal_speed * 0.1;
	flip = horizontal_speed < 0;	
}


