#pragma once
#ifndef VOLUMETRICCLOUDS_H
#define VOLUMETRICCLOUDS_H

namespace Arcane
{
	class Texture3D;

	enum class CloudNoiseAlgorithm : int
	{
		CloudNoiseAlgorithm_Worley,
		CloudNoiseAlgorithm_Perlin,
		CloudNoiseAlgorithmSize
	};

	struct NoiseTextureParams
	{
		CloudNoiseAlgorithm NoiseAlgorithm = CloudNoiseAlgorithm::CloudNoiseAlgorithm_Worley;
		float Frequency = 8.0f;
		int Octaves = 8;
		std::mt19937::result_type Seed = 12345;
	};

	class VolumetricClouds
	{
	public:
		// Function for the editor to use to pre-generate a 3D noise texture that can be used for the volumetric cloud effect at runtime
		static Texture3D* Generate3DNoiseTexture(NoiseTextureParams& params);
	private:

	};
}
#endif
