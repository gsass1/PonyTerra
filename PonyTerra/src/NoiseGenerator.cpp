#include "MathUtil.h"
#include "NoiseGenerator.h"
#include <limits.h>

CNoiseGenerator::CNoiseGenerator()
{
	seed = 0;
	octaves = 0;
	amplitude = 0.0;
	frequency = 0.0;
	persistence = 0.0;
}

CNoiseGenerator::~CNoiseGenerator()
{
}

void CNoiseGenerator::Set(int octaves, double amplitude, double frequency, double persistence)
{
	seed = Math::Random(INT_MAX);
	this->octaves = octaves;
	this->amplitude = amplitude;
	this->frequency = frequency;
	this->persistence = persistence;
}

double CNoiseGenerator::Noise(int x, int y)
{
	double total = 0.0;
	double freq = frequency;
	double ampl = amplitude;

	for (int i = 0; i < octaves; ++i) {
		total = total + Smooth(x * freq, y * freq) * ampl;
		freq *= 2;
		ampl *= persistence;
	}

	return Math::Clamp(total, -2.4, 2.4) / 2.4;
}

double CNoiseGenerator::Noise1D(int x)
{
	return (1.0 - ((x * (x * x * 15731 + 789221) + seed) & 0x7fffffff) / 1073741824.0);
}

double CNoiseGenerator::NoiseGeneration(int x, int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + seed) & 0x7fffffff) / 1073741824.0);
}

double CNoiseGenerator::Smooth(double x, double y)
{
	double n1 = NoiseGeneration((int)x, (int)y);
	double n2 = NoiseGeneration((int)x + 1, (int)y);
	double n3 = NoiseGeneration((int)x, (int)y + 1);
	double n4 = NoiseGeneration((int)x + 1, (int)y + 1);

	double i1 = Interpolate(n1, n2, x - (int)x);
	double i2 = Interpolate(n3, n4, x - (int)x);

	return Interpolate(i1, i2, y - (int)y);
}

double CNoiseGenerator::Interpolate(double x, double y, double a)
{
	double val = (1.0 - Math::Cos(a * (double)Math::PI)) * 0.5;
	return x * (1.0 - val) + y * val;
}
