#pragma once

class UpdateSystem
{
public:
	void update();

	UpdateSystem();
private:
	void updateEntitiesWithTransformation();
	void updateEntitiesWithInput();
	void updateEntitiesWithPhysics();
	void updateEntitiesWithCameras();
	void updateEntitiesWthModels();
};