// MIT License, Copyright (c) 2022 Malik Allen

#include "../include/Matrix.h"
#include "../include/Quaternion.h"

namespace Kobe
{

	Matrix4 Matrix4::Rotate( float degrees, float x, float y, float z )
	{
		float cosAngle, sinAngle, cosm;
		Vector3 rotateAxis( x, y, z );
		rotateAxis = Vector3::normalize( rotateAxis );
		degrees *= DEGREES_TO_RADIANS;				// We do out math using radians
		cosAngle = cos( degrees );
		sinAngle = sin( degrees );
		cosm = ( 1.0f - cosAngle );

		Matrix4 m;

		/// We obtain the below rotation matrix via concatination (combining matrices), 
		/// Using the 3 independent axis rotation matrices ofcourse!

		m[0] = ( rotateAxis.x * rotateAxis.x * cosm ) + cosAngle;
		m[1] = ( rotateAxis.x * rotateAxis.y * cosm ) + ( rotateAxis.z * sinAngle );
		m[2] = ( rotateAxis.x * rotateAxis.z * cosm ) - ( rotateAxis.y * sinAngle );
		m[3] = 0.0;

		m[4] = ( rotateAxis.y * rotateAxis.x * cosm ) - ( rotateAxis.z * sinAngle );
		m[5] = ( rotateAxis.y * rotateAxis.y * cosm ) + cosAngle;
		m[6] = ( rotateAxis.y * rotateAxis.z * cosm ) + ( rotateAxis.x * sinAngle );
		m[7] = 0.0;

		m[8] = ( rotateAxis.z * rotateAxis.x * cosm ) + ( rotateAxis.y * sinAngle );
		m[9] = ( rotateAxis.z * rotateAxis.y * cosm ) - ( rotateAxis.x * sinAngle );
		m[10] = ( rotateAxis.z * rotateAxis.z * cosm ) + cosAngle;
		m[11] = 0.0;

		m[12] = 0.0;
		m[13] = 0.0;
		m[14] = 0.0;
		m[15] = 1.0;

		return m;
	}

	Matrix4 Matrix4::Rotate( const float degrees, const Vector3& axis )
	{
		return Matrix4::Rotate( degrees, axis.x, axis.y, axis.z );
	}

	Matrix4 Matrix4::Scale( float x, float y, float z )
	{
		return Matrix4( x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f );
	}

	Matrix4 Matrix4::Scale( const Vector3& scale )
	{
		return Matrix4::Scale( scale.x, scale.y, scale.z );
	}

	Matrix4 Matrix4::Perspective( const float fovy, const float aspect, const float zNear, const float zFar )
	{
		// Aspect ratio is calculated by divindg the height of the screen by its width in pixels
		// Fov along the y axis is usually 90 degrees for humans
		// zNear defines the position of out near plane and zFar the position of the far plane.

		float cot = 1.0f / tan( fovy * 0.5f * DEGREES_TO_RADIANS );

		// Keep in mind we are using the right-hand rule
		// We are using the Matrix to create the View Frustum with a Perspective Projection
		// To be then projected on the Normalized Device Coordinates becase that is what is used by OpenGL
		Matrix4 result( cot / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, cot, 0.0f, 0.0f,
			0.0f, 0.0f, ( zNear + zFar ) / ( zNear - zFar ), -1.0,
			0.0, 0.0, ( 2.0f * zNear * zFar ) / ( zNear - zFar ), 0.0 );
		return result;
	}


	/// This creates a transform from Normalized Device Coordinates (NDC) to 
	/// screen coordinates. OpenGL uses NDC as	(Left-Hand Rule)		 
	///	              ------------------------------
	///	             /|                           /|
	///	            / |                          / |
	///	           /  |                         /  |
	///	          /   |                        /   |
	///	         /    |                       /    |
	///	        /     |                      /     |
	///	       /      |                     /      |
	///	      /       |                    /       |
	///	     /        |                   /        |
	///	    /         |                  /         |
	///	   /----------------------------/ (1.0,1.0)|
	///	   |          |                 |          |
	///	   |          |                 |          |      +Y
	///	   |          |                 |          | 
	///	   |          |-----------------|----------|      ^
	///	   |         /                  |         /       |
	///	   |        /                   |        /        |       -Z
	///	   |       /                    |       /         |
	///	   |      /                     |      /          |     /
	///	   |     /                      |     /           |    /
	///	   |    /                       |    /            |   /
	///	   |   /                        |   /             |  /
	///	   |  /                         |  /              | /
	///	   | /                          | /               |/
	///	   |/ (-1.0,-1.0)               |/                ----------------> +X
	///	   ------------------------------
	Matrix4 Matrix4::ViewportNDC( int width_, int height_ )
	{
		// When using the NDC the z that we use will not ever be negative, it will be between 0 and 1, anything outside that will not be drawn.

		float minZ = 0.0f;
		float maxZ = 1.0f;

		Matrix4 m;
		Matrix4 m1 = Matrix4::Scale( 1.0f, -1.0f, 1.0f );
		Matrix4 m2 = Matrix4::Scale( float( width_ ) / 2.0f, float( height_ ) / 2.0f, maxZ - minZ );
		Matrix4 m3 = Matrix4::Translate( float( width_ ) / 2.0f, float( height_ ) / 2.0f, minZ );
		m = m3 * m2 * m1;

		/***
		m[0] = float(width_)/2.0f;
		m[5] = -float(height_)/2.0f;
		m[10] =  maxZ - minZ;
		m[12] = float(width_)/2.0f;
		m[13] = float(height_)/2.0f;
		m[14] = minZ;
		m[15] = 1.0f; ***/

		return m;
	}

	Matrix4 Matrix4::Orthographic( float xMin_, float xMax_, float yMin_, float yMax_, float zMin_, float zMax_ )
	{

		Matrix4 m;

		Matrix4 m1 = Matrix4::Scale( 2.0f / ( xMax_ - xMin_ ), 2.0f / ( yMax_ - yMin_ ), -2.0f / ( zMax_ - zMin_ ) );
		Matrix4 m2 = Matrix4::Translate( -( xMax_ + xMin_ ) / ( xMax_ - xMin_ ), -( yMax_ + yMin_ ) / ( yMax_ - yMin_ ), -( zMax_ + zMin_ ) / ( zMax_ - zMin_ ) );
		m = m2 * m1;
		// Above the Matrix we use to obtain the below Matrix
		// Below is the Matrix to define orthographic projection
		// Keeping parallel lines parallel and maintain th size of far and near things the same

		/***
		m[0] = 2.0f / (xMax - xMin);
		m[5] = 2.0f / (yMax - yMin);
		m[10] = -2.0f / (zMax - zMin);
		m[12] = -((xMax + xMin) / (xMax - xMin));
		m[13] = -((yMax + yMin) / (yMax - yMin));
		m[14] = -((zMax + zMin) / (zMax - zMin));
		m[15] = 1.0f;
		***/
		return m;
	}

	Matrix4 Matrix4::UnOrtho( const Matrix4& ortho )
	{
		Matrix4 m;
		m[0] = 1.0f / ortho[0];
		m[5] = 1.0f / ortho[5];
		m[10] = 1.0f / ortho[10];
		m[12] = -ortho[12] * m[0];
		m[13] = -ortho[13] * m[5];
		m[14] = -ortho[14] * m[10];
		m[15] = 1.0f;
		return m;
	}

	Matrix4 Matrix4::Translate( float x_, float y_, float z_ )
	{
		return Matrix4( 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x_, y_, z_, 1.0f );
	}

	Matrix4 Matrix4::Translate( const Vector3& translate_ )
	{
		return Matrix4::Translate( translate_.x, translate_.y, translate_.z );
	}

	Matrix4 Matrix4::LookAt( float eyeX, float eyeY, float eyeZ,
		float atX, float atY, float atZ,
		float upX, float upY, float upZ )
	{

		Vector3 at( atX, atY, atZ );
		Vector3 up( upX, upY, upZ );
		Vector3 eye( eyeX, eyeY, eyeZ );

		Matrix4 result;

		Vector3 forward = Vector3::normalize( at - eye );					// Creating the direction vector which is the -eyeDirec currently
		up = Vector3::normalize( up );										// Working with direction of the up vector no need for the magnitude
		Vector3 side = Vector3::normalize( Vector3::Cross( forward, up ) );		// Creating the side of the camera
		up = Vector3::Cross( side, forward );								// Then using the side and forward vector's we can make the new up direction


		// Below is the Matrix to used represnt the Eye(LookAt)
		result[0] = side.x;
		result[1] = side.y;
		result[2] = side.z;
		result[3] = 0.0;

		result[4] = up.x;
		result[5] = up.y;
		result[6] = up.z;
		result[7] = 0.0;

		result[8] = -forward.x;
		result[9] = -forward.y;
		result[10] = -forward.z;
		result[11] = 0.0;

		result[12] = -Vector3::Dot( side, eye );
		result[13] = -Vector3::Dot( up, eye );
		result[14] = Vector3::Dot( forward, eye );
		result[15] = 1.0;

		return result;
	}

	Matrix4 Matrix4::LookAt( const Vector3& eye, const Vector3& at, const Vector3& up )
	{
		return LookAt( eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z );
	}

	Matrix4 Matrix4::Transpose( const Matrix4& m )
	{
		return Matrix4( m[0], m[4], m[8], m[12],
			m[1], m[5], m[9], m[13],
			m[2], m[6], m[10], m[14],
			m[3], m[7], m[11], m[15] );

	}

	Matrix4 Matrix4::Inverse( const Matrix4& m )
	{
		Matrix4 inverseM;
		float determinate;

		inverseM[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
		inverseM[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
		inverseM[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
		inverseM[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
		inverseM[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
		inverseM[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
		inverseM[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
		inverseM[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
		inverseM[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
		inverseM[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
		inverseM[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
		inverseM[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
		inverseM[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
		inverseM[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
		inverseM[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
		inverseM[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

		determinate = m[0] * inverseM[0] + m[1] * inverseM[4] + m[2] * inverseM[8] + m[3] * inverseM[12];

		// When the determinant is less than zero, it means the Matrix has been reflected
		// When the determninant is zero then this Matrix has been projected, meaning that a column or row is filled with zeroes
		// When the determinant is one than this Matrix is an identity Matrix
		// With any other determinant result, this inverse matrix will reverse a rotation, transformation, scale, etcimpacting said matrix 
#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if( fabs( determinate ) < VERY_SMALL )
		{
			throw std::runtime_error( "Error! Dividing by nearly zero!" );
		}
#endif
		determinate = 1.0f / determinate;
		for( int i = 0; i < 16; i++ )
		{
			inverseM[i] *= determinate;
		}
		return inverseM;
	}

	Matrix4 Matrix4::EulerToMatrix( const Euler& e )
	{
		/// The order will be roll-yaw-pitch

		float cr, cp, cy, sr, sp, sy;

		cr = cos( e.z * DEGREES_TO_RADIANS );
		cp = cos( e.x * DEGREES_TO_RADIANS );
		cy = cos( e.y * DEGREES_TO_RADIANS );

		sr = sin( e.z * DEGREES_TO_RADIANS );
		sp = sin( e.x * DEGREES_TO_RADIANS );
		sy = sin( e.y * DEGREES_TO_RADIANS );

		Matrix4 m;

		// This is the Matrix used to covert a Euler into a Matirx
		// We do this because we want to avoid gimble lock asociated with Euler angles
		// We can show Eulers but work with Matrices behind scenes

		m[0] = cy * cr;
		m[1] = cy * sr;
		m[2] = -sy;
		m[3] = 0.0f;

		m[4] = ( sp * sy * cr ) - ( cp * sr );
		m[5] = ( sp * sy * sr ) + ( cp * cr );
		m[6] = sp * cy;
		m[7] = 0.0f;

		m[8] = ( cp * sy * cr ) + ( sp * sr );
		m[9] = ( cp * sy * sr ) - ( sp * cr );
		m[10] = cp * cy;
		m[11] = 0.0f;

		m[12] = 0.0f;
		m[13] = 0.0f;
		m[14] = 0.0f;
		m[15] = 1.0f;

		/*
		m[0] = (cy * cr) + (sy * sp * sr);
		m[1] = -(cy * sr) + (sy * sp * cr);
		m[2] = sy * cp;
		m[3] = 0.0f;

		m[4] = sr * cp;
		m[5] = cr * cp;
		m[6] = -sp;
		m[7] = 0.0f;

		m[8] = -(sy * cr) + (cy * sp * sr);
		m[9] = (sr * sy) + (cy * sp *cr);
		m[10] = cy * cp;
		m[11] = 0.0f;

		m[12] = 0.0f;
		m[13] = 0.0f;
		m[14] = 0.0f;
		m[15] = 1.0f;
		*/

		return m;
	}

	Matrix4 Matrix4::QuaternionToMatrix( const Quaternion& q )
	{
		Matrix4 m;

		m[0] = ( 1.0f - ( 2.0f * pow( q.y, 2.0f ) ) - ( 2.0f * pow( q.z, 2.0f ) ) );
		m[1] = ( 2.0f * q.x * q.y ) + ( 2.0f * q.w * q.z );
		m[2] = ( 2.0f * q.x * q.z ) - ( 2.0f * q.w * q.y );
		m[3] = 0.0f;

		m[4] = ( 2.0f * q.x * q.y ) - ( 2.0f * q.w * q.z );
		m[5] = ( 1.0f - ( 2.0f * pow( q.x, 2.0f ) ) - ( 2.0f * pow( q.z, 2.0f ) ) );
		m[6] = ( 2.0f * q.y * q.z ) + ( 2.0f * q.w * q.x );
		m[7] = 0.0f;

		m[8] = ( 2.0f * q.x * q.z ) + ( 2.0f * q.w * q.y );
		m[9] = ( 2.0f * q.y * q.z ) - ( 2.0f * q.w * q.x );
		m[10] = ( 1.0f - ( 2.0f * pow( q.x, 2.0f ) ) - ( 2.0f * pow( q.y, 2.0f ) ) );
		m[11] = 0.0f;

		m[12] = 0.0f;
		m[13] = 0.0f;
		m[14] = 0.0f;
		m[15] = 1.0f;

		return m;
	}

}