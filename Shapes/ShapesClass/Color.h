#pragma once
#include<stdint.h>
struct Color {
	Color();
	Color(const uint8_t iRed, const uint8_t iGreen, const uint8_t iBlue);
	uint8_t mRed;
	uint8_t mGreen;
	uint8_t mBlue;
};