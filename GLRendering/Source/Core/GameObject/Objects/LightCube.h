#ifndef LIGHTCUBEH
#define LIGHTCUBEH
#include "../GameObject.h"

class LightCube : public GameObject
{
public:
	LightCube(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);
	virtual ~LightCube();

	void update(float dt) override;

private:



};



#endif
