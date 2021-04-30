#pragma once
#include <SFML/Graphics.hpp>
#include "kage/atlas.h"

struct Tile
{
	int tiledef = 0;	// Which TileDefinition entry this tile uses.
	int data = 0;		// Optional data for the tile (like health before breaking)
	// You could add more members like tile flips, animation, etc.
};

struct TileDefinition
{
	bool blocking = false;		// The tile will generate a physics collider in game mode.
	bool visibleInGame = true;	// The tile is visible when in game mode. Tiles like spawners should only be visible in the editor.
	int tileX = 0;				// X coordinate of tile graphic in the atlas.
	int tileY = 0;				// Y coordinate of tile graphic in the atlas.
};

class TileMap
{
public:
	enum Layer
	{
		e_background,	// Background layer should have no effect on the world.
		e_foreground,	// Foreground layer is where physics and AI takes place.
		e_layerCount	// The number of layers.
	};
	enum Mode
	{
		e_editor,		// Editor mode. All tiles will render.
		e_game			// Game mode. Only "visibleInGame" tiles will render.
	};
	enum TileTypes
	{
		e_blank = 0,
		e_Wall,
		e_chest,
		e_health,
		e_playerSpawn,
		e_manaSpawn,
		e_devilSpawn,
		e_frostySpawn,
		e_door,


	};

private:
	int m_mapWidth = 0;									// Width of the map in tiles.
	int m_mapHeight = 0;								// Height of the map in tiles.
	int m_tileWidth = 0;								// Width of a tile in pixels.
	int m_tileHeight = 0;								// Height of a tile in pixels.
	Mode m_mode = Mode::e_editor;						// Current mode.
	kage::Atlas m_atlas;								// Atlas used for tile rendering.
	std::vector<TileDefinition> m_tileDefinitions;		// Collection of tile definitions.
	std::vector<Tile> m_tiles[Layer::e_layerCount];		// The map.

public:
	TileMap();
	~TileMap();

	// Render the tile map.
	// rt - a render target, such as a window or texture. eg. App's m_window
	void render(sf::RenderTarget &rt);

	// Set the size of the map and reallocate memory for all layers.
	// width - width of the map in tiles
	// height - height of the map in tiles
	void setMapSize(int width, int height);

	// Return a reference to the vector of TileDefinitions.
	std::vector<TileDefinition>& getTileDefinitions();

	// Return a reference to the Atlas.
	kage::Atlas& getAtlas();

	void setTile(int x, int y, int layer, Tile tile);
	Tile getTile(int x, int y, int layer);

	void load(std::string filename);
	void save(std::string filename);

	int getMapWidth();
	int getMapHeight();
	void setMode(Mode mode);

};
