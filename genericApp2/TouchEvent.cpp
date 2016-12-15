//
//  TouchEvent.cpp
//  genericApp2
//
//  Created by Arpin, Gregg on 6/24/16.
//  Copyright (c) 2016 Arpin, Gregg. All rights reserved.
//

#include "TouchEvent.h"

TouchPoint::TouchPoint()
{
    set(-1, -1);
}

TouchPoint::TouchPoint(int xp, int yp)
{
    set(xp, yp);
}

int TouchPoint::getX() const
{
    return x;
}

void TouchPoint::setX(int xp)
{
    x = xp;
}

int TouchPoint::getY() const
{
    return y;
}

void TouchPoint::setY(int yp)
{
    y = yp;
}

void TouchPoint::set(int xp, int yp)
{
    setX(xp);
    setY(yp);
}

void TouchPoint::set(const TouchPoint &original)
{
    set(original.getX(), original.getY());
}

TouchEvent::TouchEvent(const TouchPoint *pointsIn, int numPointsIn)
{
    points = NULL;
    setPoints(pointsIn, numPointsIn);
}

TouchEvent::TouchEvent(const TouchEvent &originalEvent)
{
    points = NULL;
    setPoints(originalEvent.points, originalEvent.numPoints);
}

TouchEvent::~TouchEvent()
{
    if (points)
    {
        delete [] points;
    }
}

void TouchEvent::setPoints(const TouchPoint *pointsIn, int numPointsIn)
{
    if (points)
    {
        delete [] points;
    }

    points = new TouchPoint[numPointsIn];
    for(int i = 0; i < numPointsIn; i++)
    {
        points[i].set(pointsIn[i]);
    }
    numPoints = numPointsIn;
}

const TouchPoint &TouchEvent::getPoint(int pointIndex) const
{
    // Exception for pointIndex overflow
    return points[pointIndex];
}

int TouchEvent::getNumPoints() const
{
    return numPoints;
}

TouchEventList::~TouchEventList()
{
    clear();
}

void TouchEventList::appendEvent(const TouchEvent &event)
{
    append(new TouchEvent(event));
}

const TouchEvent *TouchEventList::getCurr() const
{
    // TODO:: Need exception based on size
    return getAt(getNumItems() - 1);
}

const TouchEvent *TouchEventList::getFirst() const
{
    // TODO:: Need exception based on size
    return getAt(0);
}

const TouchEvent *TouchEventList::getPrevious() const
{
    // TODO:: Need exception based on size
    return getAt(getNumItems() - 2);
}

void TouchEventList::clear()
{
    for (int i = 0; i < getNumItems(); i++)
    {
        delete getAt(i);
    }

    List<TouchEvent*>::clear();
}

static void testPoints()
{
    TouchPoint defPoint;
    TouchPoint setPoint(3, 4);

    test_fail_if(defPoint.getX() != -1, "Unexpected value for x in default point");
    test_fail_if(defPoint.getY() != -1, "Unexpected value for y in default point");

    test_fail_if(setPoint.getX() != 3, "Unexpected value for x in set point");
    test_fail_if(setPoint.getY() != 4, "Unexpected value for y in set point");

    setPoint.set(defPoint);

    test_fail_if(setPoint.getX() != -1, "Unexpected value for x in set point");
    test_fail_if(setPoint.getY() != -1, "Unexpected value for y in set point");

    setPoint.set(8, 9);

    test_fail_if(setPoint.getX() != 8, "Unexpected value for x in set point");
    test_fail_if(setPoint.getY() != 9, "Unexpected value for y in set point");

    setPoint.setX(12);
    setPoint.setY(13);

    test_fail_if(setPoint.getX() != 12, "Unexpected value for x in set point");
    test_fail_if(setPoint.getY() != 13, "Unexpected value for y in set point");
}
static void testEvents()
{
    TouchPoint points[3];
    points[0].set(1, 2);
    points[1].set(3, 4);
    points[2].set(5, 6);

    TouchEvent eventA(points, 3);
    TouchEvent eventB(eventA);

    test_fail_if(eventA.getNumPoints() != 3, "Unexpected num points for eventA");
    test_fail_if(eventB.getNumPoints() != 3, "Unexpected num points for eventB");

    test_fail_if(eventA.getPoint(0).getX() != 1, "Unexpected value for X in point 0");
    test_fail_if(eventA.getPoint(0).getY() != 2, "Unexpected value for Y in point 0");

    test_fail_if(eventA.getPoint(1).getX() != 3, "Unexpected value for X in point 1");
    test_fail_if(eventA.getPoint(1).getY() != 4, "Unexpected value for Y in point 1");

    test_fail_if(eventA.getPoint(2).getX() != 5, "Unexpected value for X in point 3");
    test_fail_if(eventA.getPoint(2).getY() != 6, "Unexpected value for Y in point 3");

    test_fail_if(eventB.getPoint(0).getX() != 1, "Unexpected value for X in eventB point 0");
    test_fail_if(eventB.getPoint(0).getY() != 2, "Unexpected value for Y in eventB point 0");

    test_fail_if(eventB.getPoint(1).getX() != 3, "Unexpected value for X in eventB point 1");
    test_fail_if(eventB.getPoint(1).getY() != 4, "Unexpected value for Y in eventB point 1");

    test_fail_if(eventB.getPoint(2).getX() != 5, "Unexpected value for X in eventB point 3");
    test_fail_if(eventB.getPoint(2).getY() != 6, "Unexpected value for Y in eventB point 3");
}

static void testEventList()
{
    TouchPoint points[4] = {TouchPoint(0, 0), TouchPoint(1, 1), TouchPoint(2, 2), TouchPoint(3, 3)};
    TouchEvent events[4] = {TouchEvent(&points[0], 1), TouchEvent(&points[1], 1), TouchEvent(&points[2], 1), TouchEvent(&points[3], 1)};
    TouchEventList list;

    list.appendEvent(events[0]);
    list.appendEvent(events[1]);
    list.appendEvent(events[2]);
    list.appendEvent(events[3]);

    test_fail_if(list.getNumItems() != 4, "Unexpected number of items after populating list");

    const TouchEvent *first = list.getFirst();
    const TouchEvent *curr = list.getCurr();
    const TouchEvent *prev = list.getPrevious();

    test_fail_if(first == NULL, "Got NULL value for first event");
    test_fail_if(curr == NULL, "Got NULL value for curr event");
    test_fail_if(prev == NULL, "Got NULL value for prev event");

    test_fail_if(first->getNumPoints() != 1, "Unexpected num points for first event");
    test_fail_if(curr->getNumPoints() != 1, "Unexpected num points for curr event");
    test_fail_if(prev->getNumPoints() != 1, "Unexpected num points for prev event");

    test_fail_if(first->getPoint(0).getX() != 0, "Unexpected X for first event point");
    test_fail_if(first->getPoint(0).getY() != 0, "Unexpected Y for first event point");

    test_fail_if(curr->getPoint(0).getX() != 3, "Unexpected X for curr event point");
    test_fail_if(curr->getPoint(0).getY() != 3, "Unexpected Y for curr event point");

    test_fail_if(prev->getPoint(0).getX() != 2, "Unexpected X for prev event point");
    test_fail_if(prev->getPoint(0).getY() != 2, "Unexpected Y for prev event point");

    list.clear();

    test_fail_if(list.getNumItems() != 0, "Unexpected number of items after clearing list");

    list.appendEvent(events[0]);
    test_fail_if(list.getNumItems() != 1, "Unexpected number of items after appending single item to list");
}

void TouchEventTestSled::test()
{
    testPoints();
    testEvents();
    testEventList();

    test_pass;
}