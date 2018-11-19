#ifndef GAMEOBJECTRENDERMODULEH
#define GAMEOBJECTRENDERMODULEH

#include <GL/glew.h>
#include "../../../Shaders/GameObjectShader.h"
#include "../../../../GameObject/GameObject.h"
#include <map>
/* GAME OBJECT RENDER MODULE*/

class GORenderModule {

private:
	GameObjectShader* p_shader;

	void prepareModel(const OBJModel* model);
	void doneWithModel();
	void setUpModelMatrix(const GameObject* gameObject);

public:
	GORenderModule(GameObjectShader* shader);
	virtual ~GORenderModule();

	void render(const std::map<const OBJModel*, std::vector<const GameObject*>>& gameObjects);
};

#endif
