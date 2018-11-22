#ifndef CUBEH
#define CUBEH
#include "../GameObject.h"

class Cube : public GameObject
{
public:
	Cube(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);
	virtual ~Cube();

	void update(float dt) override;

private:



};



#endif
