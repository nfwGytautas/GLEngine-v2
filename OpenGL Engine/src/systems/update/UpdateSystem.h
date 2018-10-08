#pragma once

class UpdateSystem
{
public:
	void update();

	UpdateSystem();
private:
	void postEvents();
	void updatePhysics();
	void updateEntitiesWthModels();
	void updateFrustum();
};