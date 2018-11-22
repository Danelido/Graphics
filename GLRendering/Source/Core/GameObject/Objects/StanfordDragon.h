#ifndef STANFORDDRAGONH
#define STANFORDDRAGONH
#include "../GameObject.h"

class StanfordDragon : public GameObject
{
public:
	StanfordDragon(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), float scale = 1.f);
	virtual ~StanfordDragon();

	void update(float dt) override;

private:



};



#endif
