#pragma once
#include "..\Component.h"
//Dependencies
#include <utility>
#include <vector>
#include <unordered_map>
#include "..\..\data manager\data structures\Model.h"

class GraphicsAPI;
class RenderSystem;
struct CModel : Component
{
	void init() override;

	size_t hash() const;
	bool operator==(const CModel& model) const
	{
		if (hash() == model.hash())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual CModel* clone() { return new CModel(*this); }

	CModel(Model model);
private:
	Model m_model;

	friend GraphicsAPI;
	friend RenderSystem;
};