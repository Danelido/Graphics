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

void GORenderModule::render(const std::map<const OBJModel*, std::vector<GameObject*>>& gameObjects)
{
	p_totalVertices = 0;
	for (auto const &map : gameObjects) {
		prepareModel(map.first);

		for (auto& gameObject : map.second) {
			p_totalVertices += map.first->rawMesh()->getNumVertices();
			setUpModelMatrix(gameObject);
			CHECKGLERROR(glDrawElements(GL_TRIANGLES, map.first->rawMesh()->getNumVertices(), GL_UNSIGNED_INT, NULL));
		}

		doneWithModel();
	}
}

const long int & GORenderModule::totalNrOfVertices() const
{
	return this->p_totalVertices;
}

void GORenderModule::prepareModel(const OBJModel * model)
{

	CHECKGLERROR(glBindVertexArray(model->rawMesh()->getVAO()));

	for (size_t i = 0; i < 3; i++) {
		CHECKGLERROR(glEnableVertexAttribArray(static_cast<GLint>(i)));
	}
	if (model->meshTexture()->hasTransparency())
		Renderer::disableBackFaceCulling();

	CHECKGLERROR(glActiveTexture(GL_TEXTURE0));
	CHECKGLERROR(glBindTexture(GL_TEXTURE_2D, model->meshTexture()->getTextureID()));
}

void GORenderModule::doneWithModel()
{
	Renderer::enableBackFaceCulling();
	for (size_t i = 0; i < 3; i++) {
		CHECKGLERROR(glDisableVertexAttribArray(static_cast<GLint>(i)));
	}
	CHECKGLERROR(glBindVertexArray(NULL));
}

void GORenderModule::setUpModelMatrix(GameObject* gameObject)
{
	this->p_shader->setModelMatrix(gameObject->getModelMatrix());
}
