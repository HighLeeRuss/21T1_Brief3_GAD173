#include "app.h"
#include "portable-file-dialogs.h"

namespace App
{
	// External Globals. These are really implemented in app_main.cpp
	extern sf::RenderWindow g_window;
	extern sf::Clock g_clock;
	extern sf::Font g_font;
	extern bool g_running;
	extern kf::Xor128 g_rng;
	extern GameState m_currentState;

	// Add your own variables here

	GameState m_currentState = GameState::e_editor;

	// Example of exposing a variable to other files.
	// This creates the memory for the variable.
	int exampleValue = 0;
	TileMap tileMap;

	int currentTile = 1;
	int currentLayer = TileMap::Layer::e_foreground;

	GameState g_currentState = GameState::e_editor;

	bool start()
	{
		// Add some physics colliders to the screen edges
		// Bottom
		kage::Physics::EdgeBuilder().start(0, 16.875).end(30, 16.875).friction(1).build(kage::Physics::getDefaultStatic());
		// Top
		kage::Physics::EdgeBuilder().start(0, 0).end(30, 0).friction(1).build(kage::Physics::getDefaultStatic());
		// Left
		kage::Physics::EdgeBuilder().start(0, 0).end(0, 16.875).friction(1).build(kage::Physics::getDefaultStatic());
		// Right
		kage::Physics::EdgeBuilder().start(30, 0).end(30, 16.875).friction(1).build(kage::Physics::getDefaultStatic());

		return true;
	}

	void load() //loads a saved file
	{
		pfd::open_file of("Open a map", "", { "CSV File", "*.csv" }, false);
		auto result = of.result();
		if (!result.empty())
		{
			tileMap.load(result[0]);
		}
	}

	void save() //saves a csv of the level
	{
		pfd::save_file sf("Save a map", "", { "CSV File", "*.csv" });
		auto result = sf.result();
		if (result != "")
		{
			if (result.substr(result.size() - 4) != ".csv")
			{
				result += ".csv";
			}
			// result is the save file name
			tileMap.save(result);
		}
	}

	void update(float deltaT) 
	{
		// Your main game logic goes here
		switch (m_currentState)
		{
		case GameState::e_editor:	
			updateEditor(deltaT);
			break;
		case GameState::e_game:
			updateGame(deltaT);
			break;
		}

	}

	void updateGame(float deltaT)
	{
		auto Player = kage::World::findByTag("Player"); //if there is no player then return to editor mode
		if (!Player)
		{
			setState(GameState::e_editor);
			return;
		}

		if (kage::Input::isKeyPressed(sf::Keyboard::E))
		{
			setState(GameState::e_editor);
			return;
		}
	}

	void updateEditor(float deltaT)
	{
		if (kage::Input::isKeyPressed(sf::Keyboard::G))
		{
			setState(GameState::e_game);
			return;
		}

		auto mousePos = kage::Input::getMousePosition(g_window);
		if (kage::Input::isMouseDown(sf::Mouse::Button::Left)) //&& !ImGui::GetIO().WantCaptureMouse && g_window.hasFocus())
		{
			tileMap.setTile(mousePos.x, mousePos.y, currentLayer, { currentTile, 0 }); //TileMap::Layer::e_foreground, { 2,0 });
		}

		ImGui::Begin("Tiles");

		auto buttonColour = ImGui::GetStyleColorVec4(ImGuiCol_Button);
		ImVec4 activeColour(0.5, 0.5, 0, 1);

		if (currentLayer == TileMap::Layer::e_background)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, activeColour);
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColour);
		}
		if (ImGui::Button("Background") || kage::Input::isKeyPressed(sf::Keyboard::B))
		{
			currentLayer = TileMap::Layer::e_background;
		}
		ImGui::PopStyleColor();

		if (currentLayer == TileMap::Layer::e_foreground)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, activeColour);
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColour);
		}

		if (ImGui::Button("ForeGround") || kage::Input::isKeyPressed(sf::Keyboard::F))
		{
			currentLayer = TileMap::Layer::e_foreground;
		}
		ImGui::PopStyleColor();



		auto& tiledefs = tileMap.getTileDefinitions();

		for (int i = 0; i < tiledefs.size(); ++i)
		{
			TileDefinition td = tiledefs[i];
			tileMap.getAtlas().selectTile(td.tileX, td.tileY);
			ImGui::PushID(i);

			if (i % 2 != 0)
			{
				ImGui::SameLine();
			}

			if (currentTile == i)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, activeColour);
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Button, buttonColour);
			}

			if (ImGui::ImageButton(tileMap.getAtlas()))
			{
				currentTile = i;
			}
			ImGui::PopStyleColor();
			ImGui::PopID();
		}

		if (ImGui::Button("Load"))
		{
			load();
		}

		if (ImGui::Button("Save"))
		{
			save();
		}

		ImGui::End();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open", NULL, false))
				{
					load();
				}

				if (ImGui::MenuItem("Save", NULL, false))
				{
					save();
				}

				if (ImGui::MenuItem("Quit", NULL, false))
				{
					quit();
				}

				ImGui::EndMenu();
			}
			//if (ImGui::BeginMenu("Edit"))
			//{
			//	if (ImGui::MenuItem("Select", NULL, false))
			//	{
			//		// Do select stuff
			//	}
			//	ImGui::EndMenu();
			//}
			ImGui::EndMainMenuBar();
		}
	}

	void render()
	{
		switch (m_currentState)
		{
		case GameState::e_editor:
			renderEditor();
			break;
		case GameState::e_game:
			renderGame();
			break;
		}
	}

	void renderGame()
	{
		// Draw tile map layers
		tileMap.render(g_window);

		// Render World
		kage::World::render(g_window);

#ifdef _DEBUG

		// The next line draws the physics debug info. This should be removed in a final release.
		kage::Physics::debugDraw(&g_window, 64);
#endif
	}

	void renderEditor()
	{
		// Draw tile map layers
		tileMap.render(g_window);

		// Draw a debug grid
		kage::World::debugGrid(g_window);

	}

	void cleanup()
	{
		// Perform any clean up your project needs
	}

	void setState(GameState newState)
	{
		m_currentState = newState;
		if (m_currentState == GameState::e_editor)
		{
			enterStateEditor();
		}
		else
		{
			enterStateGame();
		}
	}

	void enterStateEditor()
	{
		kage::World::clear();
		kage::Physics::clearDefaultStaticFixtures();
		tileMap.setMode(TileMap::Mode::e_editor);
	}

	void enterStateGame()
	{
		kage::World::clear();
		kage::Physics::clearDefaultStaticFixtures();
		//Generate the level
		//spawn game objects
		//Reset game variables
		tileMap.setMode(TileMap::Mode::e_game);
		buildMap();
	}

	void buildMap()
	{
		for (int y = 0; y < tileMap.getMapHeight(); ++y)
		{
			for (int x = 0; x < tileMap.getMapWidth(); ++x)
			{
				Tile tile = tileMap.getTile(x, y, TileMap::e_foreground);
				TileDefinition td = tileMap.getTileDefinitions()[tile.tiledef];
				if (td.blocking)
				{
					kage::Physics::BoxBuilder().pos(kf::Vector2(x + 0.5, y + 0.5)).size(1, 1).userData(tile.tiledef).friction(0.5).build(kage::Physics::getDefaultStatic());
					//App::createBoat(kage::Physics::getDefaultStatic(), kf::Vector2(1, 1), kf::Vector2(x + 0.5, y + 0.5), 0, 1, 0, (void*)1, 0, 0.5);
					//kage::Physics::createBox(kage::Physics::getDefaultStatic(), kf::Vector2(1, 1), kf::Vector2(x + 0.5, y + 0.5), 0, 1, 0, (void*)1, 0, 0.5);
					//kage::Physics::CircleBuilder().pos(kf::Vector2(x + 0.5, y + 0.5)).radius(0.5).userData(1).friction(0.5).build(kage::Physics::getDefaultStatic());
				}
				
				if (tile.tiledef == TileMap::TileTypes::e_playerSpawn)
				{
					auto cat = kage::World::build<Player>();
					cat->position(x + 0.5, y + 0.5);
				}
				
				if (tile.tiledef == TileMap::TileTypes::e_manaSpawn) 
				{
					auto manaOrb = kage::World::build<ManaOrb>();
					manaOrb->position(x + .5, y + .5);
				}
				if (tile.tiledef == TileMap::TileTypes::e_frostySpawn) 
				{
					auto giant = kage::World::build<Giant>();
					giant->position(x + .5, y + .5);
				}
				if (tile.tiledef == TileMap::TileTypes::e_devilSpawn) 
				{
					auto devil = kage::World::build<Devil>();
					devil->position(x + .5, y + .5);
				}
				if (tile.tiledef == TileMap::TileTypes::e_door)
				{
					auto door = kage::World::build<EndCollider>();
					door->position(x + .5, y + .5);
				}

			}
		}
	}




}
