///////////////////////////////////////////////////////
// MD Studio: A complete SEGA Mega Drive content tool
//
// (c) 2015 Matt Phillips, Big Evil Corporation
///////////////////////////////////////////////////////

#include "MapPanel.h"
#include "TileRendering.h"

MapPanel::MapPanel(ion::io::ResourceManager& resourceManager, wxWindow *parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: ViewPanel(resourceManager, parent, winid, pos, size, style, name)
{
	
	m_currentTool = eToolPaint;
	m_clipboard = NULL;
	m_clonePreviewPrimitive = NULL;

	ResetToolData();

	//Colours
	m_previewColour = ion::Colour(1.0f, 1.0f, 1.0f, 1.0f);
	m_boxSelectColour = ion::Colour(0.1f, 0.5f, 0.7f, 0.8f);
	m_clonePreviewColour = ion::Colour(0.7f, 0.7f, 0.7f, 1.0f);

	//Load shaders
	m_selectionVertexShader = m_resourceManager.GetResource<ion::render::Shader>("flat_v.ion.shader");
	m_selectionPixelShader = m_resourceManager.GetResource<ion::render::Shader>("flat_p.ion.shader");

	//Hack: wait for resources
	//TODO: SetVertexShader() fetches param handles, only succeeds if finished loading
	while(m_resourceManager.GetNumResourcesWaiting() > 0)
	{
		wxSleep(1);
	}

	//Create selection material
	m_selectionMaterial = new ion::render::Material();
	m_selectionMaterial->SetDiffuseColour(m_boxSelectColour);
	m_selectionMaterial->SetVertexShader(m_selectionVertexShader);
	m_selectionMaterial->SetPixelShader(m_selectionPixelShader);

	//Create preview quad
	m_previewPrimitive = new ion::render::Quad(ion::render::Quad::xy, ion::Vector2(4.0f, 4.0f));
}

MapPanel::~MapPanel()
{
	ResetToolData();

	delete m_selectionMaterial;
	delete m_previewPrimitive;
	m_selectionVertexShader.Clear();
	m_selectionPixelShader.Clear();

	//Hack: wait for resources
	while(m_resourceManager.GetNumResourcesWaiting() > 0)
	{
		wxSleep(1);
	}
}

void MapPanel::SetProject(Project* project)
{
	ViewPanel::SetProject(project);

	//Redraw map
	PaintMap(m_project->GetMap());

	//Refresh panel
	Refresh();
}

void MapPanel::SetTool(Tool tool)
{
	if(m_project)
	{
		Map& map = m_project->GetMap();

		switch(tool)
		{
		case eToolFill:
			//If previous tool was 'select', fill selection and leave previous tool data
			//TODO: Should this really be a tool? Doesn't follow the same rules as the others
			//(it's a single action, rather than a state which requires interaction from the user via the map)
			if(m_currentTool == eToolSelect)
			{
				if(m_project->GetPaintTile() != InvalidTileId)
				{
					//Fill selection
					FillTiles(m_project->GetPaintTile(), m_selectedTiles);

					//Refresh
					Refresh();
				}

				//Set back to select tool, leave tool data intact
				tool = eToolSelect;
			}
			else
			{
				ResetToolData();
			}
			break;

		case eToolPaint:
			m_previewTile = m_project->GetPaintTile();
			ResetToolData();
			break;

		case eToolClone:
			//Must previously have been in Select mode
			if(m_currentTool == eToolSelect)
			{
				//and have data to work with
				if(m_selectedTiles.size() > 0)
				{
					//Get min/max width/height
					int left, top, right, bottom;
					FindBounds(m_selectedTiles, left, top, right, bottom);
					int width = abs(right - left) + 1;
					int height = abs(bottom - top) + 1;

					//Create preview primitive
					if(m_clonePreviewPrimitive)
						delete m_clonePreviewPrimitive;

					m_clonePreviewPrimitive = new ion::render::Chessboard(ion::render::Chessboard::xy, ion::Vector2(width * 4.0f, height * 4.0f), width, height, true);

					//Create temp stamp
					if(m_clipboard)
						delete m_clipboard;

					m_clipboard = new Stamp(width, height);

					//Populate stamp, set primitive UV coords
					ion::render::TexCoord coords[4];

					for(int i = 0; i < m_selectedTiles.size(); i++)
					{
						int mapX = m_selectedTiles[i].x;
						int mapY = m_selectedTiles[i].y;
						int stampX = mapX - left;
						int stampY = mapY - top;
						int y_inv = height - 1 - stampY;
						TileId tileId = map.GetTile(mapX, mapY);
						u32 tileFlags = map.GetTileFlags(mapX, mapY);
						m_clipboard->SetTile(stampX, stampY, tileId);
						m_clipboard->SetTileFlags(stampX, stampY, tileFlags);
						GetTileTexCoords(tileId, coords, (tileFlags & Map::eFlipX)!=0, (tileFlags & Map::eFlipY)!=0);
						m_clonePreviewPrimitive->SetTexCoords((y_inv * width) + stampX, coords);
					}
				}
			}
			else
			{
				ResetToolData();
			}

			break;

		default:
			ResetToolData();
		}
	}

	m_currentTool = tool;
}

void MapPanel::ResetToolData()
{
	//Invalidate preview tile
	m_previewTile = InvalidTileId;
	m_previewTileFlipX = false;
	m_previewTileFlipY = false;

	//Invalidate box/multiple selection
	m_selectedTiles.clear();
	m_multipleSelection = false;
	m_boxSelectStart.x = -1;
	m_boxSelectStart.y = -1;
	m_boxSelectEnd.x = -1;
	m_boxSelectEnd.y = -1;

	//Delete clipboard stamp
	if(m_clipboard)
	{
		delete m_clipboard;
		m_clipboard = NULL;
	}

	if(m_clonePreviewPrimitive)
	{
		delete m_clonePreviewPrimitive;
		m_clonePreviewPrimitive = NULL;
	}
}

void MapPanel::OnMouse(wxMouseEvent& event)
{
	ViewPanel::OnMouse(event);
}

void MapPanel::OnKeyboard(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_ESCAPE)
	{
		ResetToolData();
		m_currentTool = eToolSelect;
		Refresh();
	}

	if(m_currentTool == eToolPaint)
	{
		if(m_previewTileFlipX != event.ShiftDown())
		{
			//SHIFT held, set H flip and refresh preview tile
			m_previewTileFlipX = event.ShiftDown();
			Refresh();
		}

		if(m_previewTileFlipY != event.ControlDown())
		{
			//CTRL held, set V flip and refresh preview tile
			m_previewTileFlipY = event.ControlDown();
			Refresh();
		}
	}

	if(m_currentTool == eToolSelect)
	{
		//Store CTRL held state for multiple selection
		m_multipleSelection = event.ControlDown();
	}

	ViewPanel::OnKeyboard(event);
}

void MapPanel::OnErase(wxEraseEvent& event)
{
	ViewPanel::OnErase(event);
}

void MapPanel::OnResize(wxSizeEvent& event)
{
	ViewPanel::OnResize(event);
}

void MapPanel::HandleMouseTileEvent(ion::Vector2 mouseDelta, int buttonBits, int x, int y)
{
	Map& map = m_project->GetMap();
	Tileset& tileset = m_project->GetMap().GetTileset();

	const int mapWidth = map.GetWidth();
	const int mapHeight = map.GetHeight();

	//Invert for OpenGL
	int y_inv = (mapHeight - 1 - y);

	//Check in map range
	if((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight))
	{
		switch(m_currentTool)
		{
		case eToolPaint:
		{
			//Update paint preview tile
			m_previewTile = m_project->GetPaintTile();

			//If clicking/dragging, paint tile
			if(buttonBits)
			{
				//Get tile ID to paint
				TileId tileId = InvalidTileId;
				if(buttonBits & eMouseLeft)
					tileId = m_project->GetPaintTile();
				else if(buttonBits & eMouseRight)
					tileId = m_project->GetEraseTile();

				if(tileId != InvalidTileId)
				{
					//Set on map
					map.SetTile(x, y, tileId);

					//Set V/H flip flags
					u32 tileFlags = 0;
					if(m_previewTileFlipX)
						tileFlags |= Map::eFlipX;
					if(m_previewTileFlipY)
						tileFlags |= Map::eFlipY;

					//Invert Y from OpenGL back to map space
					map.SetTileFlags(x, y, tileFlags);

					//Paint to canvas
					PaintTile(tileId, x, y_inv, m_previewTileFlipX, m_previewTileFlipY);
				}
			}
			break;
		}

		case eToolSelect:
		{
			if(buttonBits & eMouseLeft)
			{
				if(!(m_prevMouseBits & eMouseLeft))
				{
					//Single left-click, pick tiles one by one
					if(m_boxSelectEnd.x > 0 && m_boxSelectEnd.y > 0)
					{
						//Previous selection was box selection, clear it
						m_selectedTiles.clear();

						//Reset box end
						m_boxSelectEnd.x = -1;
						m_boxSelectEnd.y = -1;
					}

					//If CTRL not held
					if(!m_multipleSelection)
					{
						//Clear selection, start again
						m_selectedTiles.clear();

						//Start box selection, in case next event is dragging
						m_boxSelectStart.x = x;
						m_boxSelectStart.y = y;
					}

					//Single click - add tile at cursor to selection
					m_selectedTiles.push_back(ion::Vector2i(x, y));
				}
				else if(!m_multipleSelection)
				{
					//Dragging, set box end
					m_boxSelectEnd.x = x;
					m_boxSelectEnd.y = y;

					//Clear current selection
					m_selectedTiles.clear();

					//Sanitise loop order
					int top = min(m_boxSelectStart.y, m_boxSelectEnd.y);
					int left = min(m_boxSelectStart.x, m_boxSelectEnd.x);
					int bottom = max(m_boxSelectStart.y, m_boxSelectEnd.y);
					int right = max(m_boxSelectStart.x, m_boxSelectEnd.x);

					//Add all tiles in box
					for(int tileX = left; tileX <= right; tileX++)
					{
						for(int tileY = top; tileY <= bottom; tileY++)
						{
							m_selectedTiles.push_back(ion::Vector2i(tileX, tileY));
						}
					}
				}

				//Refresh to draw box selection
				Refresh();
			}
			break;
		}

		case eToolPicker:
		{
			if(buttonBits & eMouseLeft)
			{
				//Pick tile
				TileId tile = map.GetTile(x, y);

				//Set as paint tile
				m_project->SetPaintTile(tile);

				//Set as preview tile
				m_previewTile = tile;

				//Set paint tool
				SetTool(eToolPaint);
			}

			//TODO: Update tileset panel selection + toolbox button state
			break;
		}

		case eToolFlipX:
		{
			//Flip preview opposite of current tile
			m_previewTile = map.GetTile(x, y);
			m_previewTileFlipX = (map.GetTileFlags(x, y) & Map::eFlipX) == 0;

			if(buttonBits & eMouseLeft)
			{
				//Flip tile X
				u32 tileFlags = map.GetTileFlags(x, y);
				tileFlags ^= Map::eFlipX;
				map.SetTileFlags(x, y, tileFlags);

				//Redraw on canvas
				TileId tileId = map.GetTile(x, y);
				PaintTile(tileId, x, y_inv, (tileFlags & Map::eFlipX) != 0, (tileFlags & Map::eFlipY) != 0);
				Refresh();
			}

			break;
		}

		case eToolFlipY:
		{
			//Flip preview opposite of current tile
			m_previewTile = map.GetTile(x, y);
			m_previewTileFlipY = (map.GetTileFlags(x, y) & Map::eFlipY) == 0;

			if(buttonBits & eMouseLeft)
			{
				//Flip tile Y
				u32 tileFlags = map.GetTileFlags(x, y);
				tileFlags ^= Map::eFlipY;
				map.SetTileFlags(x, y, tileFlags);

				//Redraw on canvas
				TileId tileId = map.GetTile(x, y);
				PaintTile(tileId, x, y_inv, (tileFlags & Map::eFlipX) != 0, (tileFlags & Map::eFlipY) != 0);
				Refresh();
			}
			break;
		}

		case eToolClone:
		{
			//Update paste pos
			m_clonePastePos.x = x;
			m_clonePastePos.y = y;

			//Clamp to stamp size
			if(m_clonePastePos.x + m_clipboard->GetWidth() > mapWidth)
				m_clonePastePos.x = mapWidth - m_clipboard->GetWidth();
			if(m_clonePastePos.y + m_clipboard->GetHeight() > mapHeight)
				m_clonePastePos.y = mapHeight - m_clipboard->GetHeight();

			//Redraw
			Refresh();

			if((buttonBits & eMouseLeft) && !(m_prevMouseBits & eMouseLeft))
			{
				for(int stampX = 0; stampX < m_clipboard->GetWidth(); stampX++)
				{
					for(int stampY = 0; stampY < m_clipboard->GetHeight(); stampY++)
					{
						TileId tileId = m_clipboard->GetTile(stampX, stampY);
						if(tileId != InvalidTileId)
						{
							u32 tileFlags = m_clipboard->GetTileFlags(stampX, stampY);
							int mapX = stampX + m_clonePastePos.x;
							int mapY = stampY + m_clonePastePos.y;
							int y_inv = m_project->GetMap().GetHeight() - 1 - mapY;

							//Place on map - TODO: Map::PlaceStamp()
							m_project->GetMap().SetTile(mapX, mapY, tileId);
							m_project->GetMap().SetTileFlags(mapX, mapY, tileFlags);

							//Paint on canvas
							PaintTile(tileId, mapX, y_inv, (tileFlags & Map::eFlipX) != 0, (tileFlags & Map::eFlipY) != 0);
						}
					}
				}

				//Place on map
				//m_project->GetMap().SetTile(mapX, mapY, tileId);
				//m_project->GetMap().SetTileFlags(mapX, mapY, tileFlags);

				//Draw on canvas
				//PaintStamp(*m_clipboard, m_clonePastePos.x, m_clonePastePos.y);
			}
		}
		}

		//Update preview tile pos
		m_previewTilePos.x = x;
		m_previewTilePos.y = y;
	}
	else
	{
		//Mouse of of map range, invalidate preview tile
		m_previewTile = InvalidTileId;
	}

	//Refresh
	Refresh();
}

void MapPanel::RenderCanvas(ion::render::Renderer& renderer, const ion::Matrix4& cameraInverseMtx, const ion::Matrix4& projectionMtx, float& z, float zOffset)
{
	const Map& map = m_project->GetMap();
	const int mapWidth = map.GetWidth();
	const int mapHeight = map.GetHeight();
	const int tileWidth = 8;
	const int tileHeight = 8;
	const int quadHalfExtentsX = 4;
	const int quadHalfExtentsY = 4;

	//Draw preview tile
	if(m_previewTile)
	{
		//Set preview quad texture coords
		ion::render::TexCoord coords[4];
		GetTileTexCoords(m_previewTile, coords, m_previewTileFlipX, m_previewTileFlipY);
		m_previewPrimitive->SetTexCoords(coords);

		ion::Matrix4 previewQuadMtx;
		ion::Vector3 previewQuadPos(((m_previewTilePos.x - (mapWidth / 2)) * tileWidth) + quadHalfExtentsX,
			((mapHeight - 1 - m_previewTilePos.y - (mapHeight / 2)) * tileHeight) + quadHalfExtentsY, z);
		previewQuadMtx.SetTranslation(previewQuadPos);

		m_material->SetDiffuseColour(m_previewColour);
		m_material->Bind(previewQuadMtx, cameraInverseMtx, projectionMtx);
		renderer.DrawVertexBuffer(m_previewPrimitive->GetVertexBuffer(), m_previewPrimitive->GetIndexBuffer());
		m_material->Unbind();
	}

	z += zOffset;

	if(m_boxSelectStart.x >= 0 && m_boxSelectEnd.x >= 0)
	{
		//Draw overlay over box selection
		float bottom = min(mapHeight - 1 - m_boxSelectStart.y, mapHeight - 1 - m_boxSelectEnd.y);
		float left = min(m_boxSelectStart.x, m_boxSelectEnd.x);

		ion::Matrix4 boxMtx;
		ion::Vector3 boxScale((float)abs(m_boxSelectEnd.x - m_boxSelectStart.x) + 1.0f, (float)abs(m_boxSelectEnd.y - m_boxSelectStart.y) + 1.0f, 0.0f);
		ion::Vector3 boxPos(floor((left - (mapWidth / 2.0f) + (boxScale.x / 2.0f)) * tileWidth),
			floor((bottom - (mapHeight / 2.0f) + (boxScale.y / 2.0f)) * tileHeight), z);

		boxMtx.SetTranslation(boxPos);
		boxMtx.SetScale(boxScale);

		renderer.SetAlphaBlending(ion::render::Renderer::Translucent);
		m_selectionMaterial->Bind(boxMtx, cameraInverseMtx, projectionMtx);
		renderer.DrawVertexBuffer(m_previewPrimitive->GetVertexBuffer(), m_previewPrimitive->GetIndexBuffer());
		m_selectionMaterial->Unbind();
		renderer.SetAlphaBlending(ion::render::Renderer::NoBlend);
	}
	else if(m_selectedTiles.size() > 0)
	{
		//Draw overlay over selected tiles
		ion::Matrix4 selectionMtx;
		ion::Matrix4 worldViewProjMtx;
		ion::render::Shader::ParamHndl<ion::Matrix4> worldViewProjParamV = m_selectionVertexShader->CreateParamHndl<ion::Matrix4>("gWorldViewProjectionMatrix");

		renderer.SetAlphaBlending(ion::render::Renderer::Translucent);
		m_selectionMaterial->Bind(selectionMtx, cameraInverseMtx, projectionMtx);

		for(int i = 0; i < m_selectedTiles.size(); i++)
		{
			int x = m_selectedTiles[i].x;
			int y = m_selectedTiles[i].y;
			int y_inv = mapHeight - 1 - y;

			ion::Vector3 selectedQuadPos(((x - (mapWidth / 2)) * tileWidth) + quadHalfExtentsX,
				((y_inv - (mapHeight / 2)) * tileHeight) + quadHalfExtentsY, z);

			selectionMtx.SetTranslation(selectedQuadPos);
			worldViewProjMtx = selectionMtx * cameraInverseMtx * projectionMtx;
			worldViewProjParamV.SetValue(worldViewProjMtx);

			renderer.DrawVertexBuffer(m_previewPrimitive->GetVertexBuffer(), m_previewPrimitive->GetIndexBuffer());
		}

		m_selectionMaterial->Unbind();
		renderer.SetAlphaBlending(ion::render::Renderer::NoBlend);
	}

	z += zOffset;

	if(m_clipboard && m_clonePreviewPrimitive)
	{
		//Draw clipboard tiles
		float x = m_clonePastePos.x;
		float y_inv = mapHeight - 1 - m_clonePastePos.y;
		float width = m_clipboard->GetWidth();
		float height_inv = -m_clipboard->GetHeight();

		ion::Matrix4 clonePreviewMtx;
		ion::Vector3 clonePreviewPos(floor((x - (mapWidth / 2.0f) + (width / 2.0f)) * tileWidth),
			floor((y_inv - (mapHeight / 2.0f) + ((height_inv / 2.0f) + 1.0f)) * tileHeight), z);
		clonePreviewMtx.SetTranslation(clonePreviewPos);

		renderer.SetAlphaBlending(ion::render::Renderer::Translucent);
		renderer.SetDepthTest(ion::render::Renderer::Always);

		m_material->SetDiffuseColour(m_clonePreviewColour);
		m_material->Bind(clonePreviewMtx, cameraInverseMtx, projectionMtx);
		renderer.DrawVertexBuffer(m_clonePreviewPrimitive->GetVertexBuffer(), m_clonePreviewPrimitive->GetIndexBuffer());
		m_material->Unbind();
		m_material->SetDiffuseColour(ion::Colour(1.0f, 1.0f, 1.0f, 1.0f));

		renderer.SetDepthTest(ion::render::Renderer::LessEqual);
		renderer.SetAlphaBlending(ion::render::Renderer::NoBlend);
	}
}