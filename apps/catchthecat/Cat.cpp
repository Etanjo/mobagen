#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>

Point2D Cat::Move(CatWorld* world) { 
	std::vector<Point2D> path = generatePath(world);

	return path.back();


}
