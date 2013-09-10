#pragma once

#include <vector>
#include "cinder\Vector.h"

#include "Primitive.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	void InitScene();

protected:

private:
	std::vector<Primitive*> m_primitives;
	
};