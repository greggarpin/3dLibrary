#include <stdio.h>
#include "Landscape.h"
#include "RenderContext.h"

#define NUM_VERTICES 1000
#define NUM_DOME_VERTICES 6
Landscape::Landscape() : gridVertices(NUM_VERTICES), domeVertices(NUM_DOME_VERTICES)
{
    const int max = NUM_VERTICES/8;
    const float stepSize = 0.5;
    const float range = stepSize * 20;
    float step = 0;
    for(int i = 0; i < max; )
    {
        gridVertices[i++].setPosition( step, 0, -range);
        gridVertices[i++].setPosition( step, 0,  range);
        gridVertices[i++].setPosition(-step, 0, -range);
        gridVertices[i++].setPosition(-step, 0,  range);

        gridVertices[i++].setPosition(-range, 0,  step);
        gridVertices[i++].setPosition( range, 0,  step);
        gridVertices[i++].setPosition(-range, 0, -step);
        gridVertices[i++].setPosition( range, 0, -step);
        
        step += stepSize;
    }
    for (int i = 0; i < 4; i++)
    {
        gridVertices[i].setColor(0.5, 0, 0);
    }
    for (int i = 4; i < 8; i++)
    {
        gridVertices[i].setColor(0, 0, 0.5);
    }
    gridVertices[0].setPosition(0, 0, -1000);
    gridVertices[1].setPosition(0, 0,  1000);
    gridVertices[2].setPosition(-1000, 0, 0);
    gridVertices[3].setPosition( 1000, 0, 0);

    domeVertices[0].setPosition(0, range, 0);
    domeVertices[1].setPosition(-range, 0, -range);
    domeVertices[2].setPosition( range, 0, -range);
    domeVertices[3].setPosition( range, 0,  range);
    domeVertices[4].setPosition(-range, 0,  range);
    domeVertices[5].setPosition(-range, 0, -range);
    for(int i = 0; i < NUM_DOME_VERTICES; i++)
    {
        domeVertices[i].setColor(0.5, 0.5, 1.0);
    }

    cellarVertices[5].setPosition(0, -range, 0);
    cellarVertices[4].setPosition(-range, 0, -range);
    cellarVertices[3].setPosition(-range, 0,  range);
    cellarVertices[2].setPosition( range, 0,  range);
    cellarVertices[1].setPosition( range, 0, -range);
    cellarVertices[0].setPosition(-range, 0, -range);
    for(int i = 0 ; i < NUM_DOME_VERTICES; i++)
    {
        cellarVertices[i].setColor(0, 1, 0);
    }
    cellarVertices[0].setColor(0,0,0);
    cellarVertices[1].setColor(1,0,0);
    cellarVertices[2].setColor(0,1,0);
    cellarVertices[3].setColor(1,0,1);
    cellarVertices[4].setColor(1,1,0);
    cellarVertices[5].setColor(1,0,0);
}

const Landscape *Landscape::getLandscape()
{
    static Landscape *landscape = NULL;
    if (landscape == NULL)
    {
        landscape = new Landscape();
    }
    return landscape;
}

void Landscape::render(RenderMode mode) const
{
    static bool firstVisit = true;
    static GLushort indices[NUM_VERTICES];
    if (firstVisit)
    {
        for (int i = 0; i < NUM_VERTICES; i++)
            indices[i] = i;
        firstVisit = false;
    }
/*
    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, domeVertices.getStride(), domeVertices.getPositionPointer());
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, domeVertices.getStride(), domeVertices.getColorPointer());

    glDrawElements(GL_TRIANGLE_FAN, NUM_DOME_VERTICES, GL_UNSIGNED_SHORT, indices);

    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, cellarVertices.getStride(), cellarVertices.getPositionPointer());
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, cellarVertices.getStride(), cellarVertices.getColorPointer());

    glDrawElements(GL_TRIANGLE_FAN, NUM_DOME_VERTICES, GL_UNSIGNED_SHORT, indices);
*/
    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, gridVertices.getStride(), gridVertices.getPositionPointer());
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, gridVertices.getStride(), gridVertices.getColorPointer());

    glDrawElements(GL_LINES, NUM_VERTICES, GL_UNSIGNED_SHORT, indices);
}
