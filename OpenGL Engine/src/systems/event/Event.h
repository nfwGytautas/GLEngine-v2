#pragma once

enum class EventType : size_t
{
	KeyDown,
	KeyUp,
	MouseKeyDown,
	MouseMoved,
	MouseKeyUp,
	MouseScroll,

	EVENT_TYPE_MAX
};

struct Event
{
	virtual~Event() {}

	virtual EventType type() const
	{
		return (EventType) -1;
	}
};