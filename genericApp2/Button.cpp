#include "Button.h"


Button::Button(float left, float top, float width, float height, const char *imgPath) : Overlay(left, top, width, height, imgPath), listeners(1)
{
}

void Button::press()
{
    for (unsigned int i = 0; i < listeners.getNumItems(); i++)
    {
        listeners.getAt(i)->onButtonPressed(this);
    }
}

void Button::addListener(IButtonListener *listener)
{
    listeners.append(listener);
}
