#include "Line.h"

using namespace std;

Line::Line(Vector3d _firstPoint, Vector3d _secondPoint, vector<Vector3d> _pointOfViews, Vector3d _color) :
                                                                                 firstPoint(_firstPoint),
                                                                                 secondPoint(_secondPoint),
                                                                                 direction((_secondPoint -
                                                                                            _firstPoint).normalized()),
                                                                                 norm((_secondPoint -
                                                                                         _firstPoint).norm()),
                                                                                 pointOfViews(std::move(_pointOfViews)),
                                                                                 color(_color)
{

}

const Vector3d& Line::getFirstPoint() const
{
    return firstPoint;
}

const Vector3d& Line::getSecondPoint() const
{
    return secondPoint;
}

const Vector3d& Line::getDirection() const
{
    return direction;
}

double Line::getNorm() const
{
    return norm;
}

const std::vector<Vector3d>& Line::getPointOfViews() const
{
    return pointOfViews;
}

const std::vector<int>& Line::getPlanesIndex() const
{
    return planesIndex;
}

const Vector3d& Line::getColor() const
{
    return color;
}
