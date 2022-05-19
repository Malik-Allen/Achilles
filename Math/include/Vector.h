// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include "math_definitions.h"
#include <cmath>
#include <stdexcept>

namespace Kobe
{
	struct Vector2
	{
		float x, y;

		inline explicit Vector2( float s = 0.0f )
		{
			Load( s, s );
		}

		inline Vector2( float _x, float _y )
		{
			Load( _x, _y );
		}

		inline Vector2( const Vector2& v )
		{
			Load( v.x, v.y );
		}

		inline void Load( float _x, float _y )
		{
			x = _x; y = _y;
		}

		inline operator const float* ( ) const
		{
			return static_cast< const float* >( &x );
		}

		inline operator float* ( )
		{
			return static_cast< float* >( &x );
		}

		/// This operator is used to read Vector2 as if it were an array
		inline const float operator [] ( int index ) const
		{
			return *( &x + index );	// Returns a dereferenced address of the first component of this vector plus the index number
		}

		/// This operator is used to write to Vector2 as if it were an array
		inline float& operator [] ( int index )
		{
			return *( &x + index );
		}

		inline Vector2& operator=( const Vector2& v )
		{
			Load( v.x, v.y );
			return *this;
		}

		/// Returns a negative of the Vector2
		inline const Vector2 operator - () const
		{
			return Vector2( -x, -y );
		}

		/// Overloaded addition operator Vector2
		inline const Vector2 operator + ( const Vector2& v ) const
		{
			return Vector2( x + v.x, y + v.y );
		}

		/// Overloaded subtraction operator Vector2
		inline const Vector2 operator - ( const Vector2& v ) const
		{
			return Vector2( x - v.x, y - v.y );
		}

		/// Overloaded addition onto ones self operator
		inline Vector2& operator += ( const Vector2& v )
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		/// Overloaded subtraction onto ones self operator
		inline Vector2& operator -= ( const Vector2& v )
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		/// Overloaded scalar multiplication of Vector2
		inline const Vector2 operator * ( const float s ) const
		{
			return Vector2( s * x, s * y );
		}

		/// Overloaded scalar multiplication of a Vector2 assign it to itself
		inline Vector2& operator *= ( const float s )
		{
			x *= s;
			y *= s;
			return *this;
		}

		/// Overloaded division operator of a Vector2 by a scalar
		inline const Vector2 operator / ( const float s ) const
		{
#ifdef _DEBUG
			if( std::fabs( s ) < VERY_SMALL )
			{	// Check to see if we are dividing to nearly zero
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			float r = 1.0f / s;
			return *this * r;

		}

		/// Overloaded division of Vector2 by a scalar and assignment onto itself
		inline Vector2& operator /= ( const float s )
		{
#ifdef _DEBUG
			if( fabs( s ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			float r = 1.0f / s;
			return *this *= r;
		}

		/// This friend overloaded operator allows the multiplication between a Scalar and Vector2 where a scalar is first
		inline friend Vector2 operator * ( const float s, const Vector2& v )
		{
			return v * s;
		}

		inline float magnitude() const
		{
			return sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) );
		}


		// Returns the unit vector of this Vector2
		inline Vector2 normalized() const
		{
			float a = sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) );
#ifdef _DEBUG
			if( fabs( a ) < VERY_SMALL )
			{	// Checking to see that the magnitude is not zero
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			return Vector2( x / a, y / a );
		}


		// Makes this Vector2 have a magnitude of 1
		inline void Normalize()
		{
			float a = sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) );
#ifdef _DEBUG
			if( fabs( a ) < VERY_SMALL )
			{	// Checking to see that the magnitude is not zero
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			x /= a;
			y /= a;
		}

		// Multiplies two Vector2 component-wise
		inline void Scale( const Vector2& v )
		{
			x *= v.x; y *= v.y;
		}


		// Calculates the dot product between two Vector2
		static float Dot( const Vector2& v1, const Vector2& v2 );

		// Calculates the length between two Vector2
		static float Distance( const Vector2& v1, const Vector2& v2 );

		// Calculates the angle between two Vector2 in radians
		static float Angle( const Vector2& v1, const Vector2& v2 );

		// Linear Interpolation between starting vector2 and end vector2 at rate t
		// When t = 0 returns startPosition. 
		// When t = 1 returns end position. 
		// When t = 0.5 returns midway between start and end positions.
		static Vector2 Lerp( const Vector2& v1, const Vector2& v2, float t );

		// Reflects a Vector2 on a Vector2 defined by its normal
		static Vector2 Reflect( const Vector2& v, const Vector2& n );

	};

	struct Vector3
	{
		float x, y, z;

		inline explicit Vector3( float s = 0.0f )
		{	
			Load( s, s, s );
		}

		inline Vector3( float _x, float _y, float _z )
		{
			Load( _x, _y, _z );
		}

		inline Vector3( const Vector3& v )
		{
			Load( v.x, v.y, v.z );
		}

		inline void Load( float _x, float _y, float _z )
		{
			x = _x; y = _y; z = _z;
		}

		inline operator const float* ( ) const
		{
			return static_cast< const float* >( &x );
		}

		inline operator float* ( )
		{
			return static_cast< float* >( &x );
		}

		/// This overloaded operators allows Vector3 to be read as an array
		inline const float& operator[] ( int index ) const
		{
			return *( &x + index );	// Returns a dereferenced value of the address of the first component in this Vector3
		}

		/// This overloaded operator allows Vector3 to be written as an array
		inline float& operator[] ( int index )
		{
			return *( &x + index );
		}

		inline Vector3& operator=( const Vector3& v )
		{
			Load( v.x, v.y, v.z );
			return *this;
		}

		inline const Vector3 operator - () const
		{
			return Vector3( -x, -y, -z );
		}

		/// Overloaded addition operator Vector3
		inline const Vector3 operator + ( const Vector3& v ) const
		{
			return Vector3( x + v.x, y + v.y, z + v.z );
		}

		/// Overloaded subtraction operator Vector3
		inline const Vector3 operator - ( const Vector3& v ) const
		{
			return Vector3( x - v.x, y - v.y, z - v.z );

		}

		/// Overloaded addition of a Vector3 onto one's self
		inline Vector3& operator += ( const Vector3& v )
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		/// Overloaded subtraction of a Vector3 onto one's self
		inline Vector3& operator -= ( const Vector3& v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		/// Overloaded scalar multiplication Vector3 operator
		inline const Vector3 operator * ( const float s ) const
		{
			return Vector3( s * x, s * y, s * z );
		}

		/// Overloaded scalar multiplication of Vector3 and assign to itself
		inline Vector3& operator *= ( const float s )
		{
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}

		/// Overloaded division operator of Vector3 by a scalar
		inline const Vector3 operator / ( const float s ) const
		{
#ifdef _DEBUG
			if( fabs( s ) < VERY_SMALL )
			{	// Checking to see if we are dividing by zero
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			float r = 1.0f / s;
			return *this * r;
		}

		/// Overloaded division operator of Vector3 by a scalar and assignment onto itself
		inline Vector3& operator /= ( const float s )
		{
#ifdef _DEBUG
			if( fabs( s ) < VERY_SMALL )
			{	// Checking if dividing by zero
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			float r = 1.0f / s;
			return *this *= r;		// Multiplying by the fractional version of s
		}

		/// Current work around to allow scalar vector3 multiplication with the scalar first 
		inline friend Vector3 operator * ( const float s, const Vector3& v )
		{
			return v * s;
		}

		// Returns the length of this Vector3
		inline float magnitude() const
		{
			return sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) + pow( z, 2.0f ) );
		}

		// Returns the unit vector of this Vector3
		inline Vector3 normalized() const
		{
			float a = sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) + pow( z, 2.0f ) );
#ifdef _DEBUG
			if( fabs( a ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			return Vector3( x / a, y / a, z / a );
		}

		// Makes this Vector3 have a magnitude of 1
		inline void Normalize()
		{
			float a = sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) + pow( z, 2.0f ) );
#ifdef _DEBUG
			if( fabs( a ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			x /= a;
			y /= a;
			z /= a;
		}

		// Multiplies two Vector3 component-wise
		inline void Scale( const Vector3& v )
		{
			x *= v.x; y *= v.y; z *= v.z;
		}

		// Calculates the normal Vector3
		static Vector3 normalize( const Vector3& v );

		// Calculates the dot product of two Vector3
		static float Dot( const Vector3& v1, const Vector3& v2 );

		// Calculates the length between two Vector3
		static float Distance( const Vector3& v1, const Vector3& v2 );

		// Calculates the angle between two Vector3
		static float Angle( const Vector3& v1, const Vector3& v2 );

		// Linear Interpolation between starting vector3 and end vector3 at rate t
		// When t = 0 returns startPosition
		// When t = 1 returns end position
		// When t = 0.5 returns midway between start and end positions
		static Vector3 Lerp( const Vector3& v1, const Vector3& v2, float t );

		// Reflects a Vector3 on a Vector3 defined by its normal
		static Vector3 Reflect( const Vector3& v, const Vector3& n );

		// Calculates the cross product between two Vector3
		static Vector3 Cross( const Vector3& a, const Vector3& b );

		// Calculates Projection of one Vector3 onto another Vector3
		static Vector3 Project( const Vector3& u, const Vector3& v );


		// Calculates the perpindicular normal to the passed in Vector3's normal
		// The result can be infinite, so pass through a the x, and y values you would like to work with
		// The passed Vector3 must have a non-zero z-component
		static Vector3 OrthoNormalize( const Vector3& v, float x_, float y_ );

		// Calculates the Spherical Linear Interpolation between the passed starting point and end position at the rate of t
		// If the angle between the two Vector3 is less than 10 degrees than we use linear interpolation
		// When t = 0 returns startPosition 
		// When t = 1 returns end position 
		// When t = 0.5 returns midway between start and end positions
		static Vector3 SLerp( const Vector3& v1, const Vector3& v2, float t );

	};

	struct Vector4 : public Vector3
	{
		float w;	// Inherits x, y, z

		inline explicit Vector4( float s = 0.0f )
		{
			Load( s, s, s, s );
		}

		inline Vector4( float _x, float _y, float _z, float _w )
		{
			Load( _x, _y, _z, _w );
		}

		inline Vector4( const Vector4& v )
		{
			Load( v.x, v.y, v.z, v.w );
		}

		inline Vector4( const Vector3& v )
		{
			Load( v.x, v.y, v.z, 1.0f );
		}

		inline void Load( float _x, float _y, float _z, float _w )
		{
			x = _x; y = _y; z = _z; w = _w;
		}

		inline operator const float* ( ) const
		{
			return static_cast< const float* >( &x );
		}

		inline operator float* ( )
		{
			return static_cast< float* >( &x );
		}

		/// This one allows Vector4 to be read as an array, const meaning it won't be changed
		inline const float& operator [] ( int index ) const
		{
			return *( &x + index );	// Returning a dereferenced address of the first component of Vector4 returns the lvalue at address
		}

		/// This overloaded operator allows Vector4 to written as ana array, hence it is not const
		inline float& operator [] ( int index )
		{
			return *( &x + index );
		}

		inline Vector4& operator=( const Vector4& v )
		{
			x = v.x; y = v.y; z = v.z; w = v.w;
			return *this;
		}

		inline const Vector4 operator - () const
		{
			return Vector4( -x, -y, -z, -w );
		}

		/// Overloaded addition Vector4 operator
		inline const Vector4 operator + ( const Vector4& v ) const
		{
			return Vector4( x + v.x, y + v.y, z + v.z, w + v.w );
		}

		/// Overloaded subtraction Vector4 operator
		inline const Vector4 operator - ( const Vector4& v ) const
		{
			return Vector4( x - v.x, y - v.y, z - v.z, w - v.w );
		}

		/// Overloaded addition Vector4 operator and assignment to itself
		inline Vector4& operator += ( const Vector4& v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}

		/// Overloaded subtraction Vector4 operator and assignment to itself
		inline Vector4& operator -= ( const Vector4& v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}

		/// Overloaded multiplication Vector4 operator by a scalar value
		inline const Vector4 operator * ( const float s ) const
		{
			return Vector4( x * s, y * s, z * s, w * s );
		}

		/// Overloaded multiplication Vector4 by a scalar value and assignment onto itself
		inline Vector4& operator *= ( const float s )
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		/// Overloaded division operator Vector4 by a scalar value
		inline const Vector4 operator / ( const float s ) const
		{
#ifdef _DEBUG
			if( fabs( s ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			float r = 1.0f / s;
			return *this * r;
		}

		/// Overloaded division of Vector4 by scalar and assignment onto itself
		inline Vector4& operator /= ( const float s )
		{
#ifdef _DEBUG
			if( fabs( s ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			float r = 1.0f / s;
			return *this *= r;
		}

		/// Current work around to allow scalar vector4 multiplication with the scalar first 
		inline friend Vector4 operator * ( const float s, const Vector4& v )
		{
			return v * s;
		}

		// Calculates the length of this Vector4
		inline float magnitude() const
		{
			return sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) + pow( z, 2.0f ) + pow( w, 2.0f ) );
		}

		// Returns the unit vector of this Vector4
		inline Vector4 normalized() const
		{
			float a = sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) + pow( z, 2.0f ) + pow( w, 2.0f ) );
#ifdef _DEBUG
			if( fabs( a ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			return Vector4( x / a, y / a, z / a, w / a );
		}

		// Sets the length of this Vector4 to 1
		inline void Normalize()
		{
			float a = sqrt( pow( x, 2.0f ) + pow( y, 2.0f ) + pow( z, 2.0f ) + pow( w, 2.0f ) );
#if _DEBUG
			if( fabs( a ) < VERY_SMALL )
			{
				throw std::runtime_error( "Error! Dividing by nearly zero!" );
			}
#endif
			x /= a;
			y /= a;
			z /= a;
			w /= a;
		}

		// Multiplies two Vector4 component-wise
		inline void Scale( const Vector4& v )
		{
			x *= v.x; y *= v.y; z *= v.z; w *= v.w;
		}

		// Calculates the dot product between two Vector4
		static float Dot( const Vector4& v1, const Vector4& v2 );

		// Calculates the length between two Vector4
		static float Distance( const Vector4& v1, const Vector4& v2 );

		// Linear Interpolation between starting vector4 and end vector4 at rate t
		// When t = 0 returns startPosition
		// When t = 1 returns end position
		// When t = 0.5 returns midway between start and end positions
		static Vector4 Lerp( const Vector4& v1, const Vector4& v2, float t );

		// Calculates Projection of one Vector4 onto another Vector4
		static Vector4 Project( const Vector4& u, const Vector4& v );


	};
}
