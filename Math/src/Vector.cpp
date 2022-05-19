// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include "../include/Vector.h"

namespace Kobe
{

	float Vector2::Dot( const Vector2& v1, const Vector2& v2 )
	{
		return ( v1.x * v2.x + v1.y * v2.y );
	}

	float Vector2::Distance( const Vector2& v1, const Vector2& v2 )
	{
		Vector2 result( v1.x - v2.x, v1.y - v2.y );
		return result.magnitude();
	}

	float Vector2::Angle( const Vector2& v1, const Vector2& v2 )
	{
		float a = Dot( v1, v2 );
		float b = sqrt( pow( v1.x, 2.0f ) + pow( v1.y, 2.0f ) ) * sqrt( pow( v2.x, 2.0f ) + pow( v2.y, 2.0f ) );
		return acos( a / b );
	}

	Vector2 Vector2::Lerp( const Vector2& v1, const Vector2& v2, float t )
	{
		return( v1 + t * ( v2 - v1 ) );
	}

	Vector2 Vector2::Reflect( const Vector2& v, const Vector2& n )
	{
		float s = 2.0f * Dot( v, n );
		Vector2 proj = n * s;
		Vector2 result = proj - v;
		return result;
	}

	Vector3 Vector3::normalize( const Vector3& v )
	{
		float a = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) );
#ifdef _DEBUG
		if( fabs( a ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif
		return Vector3( v.x / a, v.y / a, v.z / a );
	}

	float Vector3::Dot( const Vector3& v1, const Vector3& v2 )
	{
		return ( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z );
	}

	float Vector3::Distance( const Vector3& v1, const Vector3& v2 )
	{
		Vector3 result( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
		return result.magnitude();
	}

	float Vector3::Angle( const Vector3& v1, const Vector3& v2 )
	{
		float a = ( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z );	// Dot Product
		float b = sqrt( pow( v1.x, 2.0f ) + pow( v1.y, 2.0f ) + pow( v1.z, 2.0f ) ) * sqrt( pow( v2.x, 2.0f ) + pow( v2.y, 2.0f ) + pow( v2.z, 2.0f ) );	// Multiplying the magnitude of each vector
		return acos( a / b );	// Taking the cos inverse of the dot product / magnitude result to get the angle in radians
	}

	Vector3 Vector3::Lerp( const Vector3& v1, const Vector3& v2, float t )
	{
		return ( v1 + t * ( v2 - v1 ) );
	}

	Vector3 Vector3::Reflect( const Vector3& v, const Vector3& n )
	{
		float s = 2.0f * Dot( v, n );	// Double the dot product to get the scale at the correct resultant angle
		Vector3 proj = n * s;		// Taking the dot product and scaling the normal by it
		Vector3 result = proj - v;	// Finding the resultant vector through difference
		return result;
	}

	Vector3 Vector3::Cross( const Vector3& a, const Vector3& b )
	{
		return Vector3( a.y * b.z - a.z * b.y,
			-( a.x * b.z - a.z * b.x ),
			a.x * b.y - a.y * b.x );
	}

	Vector3 Vector3::Project( const Vector3& u, const Vector3& v )
	{
		float mag = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) );	// Checking the magnitude of the Vector3 to be projected on
#ifdef _DEBUG
		if( fabs( mag ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif
		Vector3 normal( v.x / mag, v.y / mag, v.z / mag );	// Normal of the Vector3 to be projected onto
		float scalar = ( ( Dot( u, normal ) ) / ( mag * mag ) );	// Dividing the Dot Product between the Projected Vector3 and the Normal by the Normal's magnitude squared

		return normal * scalar;	// Returning the normal scaled to the length of the projected Vector3's shadow
	}


	Vector3 Vector3::OrthoNormalize( const Vector3& v, float x_, float y_ )
	{
		float mag = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) );
#ifdef _DEBUG
		if( fabs( mag ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif

		Vector3 normal( v.x / mag, v.y / mag, v.z / mag );
		Vector3 result;
		result.x = x_;
		result.y = y_;

#ifdef _DEBUG
		if( fabs( normal.z ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif
		// The Dot Product of orthogonal(perpindicular) vectors is zero, 
		// So with that in mind you can isolate for any component 
		// While passing through imaginary numbers for the other components 
		// In this case we are isolating for the z-component
		result.z = ( normal.x * x_ + normal.y * y_ ) / -normal.z;	
		return result.normalized();
	}


	Vector3 Vector3::SLerp( const Vector3& v1, const Vector3& v2, float t )
	{
		float a = sqrt( pow( v1.x, 2.0f ) + pow( v1.y, 2.0f ) + pow( v1.z, 2.0f ) );
#ifdef _DEBUG
		if( fabs( a ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif

		Vector3 n1( v1.x / a, v1.y / a, v1.z / a );	// Working with the direction of v1

		float b = sqrt( pow( v2.x, 2.0f ) + pow( v2.y, 2.0f ) + pow( v2.z, 2.0f ) );
#ifdef _DEBUG
		if( fabs( b ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif

		Vector3 n2( v2.x / b, v2.y / b, v2.z / b );	// Working with the direction of v2

		float angle = Angle( n1, n2 );

		if( -n1.x == n2.x && -n1.y == n2.y && -n1.z == n2.z )
		{	// Checking to see if v1 is equal to -v2, in other words are they in the opposite direction
			angle = -180.0f * DEGREES_TO_RADIANS;	// If so, we will just set the angle to 180 degrees to be on the safe side
		}

#ifdef _DEBUG
		if( fabs( angle ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif

		// When the angle between the two points are very small, we will use linear interpolation instead 
		// This is to avoid problems with the division in SLerp 
		// When v1 and v2 are very close the angle is smaller meaning sin(angle) will be small as well 
		// Which will result in division by a very small number, which will give us inaccurate results
		if( angle < ( 10.0f * DEGREES_TO_RADIANS ) )
		{
			return Lerp( v1, v2, t );
		}

		float c = angle * ( 1.0f - t );
		float k1 = sin( c ) / sin( angle );
		float d = angle * t;
		float k2 = sin( d ) / sin( angle );

		Vector3 result = n1 * k1 + n2 * k2;	// Spherical Linear Interpolation Eqxn (multiplication of the direction by the length)

		return result;
	}
	
	float Vector4::Dot( const Vector4& v1, const Vector4& v2 )
	{
		return ( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w );
	}

	float Vector4::Distance( const Vector4& v1, const Vector4& v2 )
	{
		Vector4 result( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w );
		return sqrt( pow( result.x, 2.0f ) + pow( result.y, 2.0f ) + pow( result.z, 2.0f ) + pow( result.w, 2.0f ) );
	}

	Vector4 Vector4::Lerp( const Vector4& v1, const Vector4& v2, float t )
	{
		return ( v1 + t * ( v2 - v1 ) );
	}

	Vector4 Vector4::Project( const Vector4& u, const Vector4& v )
	{
		float mag = sqrt( pow( v.x, 2.0f ) + pow( v.y, 2.0f ) + pow( v.z, 2.0f ) + pow( v.w, 2.0f ) );
#ifdef _DEBUG
		if( fabs( mag ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif
		Vector4 normal( v.x / mag, v.y / mag, v.z / mag, v.w / mag );
		float scalar = Dot( u, v ) / ( mag * mag );
		return normal * scalar;
	}

};