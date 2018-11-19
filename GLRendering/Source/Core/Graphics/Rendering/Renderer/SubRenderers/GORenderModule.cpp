#include "GORenderModule.h"
#include "../Renderer.h"
#include "../../../../Utils/CreateMatrix.h"
#include "../../../../Utils/GLErrorCheck.h"

GORenderModule::GORenderModule(GameObjectShader* shader)
{
	this->p_shader = shader;
}

GORenderModule::~GORenderModule()
{

}

void GORenderModule::render(const std::map<const OBJModel*, std::vector<const GameObject*>>& gameObjects)
{

	for (auto const &map : gameObjects) {
		prepareModel(map.first);

		for (auto& gameObject : map.second) {
			setUpModelMatrix(gameObject);
			CHECKGLERROR(glDrawElements(GL_TRIANGLES, map.first->rawMesh()->getNumVertices(), GL_UNSIGNED_INT, NULL));
		}

		doneWithModel();
	}
}

void GORenderModule::prepareModel(const OBJModel * model)
{

	CHECKGLERROR(glBindVertexArray(model->rawMesh()->getVAO()));

	for (size_t i = 0; i < 3; i++) {
		CHECKGLERROR(glEnableVertexAttribArray(i));
	}
	if (model->meshTexture()->hasTransparency())
		Renderer::disableCulling();

	CHECKGLERROR(glActiveTexture(GL_TEXTURE0));
	CHECKGLERROR(glBindTexture(GL_TEXTURE_2D, model->meshTexture()->getTextureID()));
}

void GORenderModule::doneWithModel()
{
	Renderer::enableCulling();
	for (size_t i = 0; i < 3; i++) {
		CHECKGLERROR(glDisableVertexAttribArray(i));
	}
	CHECKGLERROR(glBindVertexArray(NULL));
}

void GORenderModule::setUpModelMatrix(const GameObject* gameObject)
{
	glm::mat4 modelMatrix = CreateMatrix::modelMatrix(
		gameObject->getPosition(),
		gameObject->getRotation(),
		gameObject->getScale()
	);

	this->p_shader->setModelMatrix(modelMatrix);
}
