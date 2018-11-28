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

	long int p_totalVertices;

	void prepareModel(const OBJModel* model);
	void doneWithModel();
	void setUpModelMatrix(GameObject* gameObject);

public:
	GORenderModule(GameObjectShader* shader);
	virtual ~GORenderModule();

	void render(const std::map<const OBJModel*, std::vector<GameObject*>>& gameObjects);

	const long int& totalNrOfVertices() const;
};

#endif
