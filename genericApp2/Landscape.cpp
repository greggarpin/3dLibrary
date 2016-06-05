#include <stdio.h>
#include "Landscape.h"
#include "RenderContext.h"

#define NUM_VERTICES 1000
#define NUM_DOME_VERTICES 6
Landscape::Landscape() : gridVertices(NUM_VERTICES), cellarVertices(4)
{
    const float stepSize = 2;
    const float range = 500;
    float step = 0;
    const int numSteps = range/(stepSize * 2);
    for(int i = 0; i < numSteps; )
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

    cellarVertices[0].setPosition(-range, 0.1,  range);
    cellarVertices[1].setPosition( range, 0.1,  range);
    cellarVertices[2].setPosition( range, 0.1, -range);
    cellarVertices[3].setPosition(-range, 0.1, -range);
    for(int i = 0 ; i < cellarVertices.getNumVertices(); i++)
    {
        cellarVertices[i].setColor(0.25, 0.25, 0.25);
    }
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

    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, cellarVertices.getStride(), cellarVertices.getPositionPointer());
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, cellarVertices.getStride(), cellarVertices.getColorPointer());

    glDrawElements(GL_TRIANGLE_FAN, cellarVertices.getNumVertices(), GL_UNSIGNED_SHORT, indices);

    glVertexAttribPointer(RenderContext::getContext()->getPositionHandle(), 3, GL_FLOAT, GL_FALSE, gridVertices.getStride(), gridVertices.getPositionPointer());
    glVertexAttribPointer(RenderContext::getContext()->getColorHandle(), 4, GL_FLOAT, GL_FALSE, gridVertices.getStride(), gridVertices.getColorPointer());

    glDrawElements(GL_LINES, gridVertices.getNumVertices(), GL_UNSIGNED_SHORT, indices);
}
