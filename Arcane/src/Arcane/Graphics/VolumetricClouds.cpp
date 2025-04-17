#include "arcpch.h"
#include "VolumetricClouds.h"

#include <Arcane/Graphics/Texture/Texture3D.h>
#include <Arcane/Graphics/Noise/PerlinNoise.h>

namespace Arcane
{
	Texture3D* VolumetricClouds::Generate3DNoiseTexture(NoiseTextureParams& params)
	{
		Texture3D* texture3D = new Texture3D();

		const unsigned int width = 256;
		const unsigned int height = 256;
		const unsigned int depth = 256;

		const siv::PerlinNoise::seed_type seed = params.Seed;
		const siv::PerlinNoise perlin{ seed };
		const double fx = (params.Frequency / width);
		const double fy = (params.Frequency / height);
		const double fz = (params.Frequency / depth);

		std::vector<unsigned char> textureData(width * height * depth * 3); // 3 bytes per pixel (RGB)
		for (unsigned int z = 0; z < depth; z++)
		{
			for (unsigned int y = 0; y < height; y++)
			{
				for (unsigned int x = 0; x < width; x++)
				{
					size_t index = (z * width * height + y * width + x) * 3;

					if (params.NoiseAlgorithm == CloudNoiseAlgorithm::CloudNoiseAlgorithm_Worley)
					{
						textureData[index + 0] = 255;
						textureData[index + 1] = 255;
						textureData[index + 2] = 255;
					}
					else if (params.NoiseAlgorithm == CloudNoiseAlgorithm::CloudNoiseAlgorithm_Perlin)
					{
						//const double noise = perlin.octave3D_01()
						textureData[index + 0] = static_cast<unsigned char>(rand() % 256);
						textureData[index + 1] = static_cast<unsigned char>(rand() % 256);
						textureData[index + 2] = static_cast<unsigned char>(rand() % 256);
					}
				}
			}
		}

		Texture3DSettings textureSettings;
		texture3D->SetTextureSettings(textureSettings);
		texture3D->Generate3DTexture(width, height, depth, GL_RGB, GL_UNSIGNED_BYTE, textureData.data());
		return texture3D;
	}
}
