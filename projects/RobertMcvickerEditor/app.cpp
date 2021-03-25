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

	// Add your own variables here

	// Example of exposing a variable to other files.
	// This creates the memory for the variable.
	int exampleValue = 0;
	TileMap tileMap;

	int currentTile = 1;
	int currentLayer = TileMap::Layer::e_foreground;

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

	void load() 
	{
		pfd::open_file of("Open a map", "", { "CSV File", "*.csv" }, false);
		auto result = of.result();
		if (!result.empty())
		{
			tileMap.load(result[0]);
		}
	}

	void save() 
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
		
		for (int i = 0; i < tiledefs.size() ; ++i)
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
		// Draw tile map layers
		tileMap.render(g_window);

		// Draw a debug grid
		kage::World::debugGrid(g_window);

		// Render World
		kage::World::render(g_window);

		// The next line draws the physics debug info. This should be removed in a final release.
		kage::Physics::debugDraw(&g_window, 64);
	}

	void cleanup()
	{
		// Perform any clean up your project needs
	}
}
