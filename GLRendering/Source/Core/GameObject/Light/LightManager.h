#ifndef LIGHTMANAGERH
#define LIGHTMANAGERH
#include "Light.h"
#include <vector>

class LightManager
{
public:
	LightManager();
	virtual ~LightManager();

	void addLight(Light* light);
	void removeLight(Light* light);

	const size_t getNumberOfLights() const;
	const std::vector<Light*>& getLights() const;

private:
	std::vector<Light*> p_lights;

};


#endif
