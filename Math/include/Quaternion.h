// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include "Euler.h"
#include "Matrix.h"

namespace Kobe
{

	struct Quaternion : public Vector4
	{
		inline explicit Quaternion( float s = 0.0f )
		{
			x = s; y = s; z = s;
			( s == 0.0f ) ? w = 1.0f : w = s;
		}

		inline Quaternion( float x_, float y_, float z_, float w_ )
		{
			Load( x_, y_, z_, w_ );
		}

		inline void Load( float x_, float y_, float z_, float w_ )
		{
			x = x_; y = y_; z = z_; w = w_;
		}

		inline Quaternion( const Vector3& axis, float degrees )
		{
			degrees *= DEGREES_TO_RADIANS;
			w = cos( degrees / 2.0f );
			x = axis.x * sin( degrees / 2.0f );
			y = axis.y * sin( degrees / 2.0f );
			z = axis.z * sin( degrees / 2.0f );
		}

		inline Quaternion( const Quaternion& q )
		{
			x = q.x; y = q.y; z = q.z; w = q.w;
		}

		inline Quaternion& operator=( const Quaternion& q )
		{
			x = q.x; y = q.y; z = q.z; w = q.w;
			return *this;
		}

		// **WIP:: Preforms the addition between two quaternions
		inline const Quaternion operator + ( const Quaternion& q ) const
		{
			return Quaternion( x + q.x, y + q.y, z + q.z, w + q.w );
		}

		inline const Quaternion operator * ( const Quaternion& q ) const
		{
			Vector3 v1( x, y, z );
			Vector3 v2( q.x, q.y, q.z );

			float w_ = ( w * q.w ) - ( x * q.x + y * q.y + z * q.z );
			Vector3 v = ( w * v2 ) + ( q.w * v1 ) + ( Vector3::Cross( v1, v2 ) );

			return Quaternion( v.x, v.y, v.z, w_ );
		}

		inline const Quaternion operator * ( const float t ) const
		{
			return Quaternion( x * t, y * t, z * t, w * t );
		}

		inline friend Quaternion operator * ( const float t, const Quaternion& q )
		{
			return q * t;
		}

		inline Quaternion& operator *= ( const float t )
		{
			x *= t;
			y *= t;
			z *= t;
			w *= t;
			return *this;
		}

		inline Quaternion conjugated() const
		{
			return Quaternion( -x, -y, -z, w );
		}

		// Returns the unit Quaternion of this Quaternion
		inline Quaternion normalized()
		{
			float mag = sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) + pow( z, 2.0f ) + pow( w, 2.0f ) );
#ifdef _DEBUG
			if( fabs( mag ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			x /= mag;
			y /= mag;
			z /= mag;
			w /= mag;

			return *this;
		}

		// Returns the representation of this Quaternion as Euler Angles
		Euler euler() const;

		// Calculates the normalized conjugate of a Quaternion
		static Quaternion Inverse( const Quaternion& q );

		// Returns the conjugate of the passed Quaternion
		static Quaternion Conjugate( const Quaternion& q );

		// Calculates the unit quaternion
		static Quaternion Normalize( const Quaternion& q );

		// Calculates the dot product between two quaternions
		static float Dot( const Quaternion& q1, const Quaternion& q2 );

		// **WIP::Calculates the angle between two Quaternions
		static float Angle( const Quaternion& q1, const Quaternion& q2 );

		// Calculates the rotation of a Vector3 using the passed Quaternion
		static Vector3 Rotate( const Quaternion& q, const Vector3& v );

		// **WIP::Linear Interpolation between starting Quaternion and end Quaternion at rate t
		// When t = 0 returns startPosition
		// When t = 1 returns end position
		// When t = 0.5 returns midway between start and end positions
		static Quaternion Lerp( const Quaternion& q1, const Quaternion& q2, float t );

		// **WIP:: Calculates the Spherical Linear Interpolation between the passed starting point and end position at the rate of t
		// If the angle between the two Vector3 is less than 10 degrees than we use linear interpolation
		// When t = 0 returns startPosition 
		// When t = 1 returns end position 
		// When t = 0.5 returns midway between start and end positions
		static Quaternion SLerp( const Quaternion& q1, const Quaternion& q2, float t );


		// Converting a Matrix into a Quaternion
		static Quaternion MatrixToQuaternion( const Matrix4& m );

		// Converting an Euler(Y, Z, X) into a Quaternion
		static Quaternion EulerToQueaternion( const Euler& _e );

	};

}