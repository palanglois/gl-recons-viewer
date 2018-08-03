#ifndef RANSAC_ON_LINES_CPP_LINE_H
#define RANSAC_ON_LINES_CPP_LINE_H

#include <vector>
#include <Eigen/Core>

using namespace Eigen;

class Line
{
public:
    Line(Vector3d _firstPoint = Vector3d(0., 0., 0.), Vector3d _secondPoint = Vector3d(0., 0., 0.),
         std::vector<Vector3d> _pointOfViews=std::vector<Vector3d>(0));

    /* Getters */
    const Vector3d& getFirstPoint() const;
    const Vector3d& getSecondPoint() const;
    const std::vector<Vector3d>& getPointOfViews() const;
    const Vector3d& getDirection() const;
    double getNorm() const;
    const std::vector<int>& getPlanesIndex() const;

private:
    const Vector3d firstPoint;
    const Vector3d secondPoint;
    const Vector3d direction;
    const double norm;
    const std::vector<Vector3d> pointOfViews;
    std::vector<int> planesIndex;
};

#endif //RANSAC_ON_LINES_CPP_LINE_H
