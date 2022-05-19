// MIT License, Copyright (c) 2022 Malik Allen

#include "../include/Quaternion.h"

namespace Kobe
{

	Euler Quaternion::euler() const
	{
		// Taking the squared value of all components of this quaternion
		float sqw = w * w;
		float sqx = x * x;
		float sqy = y * y;
		float sqz = z * z;

		float sum = sqx + sqy + sqz + sqw;	// Calculating the summation of all 4 components
		float testCase = ( x * y ) + ( z * w );

		float yaw, roll, pitch;

		if( testCase > 0.499f * sum )
		{
			yaw = 2.0f * atan2( x, w );
			roll = PI / 2.0f;
			pitch = 0.0f;
		}
		else if( testCase < -0.499f * sum )
		{
			yaw = -2.0f * atan2( x, w );
			roll = -PI / 2.0f;
			pitch = 0.0f;
		}
		else
		{
			yaw = atan2( ( 2.0f * y * w ) - ( 2.0f * x * z ), sqx - sqy - sqz + sqw );
			roll = asin( 2.0f * testCase / sum );
			pitch = atan2( ( 2.0f * x * w ) - ( 2.0f * y * z ), -sqx + sqy - sqz + sqw );
		}

		return Euler( pitch * RADIANS_TO_DEGREES, yaw * RADIANS_TO_DEGREES, roll * RADIANS_TO_DEGREES );
	}

	Quaternion Quaternion::Inverse( const Quaternion& q )
	{
		Quaternion conj( -q.x, -q.y, -q.z, q.w );

		float mag = sqrt( pow( conj.x, 2.0f ) + pow( conj.y, 2.0f ) + pow( conj.z, 2.0f ) + pow( conj.w, 2.0f ) );

#ifdef _DEBUG
		if( fabs( mag ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif
		return Quaternion( conj.x / mag, conj.y / mag, conj.z / mag, conj.w / mag );
	}

	Quaternion Quaternion::Conjugate( const Quaternion& q )
	{
		return Quaternion( -q.x, -q.y, -q.z, q.w );
	}

	Quaternion Quaternion::Normalize( const Quaternion& q )
	{
		float mag = sqrt( pow( q.x, 2.0f ) + pow( q.y, 2.0f ) + pow( q.z, 2.0f ) + pow( q.w, 2.0f ) );
#ifdef _DEBUG
		if( fabs( mag ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif
		return Quaternion( q.x / mag, q.y / mag, q.z / mag, q.w / mag );
	}

	float Quaternion::Dot( const Quaternion& q1, const Quaternion& q2 )
	{
		return ( q1.x * q2.x ) + ( q1.y * q2.y ) + ( q1.z * q2.z ) + ( q1.w * q2.w );
	}

	float Quaternion::Angle( const Quaternion& q1, const Quaternion& q2 )
	{
		float a = ( q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w );
		float b = sqrt( pow( q1.x, 2.0f ) + pow( q1.y, 2.0f ) + pow( q1.z, 2.0f ) + pow( q1.w, 2.0f ) ) * sqrt( pow( q2.x, 2.0f ) + pow( q2.y, 2.0f ) + pow( q2.z, 2.0f ) + pow( q2.w, 2.0f ) );
		return acos( a / b );
	}

	Vector3 Quaternion::Rotate( const Quaternion& q, const Vector3& v )
	{
		Quaternion q2( v.x, v.y, v.z, 0.0f );
		Quaternion result = q * q2 * Quaternion::Inverse( q );
		return Vector3( result.x, result.y, result.z );

	}

	Quaternion Quaternion::Lerp( const Quaternion& q1, const Quaternion& q2, float t )
	{
		return Quaternion::Normalize( ( ( 1.0f - t ) * q1 ) + ( t * q2 ) );
	}

	Quaternion Quaternion::SLerp( const Quaternion& q1, const Quaternion& q2, float t )
	{
		float a = sqrt( pow( q1.x, 2.0f ) + pow( q1.y, 2.0f ) + pow( q1.z, 2.0f ) + pow( q2.w, 2.0f ) );
#ifdef _DEBUG
		if( fabs( a ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif

		Quaternion n1( q1.x / a, q1.y / a, q1.z / a, q1.w / a );	// Working with the direction of q1

		float b = sqrt( pow( q2.x, 2.0f ) + pow( q2.y, 2.0f ) + pow( q2.z, 2.0f ) + pow( q2.w, 2.0f ) );
#ifdef _DEBUG
		if( fabs( b ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif

		Quaternion n2( q2.x / b, q2.y / b, q2.z / b, q2.w / b );	// Working with the direction of q2

		float angle = Quaternion::Angle( n1, n2 );

		// Checking to see if q1 is equal to -q2, in other words are they in the opposite direction
		if( -n1.x == n2.x && -n1.y == n2.y && -n1.z == n2.z && -n1.w == n2.w )
		{	
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
		// When q1 and q2 are very close the angle is smaller meaning sin(angle) will be small as well 
		// Which will result in division by a very small number, which will give us inaccurate results
		if( angle < ( 10.0f * DEGREES_TO_RADIANS ) )
		{	
			return Quaternion::Lerp( q1, q2, t );
		}

		float c = angle * ( 1.0f - t );
		float k1 = sin( c ) / sin( angle );
		float d = angle * t;
		float k2 = sin( d ) / sin( angle );

		Quaternion result = n1 * k1 + n2 * k2;	// Spherical Linear Interpolation Eqxn (multiplication of the direction by the length)

		return result;
	}

	Quaternion Quaternion::MatrixToQuaternion( const Matrix4& m )
	{
		float t;
		Quaternion q;

		if( m[10] < 0.0f )
		{

			if( m[0] > m[5] )
			{
				t = 1.0f + m[0] - m[5] - m[10];
				q.Load( t, m[1] + m[4], m[8] + m[2], m[6] - m[9] );

			}
			else
			{
				t = 1.0f - m[0] + m[5] - m[10];
				q.Load( m[1] + m[4], t, m[6] + m[9], m[8] - m[2] );
			}
		}
		else
		{

			if( m[0] < -m[5] )
			{
				t = 1.0f - m[0] - m[5] + m[10];
				q.Load( m[8] + m[2], m[6] + m[9], t, m[1] - m[4] );
			}
			else
			{
				t = 1.0f + m[0] + m[5] + m[10];
				q.Load( m[6] - m[9], m[8] - m[2], m[1] - m[4], t );
			}
		}

		q *= ( 0.5f / sqrt( t ) );

		return q;
	}

	Quaternion Quaternion::EulerToQueaternion( const Euler& _e )
	{
		Euler e( _e.x * DEGREES_TO_RADIANS, _e.y * DEGREES_TO_RADIANS, _e.z * DEGREES_TO_RADIANS );

		float c1 = cos( e.y / 2.0f );
		float c2 = cos( e.z / 2.0f );
		float c3 = cos( e.x / 2.0f );
		float s1 = sin( e.y / 2.0f );
		float s2 = sin( e.z / 2.0f );
		float s3 = sin( e.x / 2.0f );

		float c1c2 = c1 * c2;
		float s1s2 = s1 * s2;

		float w = ( c1c2 * c3 ) - ( s1s2 * s3 );
		float x = ( c1c2 * s3 ) + ( s1s2 * c3 );
		float y = ( s1 * c2 * c3 ) + ( c1 * s2 * s3 );
		float z = ( c1 * s2 * c3 ) - ( s1 * c2 * s3 );

		return Quaternion( x, y, z, w );
	}

}