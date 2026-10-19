#pragma once
#include <cmath>
#define PI = 3.14;
namespace CustomMath
{

	class Vector2 {
	public:
		float x;
		float y;

		Vector2() {
			x = 0.0f;
			y = 0.0f;
		}
		Vector2(int xValue, int yValue){
			x = xValue;
			y = yValue;
		}
		Vector2(float xValue, float yValue) {
			x = xValue;
			y = yValue;
		}


		

		static Vector2 Zero() {
			return Vector2(0.0f, 0.0f);
		}
		static float Dot(Vector2 vec1, Vector2 vec2) {
			
			return (vec1.x * vec2.x) + (vec1.y * vec2.y);
		}

		Vector2 operator+ (const Vector2 vec2)
		{
			return Vector2(x + vec2.x, y + vec2.y);
		}
		Vector2 operator-(const Vector2 vec2)
		{
			return Vector2(x - vec2.x, y - vec2.y);
		}

		Vector2 operator/(const float denominator)
		{
			return Vector2(x / denominator, y / denominator);
		}
		Vector2 operator*(const float multiplier)
		{
			return Vector2(x * multiplier, y * multiplier);
		}
		Vector2 operator+= (const Vector2 vec2) {
			
			x += vec2.x;
			y += vec2.y;
		}

		float Length() {

			return sqrt(pow(x,2) + pow(y,2));
		}
	};

	class Vector3 {
	public: 
		float x;
		float y;
		float z;

		Vector3(float xValue, float yValue, float zValue) {

			x = xValue;
			y = yValue;
			z = zValue;
		}
		Vector3(){
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		
		static Vector3 Zero() {
			return Vector3(0.0f, 0.0f, 0.0f);
		}
		static float Dot(Vector3 vec1, Vector3 vec2) {
			return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
		}
		Vector3 operator+ (const Vector3 vec) {

			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}
		Vector3 operator-(const Vector3 vec)
		{
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}
		Vector3 operator*(const float multiplier)
		{
			return Vector3(x * multiplier, y * multiplier, z * multiplier);
		}
		void operator= (const Vector3 vec1) {
			x = vec1.x;
			y = vec1.y;
			z = vec1.z;
		}
		void operator= (const Vector2 vec1) {
			x = vec1.x;
			y = vec1.y;
			z = 0.0f;
		}
	};
}

