/*
MapGeneratorHeightmap.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/noise/noise.hpp"
#include "zcraft/mapgen/MapGeneratorHeightmap.hpp"

using namespace zn;

namespace zcraft
{
	MapGeneratorHeightmap::MapGeneratorHeightmap(u32 seed)
	{
		m_seed = seed;
	}

	Block * MapGeneratorHeightmap::makeBlock(Vector3i pos)
	{
		Block * block = nullptr;
		Vector3i org = pos * Block::SIZE;

		block = new Block(pos);

		// Generates a simple heightmap
		if(org.z >= -96 && org.z < 160)
		{
			for(u8 y = 0; y < Block::SIZE; y++)
			for(u8 x = 0; x < Block::SIZE; x++)
			{
				s16 h = (u16)(256.f * (float)noise2dPerlin(
							x + org.x, y + org.y, m_seed, 6, 0.5, 256)) - 96;

				if(h >= org.z)
					h -= org.z;
				else
					h = 0;

				if(h < 0)
					std::cout << "e";

				if(h >= static_cast<s32>(Block::SIZE))
					h = Block::SIZE;

				if(h != 0)
				{
					for(u16 z = 0; z < h; z++)
					{
						f32 n2 = noise3dPerlin(
							x + org.x, y + org.y, z + org.z, m_seed, 5, 0.5, 128);

						if(n2 > 0.3f && n2 < 0.7f)
							block->set(x, y, z, Voxel(voxel::GRASS));
					}
				}
			}
		}
		else if(org.z < 0)
		{
			block->fill(Voxel(voxel::STONE));
		}

		if(block != nullptr)
			block->dirty = true; // To make it saved even if not modified yet

		return block;
	}

} // namespace zcraft




