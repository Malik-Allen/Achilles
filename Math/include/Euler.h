// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include "Vector.h"

namespace Kobe
{
	class Matrix4;
	struct Quaternion;

	struct Euler : public Vector3
	{
		// The angles in the Euler Struct should never exceed 360.0
		// Representing a sequence of rotations
		// pitch, yaw, roll;

		inline explicit Euler( float a = 0.0f )
		{
			x = a; y = a; z = a;
		}

		inline Euler( float pitch_, float yaw_, float roll_ )
		{
			Load( pitch_, yaw_, roll_ );
		}

		inline void Load( float pitch_, float yaw_, float roll_ )
		{
			x = pitch_; y = yaw_; z = roll_;
		}

		inline Euler( const Euler& e )
		{
			x = e.x; y = e.y; z = e.z;
		}

		inline Euler& operator= ( const Euler& e )
		{
			x = e.x; y = e.y; z = e.z;
			return *this;
		}

		// Converting the representation of a Matrix4 to an Euler
		static Euler MatrixToEuler( const Matrix4& m );

		// Converting a Quaternion into an Euler(Y, Z, X)
		static Euler QuaternionToEuler( const Quaternion& q );

	};

}
