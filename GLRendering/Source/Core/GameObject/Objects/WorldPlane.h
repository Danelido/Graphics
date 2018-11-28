#ifndef WORLDPLANEH
#define WORLDPLANEH
#include "../GameObject.h"

class WorldPlane : public GameObject
{
public:
	WorldPlane(glm::vec3 position = glm::vec3(0.f));
	virtual ~WorldPlane();

	void update(float dt) override;

};

#endif
