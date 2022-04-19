#ifndef SCENE_H_SENTRY
#define SCENE_H_SENTRY

#include "classes.h"
#include "tree.h"
#include "cow.h"
#include "creeper.h"
#include "progressbar.h"
#include <iostream>
#include <memory>
#include <vector>

namespace scene
{
	class Scene;
}

class scene::Scene
{
	std::vector<std::shared_ptr<classes::Object>> objects;
public:
	Scene(short, short, short);
	void run(int);
};

#endif
