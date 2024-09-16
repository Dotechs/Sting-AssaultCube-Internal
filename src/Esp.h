#pragma once
#include"Structures.h"
extern struct ImColor;
extern struct ImVec2;
class Esp {
public:
	//static void DrawScalingVerticalBar(float x1, float y1, float x2, float y2, float width, size_t value, float max);
	static void DrawScalingVerticalBar(float x, float y, float width, float height, size_t currentHealth, size_t maxHealth);
	static void DrawEsp();
	static void DrawEnemyWarning(vec2&);
};


