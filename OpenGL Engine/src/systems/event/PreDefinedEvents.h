#pragma once
#include "Event.h"
#include "..\..\data manager\InputKeys.h"

struct KeyDownEvent : public Event
{
	Key pressedKey;

	KeyDownEvent(Key mKey);
	virtual ~KeyDownEvent() {}

	static constexpr EventType descriptor = EventType::KeyDown;

	virtual EventType type() const
	{
		return descriptor;
	}
};

struct KeyUpEvent : public Event
{
	Key releasedKey;

	KeyUpEvent(Key mKey);
	virtual ~KeyUpEvent() {}

	static constexpr EventType descriptor = EventType::KeyUp;

	virtual EventType type() const
	{
		return descriptor;
	}
};

struct MouseKeyDownEvent : public Event
{
	MouseKey pressedKey;

	MouseKeyDownEvent(MouseKey mKey);
	virtual ~MouseKeyDownEvent() {}

	static constexpr EventType descriptor = EventType::MouseKeyDown;

	virtual EventType type() const
	{
		return descriptor;
	}
};

struct MouseMovedEvent : public Event
{
	float x;
	float y;

	MouseMovedEvent(float mX, float mY);
	virtual ~MouseMovedEvent() {}

	static constexpr EventType descriptor = EventType::MouseMoved;

	virtual EventType type() const
	{
		return descriptor;
	}
};

struct MouseKeyUpEvent : public Event
{
	MouseKey releasedKey;

	MouseKeyUpEvent(MouseKey mKey);
	virtual ~MouseKeyUpEvent() {}

	static constexpr EventType descriptor = EventType::MouseKeyUp;

	virtual EventType type() const
	{
		return descriptor;
	}
};

struct MouseScrollEvent : public Event
{
	float x;
	float y;

	MouseScrollEvent(float mX, float mY);
	virtual ~MouseScrollEvent() {}

	static constexpr EventType descriptor = EventType::MouseScroll;

	virtual EventType type() const
	{
		return descriptor;
	}
};