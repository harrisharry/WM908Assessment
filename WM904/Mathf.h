#pragma once
namespace Mathf
{
	class Vector2 {
	
	public:
		
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

		float x;
		float y;
		

		static Vector2 Zero() {
			return Vector2(0.0f, 0.0f);
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
	};

	class Vector3 {
	public: 
		int x;
		int y;
		int z;
	};
}

