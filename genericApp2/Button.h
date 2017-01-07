#ifndef __genericApp2__Button__
#define __genericApp2__Button__

#include "Overlay.h"
#include "List.h"

class Button;

class IButtonListener
{
public:
    virtual void onButtonPressed(Button *button) const = 0;
};

class Button : public Overlay
{
public:
    Button(float left, float top, float width, float height, const char *imgPath);

    void press();

    void addListener(IButtonListener *listener);

private:
    List<IButtonListener*> listeners;
};

#endif /* defined(__genericApp2__Button__) */
