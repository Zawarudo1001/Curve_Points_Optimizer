#pragma once
#include "2dTypes.h"


float length(Vec2D const& v);

float dot(Vec2D const& a, Vec2D const& b);

Vec2D norm(Vec2D &v);

float length(Point2d const& p1, Point2d const& p2);

Vec3D FindCenRad(Point2d &a, Point2d &b, Point2d &c);

Vec2D FindPerp(Point2d &A, Point2d &B, Point2d &C);

bool operator<(const Point2d &a, const Point2d &b);