#include "PreDefinedEvents.h"

KeyDownEvent::KeyDownEvent(Key mKey)
	: pressedKey(mKey)
{
}

KeyUpEvent::KeyUpEvent(Key mKey)
	: releasedKey(mKey)
{
}

MouseKeyDownEvent::MouseKeyDownEvent(MouseKey mKey)
	: pressedKey(mKey)
{
}

MouseKeyUpEvent::MouseKeyUpEvent(MouseKey mKey)
	: releasedKey(mKey)
{
}

MouseMovedEvent::MouseMovedEvent(float mX, float mY)
	: x(mX), y(mY)
{
}

MouseScrollEvent::MouseScrollEvent(float mX, float mY)
	: x(mX), y(mY)
{
}
