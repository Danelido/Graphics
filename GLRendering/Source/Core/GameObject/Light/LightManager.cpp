#include "LightManager.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
	for (auto light : p_lights)
	{
		delete light;
	}

	p_lights.clear();
}

void LightManager::addLight(Light * light)
{
	p_lights.emplace_back(light);
}

void LightManager::removeLight(Light * light)
{
	int index = -1;
	for (int i = 0; i < p_lights.size() && index == -1; i++)
	{
		if (light == p_lights.at(i))
		{
			index = i;
		}
	}

	if (index != -1)
	{
		delete p_lights.at(index);
		p_lights.erase(p_lights.begin() + index);
	}

}

const size_t LightManager::getNumberOfLights() const
{
	return p_lights.size();
}

const std::vector<Light*>& LightManager::getLights() const
{
	return p_lights;
}
