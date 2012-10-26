#include "CollisionManager.h"
#include <limits>

using namespace phoenix;
using namespace bea;

//////////////////////////////////////////////////////////////////////////////////
// Update
//////////////////////////////////////////////////////////////////////////////////

void CollisionManager::update()
{
	lock();

	tests_count = 0;

	for( std::list< boost::intrusive_ptr<phoenix::Resource> >::iterator i = resourcelist.begin(); i != resourcelist.end(); ++i ){
		if( (*i)->dropped() ) continue;
		for( std::list< boost::intrusive_ptr<phoenix::Resource> >::iterator j = i; j != resourcelist.end(); ++j ){
			if( j == i ) continue;
			if( (*j)->dropped() ) continue; 

			CollisionObjectPtr a = (*i)->grab<CollisionObject>();
			CollisionObjectPtr b = (*j)->grab<CollisionObject>();

			if( filter_function && !filter_function(a,b) ) continue; //filter
			test( a, b );
		}
	}

	for( unsigned int i = 0; i < iterations; ++i ){
		std::vector< CollisionResult > current_list( last_collisions );
		last_collisions.clear();

		for( std::vector< CollisionResult >::iterator it = current_list.begin(); it != current_list.end(); ++it ){
			CollisionResult r = (*it);
			if( r.a->dropped() || r.b->dropped() ) continue;
			test( r.a, r.b );
		}
	}

	unlock();

	last_collisions.clear();
	clean();
}

//////////////////////////////////////////////////////////////////////////////////
// Object Functions
//////////////////////////////////////////////////////////////////////////////////

void CollisionManager::test( boost::intrusive_ptr<CollisionObject> a, boost::intrusive_ptr<CollisionObject> b )
{
	CollisionResult result = test( a->getPolygon(), b->getPolygon(), a->getVelocity() - b->getVelocity() );

	if( result.colliding == true ){
		
		result.a = a;
		result.b = b;
		a->signal( result );

		result.separation = -result.separation;
		result.a = b;
		result.b = a;
		b->signal( result );

		last_collisions.push_back( result );

	}

}

//////////////////////////////////////////////////////////////////////////////////
// Polygon Collision Function.
//////////////////////////////////////////////////////////////////////////////////

const CollisionResult CollisionManager::test( const Polygon& a, const Polygon& b, const Vector2d& v )
{
	tests_count++;

	// A place to store our collision result.
	CollisionResult result;
	result.colliding = true;

	// Do a radius test first.
	auto distance = a.getPosition()-b.getPosition();
	auto combined_radius = a.getRadius() + b.getRadius();
	if ( distance.getMagnitudeSquared() > combined_radius*combined_radius){
		result.colliding = false;
		return result;
	}


	// The minimum distance required to separate the two polygons.
	float mintranslation = std::numeric_limits<float>::max();

	// Loop through both polygon's vertices and test them.
	for( unsigned int i = 0; i < a.getVertexCount() + b.getVertexCount(); ++i )
	{
		// Get the edge, polygons are stored as point clouds, so we have to subtract two points to get an edge.
		Vector2d edge;
		if( i < a.getVertexCount() ) edge = a.getVertex( i ) - a.getVertex( i+1 );
		else edge = b.getVertex( i - a.getVertexCount() ) - b.getVertex( i - a.getVertexCount()+1 );

		// Get a perpendicular ( right-hand ) to the edge.
		edge = Vector2d( -edge.getY(), edge.getX() );
		edge.normalize();

		// Project the two polygons onto the edge.
		float minA,maxA,minB,maxB;
		projectPolygon( edge, a, minA, maxA );
		projectPolygon( edge, b, minB, maxB );

		// Get the distance of separation.
		float distance = intervalDistance(minA, maxA, minB, maxB);

		// If the distance is greater than 0, they aren't overlapping, so let's try a velocity.
		if (distance > 0){
			float velocityProjection = edge * v;

			// Get the projection of object A during the movement
			if (velocityProjection < 0)
				minA += velocityProjection;
			else
				maxA += velocityProjection;

			// Do the same as above, but now with velocity projected.
			float distance = intervalDistance(minA, maxA, minB, maxB);

		}

		// If the distance is greater than 0, they aren't overlapping nor will they collide, so break.
		if (distance > 0){
			result.colliding = false;
			break;
		}

		// Check to see if this is the minimum translation so far.
		if( abs(distance) < mintranslation ){
			mintranslation = abs(distance);
			result.separation = edge;
		}

	}

	// Calculate the minimum translation vector if a collision occured.
	if( result.colliding == true ){
		// multiply it by the minimum translation distance.
		result.separation *= mintranslation;
		//make sure it's facing the right way.
		if (result.separation * (a.getPosition() - b.getPosition()) < 0) result.separation = -result.separation;

	}
	
	return result;
}

//////////////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////////////

void CollisionManager::projectPolygon( const Vector2d& axis, const Polygon& poly, float& min, float& max )
{
	// use the dot product to project points onto the axis.
	float dotProduct = axis * (poly.getPosition() + poly.getVertex(0));
    min = dotProduct;
    max = dotProduct;

	// loop through each point and project it onto the axis.
	// then see if it's less than the min or greater than the max.
	for( unsigned int i = 1; i < poly.getVertexCount(); ++i )
	{
		dotProduct = axis * (poly.getPosition() + poly.getVertex(i));
		if( dotProduct < min ) min = dotProduct;
		if( dotProduct > max ) max = dotProduct;
	}
}

float CollisionManager::intervalDistance(float minA, float maxA, float minB, float maxB) {
    if (minA < minB) {
        return minB - maxA;
    } else {
        return minA - maxB;
    }
}