#include "circle_2D.h"


Circle_2D::Circle_2D(float radius, Vector_2D translation)
	: _translation(translation.x(), translation.y())
{
	_radius = radius;
}

float Circle_2D::radius()
{
	return _radius;
}

void Circle_2D::set_radius(float radius)
{
	_radius = radius;
}

Vector_2D Circle_2D::translation()
{
	return _translation;
}

void Circle_2D::set_translation(Vector_2D translation)
{
	_translation = translation;
}

float Circle_2D::intersection_depth(Circle_2D other)
{
	if (_radius == 0.0f || other._radius == 0.0f)
	{
		return 0.0;
	}

	const float distance_to_other = (other.translation() - _translation).magnitude();

	if (distance_to_other < (_radius + other._radius))
	{
		return (_radius + other._radius) - distance_to_other;
	}
	else
	{
		return 0.0f;
	}
}