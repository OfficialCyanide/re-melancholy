#include <math.h>

#pragma warning(disable : 4244)

namespace math
{
	#define M_RADPI		57.295779513082
	#define PI			3.14159265358979323846
	#define DEG2RAD(x)	((float)(x) * (float)((float)(PI) / 180.0f))
	#define RAD2DEG(x)	((float)(x) * (float)(180.0f / (float)(PI)))
	#define SQUARE(x)	(x * x)

	class vec2
	{
	public:
		vec2(void)
		{
			x = y = 0.0f;
		}

		vec2(float X, float Y)
		{
			x = X; y = Y;
		}

		vec2(float *v)
		{
			x = v[0]; y = v[1];
		}

		vec2(const float *v)
		{
			x = v[0]; y = v[1];
		}

		vec2(const vec2 &v)
		{
			x = v.x; y = v.y;
		}

		vec2 &operator=(const vec2 &v)
		{
			x = v.x; y = v.y; return *this;
		}

		float &operator[](int i)
		{
			return ((float *)this)[i];
		}

		float operator[](int i) const
		{
			return ((float *)this)[i];
		}

		vec2 &operator+=(const vec2 &v)
		{
			x += v.x; y += v.y; return *this;
		}

		vec2 &operator-=(const vec2 &v)
		{
			x -= v.x; y -= v.y; return *this;
		}

		vec2 &operator*=(const vec2 &v)
		{
			x *= v.x; y *= v.y; return *this;
		}

		vec2 &operator/=(const vec2 &v)
		{
			x /= v.x; y /= v.y; return *this;
		}

		vec2 &operator+=(float v)
		{
			x += v; y += v; return *this;
		}

		vec2 &operator-=(float v)
		{
			x -= v; y -= v; return *this;
		}

		vec2 &operator*=(float v)
		{
			x *= v; y *= v; return *this;
		}

		vec2 &operator/=(float v)
		{
			x /= v; y /= v; return *this;
		}

		vec2 operator+(const vec2 &v) const
		{
			return vec2(x + v.x, y + v.y);
		}

		vec2 operator-(const vec2 &v) const
		{
			return vec2(x - v.x, y - v.y);
		}

		vec2 operator*(const vec2 &v) const
		{
			return vec2(x * v.x, y * v.y);
		}

		vec2 operator/(const vec2 &v) const
		{
			return vec2(x / v.x, y / v.y);
		}

		vec2 operator+(float v) const
		{
			return vec2(x + v, y + v);
		}

		vec2 operator-(float v) const
		{
			return vec2(x - v, y - v);
		}

		vec2 operator*(float v) const
		{
			return vec2(x * v, y * v);
		}

		vec2 operator/(float v) const
		{
			return vec2(x / v, y / v);
		}

		void set(float X = 0.0f, float Y = 0.0f)
		{
			x = X; y = Y;
		}

		float length(void) const
		{
			return sqrtf(x * x + y * y);
		}

		float length_sqr(void) const
		{
			return (x * x + y * y);
		}

		float dist_to(const vec2 &v) const
		{
			return (*this - v).length();
		}

		float dist_to_sqr(const vec2 &v) const
		{
			return (*this - v).length_sqr();
		}

		float dot(const vec2 &v) const
		{
			return (x * v.x + y * v.y);
		}

		bool is_zero(void) const
		{
			return (x > -0.01f && x < 0.01f &&
				y > -0.01f && y < 0.01f);
		}

	public:
		float x, y;
	};

	class vec3
	{
	public:
		vec3(void)
		{
			x = y = z = 0.0f;
		}

		vec3(float X, float Y, float Z)
		{
			x = X; y = Y; z = Z;
		}

		vec3(float *v)
		{
			x = v[0]; y = v[1]; z = v[2];
		}

		vec3(const float *v)
		{
			x = v[0]; y = v[1]; z = v[2];
		}

		vec3(const vec3 &v)
		{
			x = v.x; y = v.y; z = v.z;
		}

		vec3(const vec2 &v)
		{
			x = v.x; y = v.y; z = 0.0f;
		}

		vec3 &operator=(const vec3 &v)
		{
			x = v.x; y = v.y; z = v.z; return *this;
		}

		vec3 &operator=(const vec2 &v)
		{
			x = v.x; y = v.y; z = 0.0f; return *this;
		}

		float &operator[](int i)
		{
			return ((float *)this)[i];
		}

		float operator[](int i) const
		{
			return ((float *)this)[i];
		}

		vec3 &operator+=(const vec3 &v)
		{
			x += v.x; y += v.y; z += v.z; return *this;
		}

		vec3 &operator-=(const vec3 &v)
		{
			x -= v.x; y -= v.y; z -= v.z; return *this;
		}

		vec3 &operator*=(const vec3 &v)
		{
			x *= v.x; y *= v.y; z *= v.z; return *this;
		}

		vec3 &operator/=(const vec3 &v)
		{
			x /= v.x; y /= v.y; z /= v.z; return *this;
		}

		vec3 &operator+=(float v)
		{
			x += v; y += v; z += v; return *this;
		}

		vec3 &operator-=(float v)
		{
			x -= v; y -= v; z -= v; return *this;
		}

		vec3 &operator*=(float v)
		{
			x *= v; y *= v; z *= v; return *this;
		}

		vec3 &operator/=(float v)
		{
			x /= v; y /= v; z /= v; return *this;
		}

		vec3 operator+(const vec3 &v) const
		{
			return vec3(x + v.x, y + v.y, z + v.z);
		}

		vec3 operator-(const vec3 &v) const
		{
			return vec3(x - v.x, y - v.y, z - v.z);
		}

		vec3 operator*(const vec3 &v) const
		{
			return vec3(x * v.x, y * v.y, z * v.z);
		}

		vec3 operator/(const vec3 &v) const
		{
			return vec3(x / v.x, y / v.y, z / v.z);
		}

		vec3 operator+(float v) const
		{
			return vec3(x + v, y + v, z + v);
		}

		vec3 operator-(float v) const
		{
			return vec3(x - v, y - v, z - v);
		}

		vec3 operator*(float v) const
		{
			return vec3(x * v, y * v, z * v);
		}

		vec3 operator/(float v) const
		{
			return vec3(x / v, y / v, z / v);
		}

		void set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
		{
			x = X; y = Y; z = Z;
		}

		float length(void) const
		{
			return sqrtf(x * x + y * y + z * z);
		}

		float size(void) const
		{
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		}

		float length_sqr(void) const
		{
			return (x * x + y * y + z * z);
		}

		float length_2d(void) const
		{
			return sqrtf(x * x + y * y);
		}

		float length_2d_sqr(void) const
		{
			return (x * x + y * y);
		}

		void norm_in_place()
		{
			vec3 &v = *this;

			float iradius = 1.f / (this->length() + 1.192092896e-07F); //FLT_EPSILON

			v.x *= iradius;
			v.y *= iradius;
			v.z *= iradius;
		}

		float dist_to(const vec3 &v) const
		{
			return (*this - v).length();
		}

		float dist_to_sqr(const vec3 &v) const
		{
			return (*this - v).length_sqr();
		}

		float dot(const vec3 &v) const
		{
			return (x * v.x + y * v.y + z * v.z);
		}

		vec3 cross(const vec3 &v) const
		{
			return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}

		bool is_zero(void) const
		{
			return (x > -0.01f && x < 0.01f &&
				y > -0.01f && y < 0.01f &&
				z > -0.01f && z < 0.01f);
		}

	public:
		float x, y, z;
	};
}