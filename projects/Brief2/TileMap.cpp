#include "TileMap.h"
#include "app.h"

TileMap::TileMap()
{
	m_tileWidth = 64;
	m_tileHeight = 64;
	m_atlas.create("data/rpg_tiles.png", m_tileWidth, m_tileHeight);

	// Set these (and add more) for your game. These are just examples for testing.
	// TileDefinition data is in the order: {blocking, visibleInGame, tileX, tileY}
	// Tiles that are spawners for game objects should be not blocking or visible.
	m_tileDefinitions.push_back({ false, false, 0, 0 });	// Tile Definition 0: Blank
	m_tileDefinitions.push_back({ true, true, 21, 7 });		// Tile Definition 1: Wall
	m_tileDefinitions.push_back({ false, false, 6, 0 });	// Tile Definition 2: Chest
	m_tileDefinitions.push_back({ false, false, 1, 0 });	// Tile Definition 3: Health
	m_tileDefinitions.push_back({ false, false, 27, 13 });	// Tile Definition 4: Player Spawn

	setMapSize(16, 16);

	// Put some testing data into the map. This code should be removed once you add map editing.
	m_tiles[Layer::e_background][0 + 0 * m_mapWidth] = { 1,0 }; // {1,0} means tile definition 1 with data 0.
	m_tiles[Layer::e_background][1 + 1 * m_mapWidth] = { 2,0 };
	m_tiles[Layer::e_background][2 + 2 * m_mapWidth] = { 3,0 };
	m_tiles[Layer::e_foreground][0 + 0 * m_mapWidth] = { 2,0 };
	m_tiles[Layer::e_background][15 + 15 * m_mapWidth] = { 4,0 };
}

TileMap::~TileMap()
{
}

void TileMap::setMapSize(int width, int height)
{
	m_mapWidth = width;
	m_mapHeight = height;
	for (int layer = 0; layer < Layer::e_layerCount; ++layer)
	{
		m_tiles[layer].resize(m_mapWidth * m_mapHeight);
	}
}

void TileMap::render(sf::RenderTarget& rt)
{
	for (int layer = 0; layer < Layer::e_layerCount; ++layer)
	{
		for (int y = 0; y < m_mapHeight; ++y)
		{
			for (int x = 0; x < m_mapWidth; ++x)
			{
				Tile tile = m_tiles[layer][x + y * m_mapWidth];
				TileDefinition td = m_tileDefinitions[tile.tiledef];
				if (m_mode == Mode::e_editor || td.visibleInGame)
				{
					m_atlas.draw(rt, x * m_tileWidth, y * m_tileHeight, td.tileX, td.tileY);
				}
			}
		}
	}
}

std::vector<TileDefinition>& TileMap::getTileDefinitions()
{
	return m_tileDefinitions;
}

kage::Atlas& TileMap::getAtlas()
{
	return m_atlas;
}
