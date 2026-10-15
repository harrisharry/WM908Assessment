#pragma once

namespace Colour {
	struct Colour {
	public:

		Colour(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
		{
			red = r;
			blue = b;
			green = g;
			alpha = a;
		}
		Colour(unsigned int r, unsigned int g, unsigned int b)
		{
			red = r;
			blue = b;
			green = g;
			alpha = 255;
		}
		unsigned int red = 0;
		unsigned int blue = 0;
		unsigned int green = 0;
		unsigned int alpha = 0;

		static const Colour Red() {
			return Colour(255, 0, 0, 255);
		}
		static const Colour Purple() {
			return Colour(128, 0, 128);
		}

	};


}