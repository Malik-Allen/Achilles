// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include "Vector.h"

namespace Kobe
{
	struct Euler;
	struct Quaternion;

	class Matrix4
	{
		// Shoutout and thank you to Scott
		/// These are the default vectors of the eye (camera) according to OpenGL and the right hand rule
		///								+Y   -Z
		///	                             |  /
		///   origin(0.0f,0.0f,0.0f);    | /
		///   up(0.0f,1.0f,0.0f);        |/_____+X
		///   forward(0.0f,0.0f,-1.0f);  /
		///                             /
		///                           +Z
		///

		/// Let's just make sure that all is clear about how this matrix is layed out. 

		/// How a matrix is really layed out is pretty much abitrary but we need to agree
		/// and the world has agreed (except for Microsoft) on the right-hand rule. 
		/// First, the 4x4 matrix is really just an array of 16 numbers.  
		/// We need to think of the array as a matrix in the following way
		/// 4x4 matrix - COLUMN MAJOR - The OpenGL, science, physics, mathematics and engineering way. 
		///	0  4  8  12        [0][0]  [1][0]  [2][0]  [3][0]   
		///	1  5  9  13  (or)  [0][1]  [1][1]  [2][1]  [3][1]
		///	2  6  10 14        [0][2]  [1][2]  [2][2]  [3][2]
		///	3  7  11 15        [0][3]  [1][3]  [2][3]  [3][3]
	
	private:
		float m[16];

	public:
		inline explicit Matrix4( float x0, float x1, float x2, float x3,
			float y0, float y1, float y2, float y3,
			float z0, float z1, float z2, float z3,
			float w0, float w1, float w2, float w3 )
		{
			m[0] = x0;   m[4] = y0;   m[8] = z0; m[12] = w0;
			m[1] = x1;   m[5] = y1;   m[9] = z1; m[13] = w1;
			m[2] = x2;   m[6] = y2;   m[10] = z2; m[14] = w2;
			m[3] = x3;   m[7] = y3;   m[11] = z3; m[15] = w3;
		}

		// Create the unit matrix probably the most common way of initializing a matrix
		inline explicit Matrix4( const float d = 1.0f )
		{
			if( d == 1.0f )
			{
				LoadIdentity();
			}
			else
			{
				m[0] = d;   m[4] = d;   m[8] = d;   m[12] = d;
				m[1] = d;   m[5] = d;   m[9] = d;   m[13] = d;
				m[2] = d;   m[6] = d;   m[10] = d;   m[14] = d;
				m[3] = d;   m[7] = d;   m[11] = d;   m[15] = d;
			}
		}

		// Creates the identity matrix
		inline void LoadIdentity()
		{
			m[0] = 1.0f;   m[4] = 0.0f;   m[8] = 0.0f;   m[12] = 0.0f;
			m[1] = 0.0f;   m[5] = 1.0f;   m[9] = 0.0f;   m[13] = 0.0f;
			m[2] = 0.0f;   m[6] = 0.0f;   m[10] = 1.0f;   m[14] = 0.0f;
			m[3] = 0.0f;   m[7] = 0.0f;   m[11] = 0.0f;   m[15] = 1.0f;
		}

		/// Multiply two 4x4 matricies. 
		inline const Matrix4 operator*( const Matrix4& n ) const
		{
			Matrix4 result;
			for( int i = 0; i < 4; ++i )
			{
				for( int j = 0; j < 4; ++j )
				{
					result[i * 4 + j] = ( m[0 * 4 + j] * n[i * 4 + 0] ) + ( m[1 * 4 + j] * n[i * 4 + 1] ) + ( m[2 * 4 + j] * n[i * 4 + 2] ) + ( m[3 * 4 + j] * n[i * 4 + 3] );
				}
			}
			return result;
		}

		// Multipling a matrix by itself is probably the most commom
		// ("this" is the address of the matrix. "*this" de-references that address
		inline Matrix4& operator*=( const Matrix4& n )
		{
			*this = *this * n;
			return *this;
		}

		// Multiply a Vec4 by this matrix and return the resulting vector
		inline  Vector4 operator* ( const Vector4& v ) const
		{
			float x = v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12];
			float y = v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13];
			float z = v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14];
			float w = v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15];
			return Vector4( x, y, z, w );
		}

		/// Now I can use the structure itself as an array.
		/// When overloading the [] operator you need to declair one
		/// to read the array and one to write to the array. 
		///  Returns a const rvalue
		inline const float operator [] ( int index ) const
		{
			return *( m + index );
		}

		/// This one is for writing to the structure as if where an array 
		/// it returns a lvalue
		inline float& operator [] ( int index )
		{
			return *( m + index );
		}

		inline  Vector3 operator* ( const Vector3& v ) const
		{
			float x = v.x * m[0] + v.y * m[4] + v.z * m[8] + 1.0f * m[12];
			float y = v.x * m[1] + v.y * m[5] + v.z * m[9] + 1.0f * m[13];
			float z = v.x * m[2] + v.y * m[6] + v.z * m[10] + 1.0f * m[14];
			float w = v.x * m[3] + v.y * m[7] + v.z * m[11] + 1.0f * m[15];
			return Vector3( x, y, z );
		}

		/// These allow me convert from type Matrix to const float * without issues
		inline operator float* ( )
		{
			return static_cast< float* >( &m[0] );
		}
		inline operator const float* ( ) const
		{
			return static_cast< const float* >( &m[0] );
		}

		inline Matrix4& operator = ( const Matrix4& m_ )
		{
			this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2]; this->m[3] = m_[3];
			this->m[4] = m_[4]; this->m[5] = m_[5]; this->m[6] = m_[6]; this->m[7] = m_[7];
			this->m[8] = m_[8]; this->m[9] = m_[9]; this->m[10] = m_[10]; this->m[11] = m_[11];
			this->m[12] = m_[12]; this->m[13] = m_[13]; this->m[14] = m_[14]; this->m[15] = m_[15];
			return *this;
		}

		inline Vector4 getColumn( int index ) const
		{
			return Vector4( m[4 * index + 0], m[4 * index + 1], m[4 * index + 2], m[4 * index + 3] );
		}

		inline Vector4 getRow( int index ) const
		{
			return Vector4( m[0 + index], m[4 + index], m[8 + index], m[12 + index] );
		}

		// Rotates this Matrix4 about any of the provided axes, and the given the degrees of rotation
		static Matrix4 Rotate( const float degrees, const float x, const float y, const float z );

		// Rotates this Matrix4 about any of the provided axes as a Vector3, and the given the degrees of rotation
		static Matrix4 Rotate( const float degrees, const Vector3& axis );

		// Preforms uniform scaling, provided the scale factor on each axis
		static Matrix4 Scale( const float x, const float y, const float z );

		// Preforms uniform scaling, provided the scale factor on each axis as a Vector3
		static Matrix4 Scale( const Vector3& scale );

		// Translates this Matrix4 across the given direction components
		static Matrix4 Translate( const float x_, const float y_, const float z_ );

		// Translates this Matrix4 across the given Vector3 direction components
		static Matrix4 Translate( const Vector3& translate_ );

		// Geometric operation of Perspective projection
		static Matrix4 Perspective( const float fovy_, const float aspect_, const float zNear_, const float zFar_ );

		// This creates a transform from Normalized Device Coordinates (NDC) to screen coordinates.
		static Matrix4 ViewportNDC( const int width_, const int height_ );

		// This Orthographic function is a dimension reducing operatorion
		static Matrix4 Orthographic( const float xMin_, const float xMax_,
			const float yMin_, const float yMax_,
			const float zMin_, const float zMax_ );

		static Matrix4 UnOrtho( const Matrix4& ortho );

		// Look At functions creating the eye, look at position and up position of a camera
		static Matrix4 LookAt( const float eyeX_, const float eyeY_, const float eyeZ_,
			const float atX_, const float atY_, const float atZ_,
			const float upX_, const float upY_, const float upZ_ );

		// Look At functions creating the eye, look at position and up position of a camera
		static Matrix4 LookAt( const Vector3& eye, const Vector3& at, const Vector3& up );

		// Switchs the columns with the rows in the Matrix4
		static Matrix4 Transpose( const Matrix4& m );

		// Returns the inverse of a Matrix4
		static Matrix4 Inverse( const Matrix4& m );

		// Converting the representation of a Euler to a Matrix4
		static Matrix4 EulerToMatrix( const Euler& e );

		// Converting a Quaternion into a 4x4 Matrix
		static Matrix4 QuaternionToMatrix( const Quaternion& q );

	};


	class Matrix3
	{
		float m[9];

	public:
		inline explicit Matrix3( float d = 0.0f )
		{
			if( d == 0.0f )
			{
				// When the passed value is zero, lets create an identity matrix
				LoadIdentity();
			}
			else
			{
				m[0] = d;	m[1] = d;	m[2] = d;
				m[3] = d;	m[4] = d;	m[5] = d;
				m[6] = d;	m[7] = d;	m[8] = d;
			}
		}

		inline Matrix3( float xx, float xy, float xz,
			float yx, float yy, float yz,
			float zx, float zy, float zz )
		{
			m[0] = xx;	m[1] = xy; m[2] = xz;
			m[3] = yx; m[4] = yy; m[5] = yz;
			m[6] = zx; m[7] = zy; m[8] = zz;
		}

		inline void Load( float xx, float xy, float xz,
			float yx, float yy, float yz,
			float zx, float zy, float zz )
		{
			m[0] = xx;	m[1] = xy;	m[2] = xz;
			m[3] = yx;	m[4] = yy;	m[5] = yz;
			m[6] = zx;	m[7] = zy;	m[8] = zz;
		}

		// In order to use Matrix3 as an array I requires two overloaded operators
		// One to read Matrix 3 as if it were an array 
		inline const float operator [] ( int index ) const
		{
			return *( m + index );
		}

		// One to write Matrix3 as an array
		inline float& operator [] ( int index )
		{
			return *( m + index );
		}

		// Overloaded assignment operator
		inline Matrix3& operator=( const Matrix3& m_ )
		{
			this->m[0] = m_[0];	this->m[1] = m_[1];	this->m[2] = m_[2];
			this->m[3] = m_[3];	this->m[4] = m_[4];	this->m[5] = m_[5];
			this->m[6] = m_[6];	this->m[7] = m_[7];	this->m[8] = m_[8];
			return *this;
		}

		// Load an identity matrix
		inline void LoadIdentity()
		{
			this->m[0] = 1.0f; this->m[1] = 0.0f; this->m[2] = 0.0f;
			this->m[3] = 0.0f; this->m[4] = 1.0f; this->m[5] = 0.0f;
			this->m[6] = 0.0f; this->m[7] = 0.0f; this->m[8] = 1.0f;
		}

		// Populate an Diagonal Matrix with a value
		inline void LoadIdentity( float d )
		{
			if( d == 0.0f )
				d = 1.0f;

			this->m[0] = d;	this->m[1] = 0.0f;	this->m[2] = 0.0f;
			this->m[3] = 0.0f;	this->m[4] = d;	this->m[5] = 0.0f;
			this->m[6] = 0.0f;	this->m[7] = 0.0f;	this->m[8] = d;
		}

		// Overloaded multiplication operator between two Matrix3 
		inline const Matrix3 operator * ( const Matrix3& n ) const
		{
			Matrix3 result;
			for( int i = 0; i < 3; i++ )
			{
				for( int j = 0; j < 3; j++ )
				{
					result[i * 3 + j] = ( m[0 * 3 + j] * n[i * 3 + 0] ) + ( m[1 * 3 + j] * n[i * 3 + 1] ) + ( m[2 * 3 + j] * n[i * 3 + 2] );
				}
			}
			return result;
		}

		// Overloaded multiplication of two Matrix3 and asignment onto self
		inline Matrix3& operator *= ( const Matrix3& n )
		{
			*this = *this * n;
			return *this;
		}

		// Overloaded multiplication operator between a Vector3 and Matrix3
		inline const Vector3 operator * ( const Vector3& v )
		{
			Vector3 result;
			result.x = m[0] * v.x + m[1] * v.y + m[2] * v.z;
			result.y = m[3] * v.x + m[4] * v.y + m[5] * v.z;
			result.z = m[6] * v.x + m[7] * v.y + m[8] * v.z;
			return result;
		}


		// Extracts the inner 3x3 from a 4x4 matrix
		inline Matrix3& operator = ( const Matrix4& m_ )
		{
			this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2];
			this->m[3] = m_[4]; this->m[4] = m_[5]; this->m[5] = m_[6];
			this->m[6] = m_[8]; this->m[7] = m_[9]; this->m[8] = m_[10];
			return *this;
		}

		// Extracts the inner 3x3 from a 4x4 matrix
		inline Matrix3( const Matrix4& m_ )
		{
			this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2];
			this->m[3] = m_[4]; this->m[4] = m_[5]; this->m[5] = m_[6];
			this->m[6] = m_[8]; this->m[7] = m_[9]; this->m[8] = m_[10];
		}

	};

}
