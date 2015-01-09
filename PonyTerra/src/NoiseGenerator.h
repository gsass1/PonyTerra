#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

class CNoiseGenerator
{
public:
            CNoiseGenerator();
            ~CNoiseGenerator();

    void    Set(int octaves, double amplitude, double frequency, double persistence);

    double  Noise(int x, int y);

    double  Noise1D(int x);

    double  NoiseGeneration(int x, int y);

    double  Smooth(double x, double y);

    double  Interpolate(double x, double y, double a);

    int     seed;
    int     octaves;
    double  amplitude;
    double  persistence;
    double  frequency;
};

#endif