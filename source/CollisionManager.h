#ifndef __BEA_COLLISIONMANAGER_H__
#define __BEA_COLLISIONMANAGER_H__

#include "Phoenix.h"

namespace bea{

// forward decl for CollisionObject.
class CollisionObject;

//! A structure for storing the result of a collision.
struct CollisionResult{
	bool colliding;
	boost::intrusive_ptr<CollisionObject> a;
	boost::intrusive_ptr<CollisionObject> b;

	//! The minimun translation vector
	phoenix::Vector2d separation;
};


//! Polygon Collision Manager.
/*
	Manages collision objects and tests collisions between polygons.
*/
class CollisionManager
	: public phoenix::ResourceManager
{
public:

	typedef boost::function< bool( boost::intrusive_ptr<CollisionObject> a, boost::intrusive_ptr<CollisionObject> b ) > FilterFunction;

	CollisionManager()
		: ResourceManager(), iterations(2), last_collisions(), tests_count(0), filter_function()
	{
	}

	virtual ~CollisionManager(){
	}


	//! Tests all objects against all others.
	void update();

	//! Tests two collision objects & fires signals.
	void test( boost::intrusive_ptr<CollisionObject> a, boost::intrusive_ptr<CollisionObject> b );

	//! Checks to see if two polygons are overlapping.
	/*!
		Also calculates the minimum translation vector.
		\param v The relative velocity of the two polygons.
	*/
	const CollisionResult test( const phoenix::Polygon& a, const phoenix::Polygon& b, const phoenix::Vector2d& v = phoenix::Vector2d(0,0) );

	void setIterations( const unsigned int its = 2 ){ iterations = its; }
	const unsigned int getIterations(){ return iterations; }

	unsigned int getTestsCount(){ return tests_count; }

	void setFilter( FilterFunction f ) { filter_function = f; };

private:

	//! Projects a polygon onto an axis.
	void projectPolygon( const phoenix::Vector2d& axis, const phoenix::Polygon& poly, float& min, float& max );

	//! Calculates the distance between two intervals.
	float intervalDistance(float minA, float maxA, float minB, float maxB);

	//! List of objects that collided in the last run.
	std::vector<CollisionResult> last_collisions;

	//! How many times to iterate over the last collided collection
	unsigned int iterations;

	//! Number of tests we performed during the last call to update
	unsigned int tests_count;

	//! Function that filters out collision test
	FilterFunction filter_function;

};

}; // namespace bea

#include "CollisionObject.h"

#endif //__BEA_COLLISIONMANAGER_H__