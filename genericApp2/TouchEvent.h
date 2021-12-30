//
//  TouchEvent.h
//  genericApp2
//
//  Created by Arpin, Gregg on 6/24/16.
//  Copyright (c) 2016 Arpin, Gregg. All rights reserved.
//

#ifndef __genericApp2__TouchEvent__
#define __genericApp2__TouchEvent__

#include "List.h"
#include "TestSled.h"

class TouchPoint
{
public:
    TouchPoint()
    {
        set(-1, -1);
    }
    inline TouchPoint(int xp, int yp);

    inline int getX() const;
    inline void setX(int xp);

    inline int getY() const;
    inline void setY(int yp);

    inline void set(int xp, int yp);
    inline void set(const TouchPoint &original);
private:
    int x, y;
};

class TouchEvent
{
public:
    TouchEvent(const TouchPoint *points, int numPoints);
    TouchEvent(const TouchEvent &originalEvent);

    virtual ~TouchEvent();

    inline const TouchPoint &getPoint(int pointIndex) const;
    inline int getNumPoints() const;

private:
    void setPoints(const TouchPoint *points, int numPoints);
    TouchPoint *points;
    int numPoints;
};

class TouchEventList : public List<TouchEvent*>
{
public:
    virtual ~TouchEventList();

    void appendEvent(const TouchEvent &event);
    inline const TouchEvent *getCurr() const;
    inline const TouchEvent *getFirst() const;
    inline const TouchEvent *getPrevious() const;

    // Returns whether a given event is different from the last known event - if not, it can be ignored
    bool isSignificant(const TouchEvent &newEvent) const;

    virtual void clear();
};

class TouchEventTestSled : public TestSled
{
public:
    void test();

};
#endif /* defined(__genericApp2__TouchEvent__) */
