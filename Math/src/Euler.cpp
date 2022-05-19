// MIT License, Copyright (c) 2022 Malik Allen

#include "../include/Euler.h"
#include "../include/Matrix.h"
#include "../include/Quaternion.h"

namespace Kobe
{

	Euler Euler::MatrixToEuler( const Matrix4& m )
	{
		float roll, yaw, pitch;

		pitch = atan2( m[6], m[10] );

		float cy = sqrt( pow( m[0], 2.0f ) + pow( m[1], 2.0f ) );

		yaw = atan2( -m[2], cy );

		float sp = sin( pitch );
		float cp = cos( pitch );

		// In order to counter-act the gimble lock relation between the pitch and roll
		// We calculate the angles of roll and pitch independent
		roll = atan2( ( sp * m[8] - cp * m[4] ), ( cp * m[5] - sp * m[9] ) );

		pitch *= RADIANS_TO_DEGREES;
		yaw *= RADIANS_TO_DEGREES;
		roll *= RADIANS_TO_DEGREES;

		return Euler( pitch, yaw, roll );
	}

	Euler Euler::QuaternionToEuler( const Quaternion& q )
	{
		float sqw = q.w * q.w;
		float sqx = q.x * q.x;
		float sqy = q.y * q.y;
		float sqz = q.z * q.z;

		float sum = sqx + sqy + sqz + sqw;
		float testCase = ( q.x * q.y ) + ( q.z * q.w );

		float yaw, roll, pitch;

		if( testCase > 0.499f * sum )
		{
			yaw = 2.0f * atan2( q.x, q.w );
			roll = PI / 2.0f;
			pitch = 0.0f;
		}
		else if( testCase < -0.499f * sum )
		{
			yaw = -2.0f * atan2( q.x, q.w );
			roll = -PI / 2.0f;
			pitch = 0.0f;
		}
		else
		{
			yaw = atan2( ( 2.0f * q.y * q.w ) - ( 2.0f * q.x * q.z ), sqx - sqy - sqz + sqw );
			roll = asin( 2.0f * testCase / sum );
			pitch = atan2( ( 2.0f * q.x * q.w ) - ( 2.0f * q.y * q.z ), -sqx + sqy - sqz + sqw );
		}

		return Euler( pitch * RADIANS_TO_DEGREES, yaw * RADIANS_TO_DEGREES, roll * RADIANS_TO_DEGREES );
	}

}