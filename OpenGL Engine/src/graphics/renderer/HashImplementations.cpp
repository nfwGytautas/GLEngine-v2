#include "HashImplementations.h"

#include "..\renderables\Model.h"

size_t KeyHasher::operator()(const Model& model) const
{
	return model.GetHash();
}