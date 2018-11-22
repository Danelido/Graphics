#ifndef SCENEH
#define SCENEH

class Scene
{

public:
	virtual Scene* handleEvent() = 0;
	virtual Scene* update(float dt) = 0;
	virtual Scene* renderImGui() = 0;
	virtual Scene* render() = 0;

	virtual ~Scene(){}


};


#endif
