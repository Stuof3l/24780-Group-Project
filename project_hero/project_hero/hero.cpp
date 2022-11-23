#include "hero.h"
hero::hero() {
	health = 100;
	heroX = 0;
	heroY = 0;
	horizontal_speed = 0;
	vertical_speed = 0;
	on_ground = true;
	
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

void Draw() {

}

