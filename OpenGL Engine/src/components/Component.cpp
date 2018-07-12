#include "Component.h"

ComponentID getUniqueComponentID() noexcept
{
	static ComponentID lastID{ 0u };
	return lastID++;
}
