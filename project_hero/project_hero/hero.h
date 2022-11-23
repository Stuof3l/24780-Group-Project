#pragma once
#include "fssimplewindow.h"
#include "Drawer.h"
#include <math.h>
#include "yspng.h"
#include "level1.h"
class hero
{

	int health;
	double heroX, heroY;
	double horizontal_speed, vertical_speed;
	bool on_ground;
public:

	hero();

	double GetX() const;
	double Get_vertical_speed() const;

	void Draw();
	void Set_Position(const double x, const double y);
	void Reset();
	void Set_vertical_speed(const double v);

	void updata(Level1& l1);

};

