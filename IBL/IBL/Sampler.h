#pragma once
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ToolFunctions.h"
#include "SphericalHarmonic.h"

using std::vector;

struct Sample
{
	glm::vec3 direction;// for (n . w) dot
	float theta, phi;
	float SHcoeffs[9];
};



class Sampler
{
public:
	Sampler(int numSamples);
	~Sampler();

	bool GenerateSamples(int sqrtNumSamples)
	{
		//int numSamples = sqrtNumSamples*sqrtNumSamples;

		for (int i = 0; i < sqrtNumSamples; i++)
		{
			for (int j = 0; j < sqrtNumSamples; j++)
			{
				float a = ((float)i + rand() / RAND_MAX) / (float)sqrtNumSamples;
				float b = ((float)j + rand() / RAND_MAX) / (float)sqrtNumSamples;
				float theta = 2 * acos(sqrt(1 - a));
				float phi = 2 * MY_PI*b;
				float x = sin(theta)*cos(phi);
				float y = sin(theta)*sin(phi);
				float z = cos(theta);
				int k = i*sqrtNumSamples + j;
				samples[k].direction.x = x;
				samples[k].direction.y = y;
				samples[k].direction.z = z;
				samples[k].phi = phi;
				samples[k].theta = theta;

				// Fill sample's SH coefficients
				for (int n = 0; n < 9; ++n)
					samples[k].SHcoeffs[n] = SphericalH::SHFunc::SHvalue(theta, phi, n);

			}
		}
		//sampleInitialized = true;
		return true;
	}
	unsigned size() const
	{
		return samples.size();
	}
private:
	vector<Sample> samples;

};
