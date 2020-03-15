#pragma once
#include <cmath>
#include "../math/vector.hpp"

#undef min
#undef max

namespace math
{
	typedef float matrix3x4[3][4];

	inline double __declspec (naked) __fastcall fsqrt(double n)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}

	inline void vector_angles(math::vec3 &forward, math::vec3 &angles)
	{
		float tmp	= 0.0f;
		float yaw	= 0.0f;
		float pitch = 0.0f;

		if (forward.y == 0.0f && forward.x == 0.0f) {
			yaw = 0.0f;

			if (forward.z > 0.0f)
				pitch = 270.0f;

			else pitch = 90.0f;
		}

		else {
			yaw = RAD2DEG(atan2f(forward.y, forward.x));

			if (yaw < 0.0f)
				yaw += 360.0f;

			tmp = forward.length_2d();
			pitch = RAD2DEG(atan2f(-forward.z, tmp));

			if (pitch < 0.0f)
				pitch += 360.0f;
		}

		angles.x = pitch;
		angles.y = yaw;
		angles.z = 0.0f;
	}

	inline void make_vector(math::vec3 angles, math::vec3 &vector)
	{
		float pitch = float(angles.x * PI / 180.0f);
		float yaw = float(angles.y * PI / 180.0f);
		float tmp = float(cos(pitch));

		vector.x = (-tmp * -cosf(yaw));
		vector.y = (sinf(yaw) * tmp);
		vector.z = -sinf(pitch);
	}

	inline void angle_vectors(const math::vec3 &angles, math::vec3 *forward)
	{
		float sp, sy, cp, cy;

		sy = sinf(DEG2RAD(angles.y));
		cy = cosf(DEG2RAD(angles.y));

		sp = sinf(DEG2RAD(angles.x));
		cp = cosf(DEG2RAD(angles.x));

		forward->x = (cp * cy);
		forward->y = (cp * sy);
		forward->z = -sp;
	}

	inline float dot_product(const float *v1, const float *v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	inline void sin_cos(float radians, float *sine, float *cosine)
	{
		_asm
		{
			fld		DWORD PTR[radians]
			fsincos

			mov edx, DWORD PTR[cosine]
			mov eax, DWORD PTR[sine]

			fstp DWORD PTR[edx]
			fstp DWORD PTR[eax]
		}
	}

	inline void vector_transform(const math::vec3 &some, const matrix3x4 &matrix, math::vec3 &out)
	{
		for (auto i = 0; i < 3; i++)
			out[i] = some.dot((math::vec3 &)matrix[i]) + matrix[i][3];
	}

	inline float angles_diff(math::vec3 view_angles, math::vec3 target_angles, float distance)
	{
		float fPitch = sinf(DEG2RAD(view_angles.x - target_angles.x)) * distance;
		float fYaw = sinf(DEG2RAD(view_angles.y - target_angles.y)) * distance;

		return fsqrt(powf(fPitch, 2.0f) + powf(fYaw, 2.0f));
	}

	inline void matrix_set_column(const math::vec3 &in, int column, matrix3x4 &out)
	{
		out[0][column] = in.x;
		out[1][column] = in.y;
		out[2][column] = in.z;
	}

	inline void matrix_copy(const matrix3x4 &source, matrix3x4 &target)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				target[i][j] = source[i][j];
			}
		}
	}

	inline void angle_matrix(const math::vec3 &angles, matrix3x4 &matrix)
	{
		auto SinCos = [](float radians, float *sine, float *cosine)
		{
			*sine = sin(radians);
			*cosine = cos(radians);
		};

		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		// matrix = (YAW * PITCH) * ROLL
		matrix[0][0] = cp * cy;
		matrix[1][0] = cp * sy;
		matrix[2][0] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;
		matrix[0][1] = sp * srcy - crsy;
		matrix[1][1] = sp * srsy + crcy;
		matrix[2][1] = sr * cp;

		matrix[0][2] = sp * crcy + srsy;
		matrix[1][2] = sp * crsy - srcy;
		matrix[2][2] = cr * cp;

		matrix[0][3] = 0.0f;
		matrix[1][3] = 0.0f;
		matrix[2][3] = 0.0f;
	}

	inline void angle_matrix(const math::vec3 &angles, const math::vec3 &origin, matrix3x4 &matrix)
	{
		angle_matrix(angles, matrix);
		matrix_set_column(origin, 3, matrix);
	}

	inline void concat_transforms(const matrix3x4 &in1, const matrix3x4 &in2, matrix3x4 &out)
	{
		if (&in1 == &out)
		{
			matrix3x4 in1b;
			matrix_copy(in1, in1b);
			concat_transforms(in1b, in2, out);
			return;
		}

		if (&in2 == &out)
		{
			matrix3x4 in2b;
			matrix_copy(in2, in2b);
			concat_transforms(in1, in2b, out);
			return;
		}

		out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
			in1[0][2] * in2[2][0];
		out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
			in1[0][2] * in2[2][1];
		out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
			in1[0][2] * in2[2][2];
		out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
			in1[0][2] * in2[2][3] + in1[0][3];
		out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
			in1[1][2] * in2[2][0];
		out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
			in1[1][2] * in2[2][1];
		out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
			in1[1][2] * in2[2][2];
		out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
			in1[1][2] * in2[2][3] + in1[1][3];
		out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
			in1[2][2] * in2[2][0];
		out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
			in1[2][2] * in2[2][1];
		out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
			in1[2][2] * in2[2][2];
		out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
			in1[2][2] * in2[2][3] + in1[2][3];
	}

	inline void matrix_multiply(const matrix3x4 &in1, const matrix3x4 &in2, matrix3x4 &out)
	{
		concat_transforms(in1, in2, out);
	}

	inline void vector_rotate(const float *in1, const matrix3x4 &in2, float *out)
	{
		out[0] = dot_product(in1, in2[0]);
		out[1] = dot_product(in1, in2[1]);
		out[2] = dot_product(in1, in2[2]);
	}

	inline void vector_rotate(const math::vec3 &in1, const matrix3x4 &in2, math::vec3 &out)
	{
		vector_rotate(&in1.x, in2, &out.x);
	}

	inline void vector_rotate(const math::vec3 &in1, const math::vec3 &in2, math::vec3 &out)
	{
		matrix3x4 matRotate;
		angle_matrix(in2, matRotate);
		vector_rotate(in1, matRotate, out);
	}

	inline float normalize_angle(float ang)
	{
		if (!std::isfinite(ang))
			return 0.0f;

		return std::remainder(ang, 360.0f);
	}

	inline void clamp_angles(math::vec3 &v)
	{
		v.x = std::max(-89.0f, std::min(89.0f, normalize_angle(v.x)));
		v.y = normalize_angle(v.y);
		v.z = 0.0f;
	}

	inline math::vec3 calc_angle(const math::vec3 &src, const math::vec3 &dst)
	{
		math::vec3 ang = math::vec3(0.0f, 0.0f, 0.0f);
		math::vec3 delta = (src - dst);
		float fHyp = fsqrt((delta.x * delta.x) + (delta.y * delta.y));

		ang.x = (atanf(delta.z / fHyp) * M_RADPI);
		ang.y = (atanf(delta.y / delta.x) * M_RADPI);
		ang.z = 0.0f;

		if (delta.x >= 0.0f)
			ang.y += 180.0f;

		return ang;
	}

	inline float calc_fov(const math::vec3 &src, const math::vec3 &dst)
	{
		math::vec3 v_src = math::vec3();
		angle_vectors(src, &v_src);

		math::vec3 v_dst = math::vec3();
		angle_vectors(dst, &v_dst);
		
		float result = RAD2DEG(acos(v_dst.dot(v_src) / v_dst.length_sqr()));

		if (!isfinite(result) || isinf(result) || isnan(result))
			result = 0.0f;

		return result;
	}

	inline float map(float x, float in_min, float in_max, float out_min, float out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}