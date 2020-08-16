#include "stdafx.h"
#include "tile.h"

HRESULT tile::init()
{
	_tileSize[0] = 32;
	_tileSize[1] = 18;
	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _tileSize[0] * TILESIZE - WINSIZEX, _tileSize[1] * TILESIZE - WINSIZEY);


	imageLoad();
	{
		_sampleTileUI.right = WINSIZEX;
		_sampleTileUI.bottom = WINSIZEY;
		_sampleTileUI.top = 0;
		_sampleTileUI.left = WINSIZEX - 550;


		_sampleTileOnOff.right = WINSIZEX;
		_sampleTileOnOff.left = _sampleTileOnOff.right - 20;
		_sampleTileOnOff.top = WINSIZEY / 2 - 50;
		_sampleTileOnOff.bottom = WINSIZEY / 2 + 50;
	}

	{
		_miniMap = RectMakePivot(Vector2(10, 10), Vector2(_tileSize[0] * TILESIZE * 0.05f, _tileSize[1] * TILESIZE * 0.05f), Pivot::LeftTop);
		_miniMapMove = RectMakePivot(Vector2(10, 10), Vector2(WINSIZEX * 0.05f, WINSIZEY * 0.05f), Pivot::LeftTop);
	}

	{
		_leftRightButton[0] = RectMakeCenter(WINSIZEX - 321, 230, 70, 70);
		_leftRightButton[1] = RectMakeCenter(WINSIZEX - 220, 230, 70, 70);
	}


	_button = new button;
	_button->init();
	setup();
	return S_OK;
}

void tile::render()
{
	if (_mapImg != NULL)
	{
		CAMERAMANAGER->render(_mapImg, 0, 0, 1);
	}

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;
			int index = (i + cullY) * _tileSize[0] + (j + cullX);
			if (index >= _tileSize[0] * _tileSize[1])
				continue;

			CAMERAMANAGER->rectangle(_vTile[index].rc, D2D1::ColorF::Black, 1.0f);
			if (_vTile[index].terrain != TR_NONE)
			{
				Vector2 vec((_vTile[index].rc.left + _vTile[index].rc.right) * 0.5f, (_vTile[index].rc.top + _vTile[index].rc.bottom) * 0.5f);

				CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("mapTiles"), vec.x, vec.y, _vTile[index].terrainFrameX, _vTile[index].terrainFrameY);
				//CAMERAMANAGER->addFrameRender(ImageManager::GetInstance()->FindImage("mapTiles"), )
			}
			if (KEYMANAGER->isToggleKey('V'))
			{
				if (_vTile[index].terrain == TR_WALL || _vTile[index].isColTile)
				{
					CAMERAMANAGER->fillRectangle(_vTile[index].rc, D2D1::ColorF::Red, 0.5f);
				}
			}


			if (_vTile[index].isDrag)
			{
				CAMERAMANAGER->rectangle(_vTile[index].rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
			}


		}
	}


	for (int i = 0; i < _vObject.size(); i++) // 오브젝트들 렌더
	{
		if (_vObject[i].isFrameRender)
		{
			CAMERAMANAGER->zOrderFrameRender(findImg(_vObject[i].type, _vObject[i].imgNumber), (_vObject[i].rc.left + _vObject[i].rc.right) * 0.5f, (_vObject[i].rc.top + _vObject[i].rc.bottom) * 0.5f,
				_vObject[i].rc.bottom, _vObject[i].frameX, 0, _vObject[i].scale, 1);

			_vObject[i].count++;
			_vObject[i].type == OBJ_NPC ? _frameCount = 5 : _frameCount = 10;
			if (_vObject[i].count % _frameCount == 0)
			{
				_vObject[i].count = 0;
				_vObject[i].frameX++;

				if (findImg(_vObject[i].type, _vObject[i].imgNumber)->GetMaxFrameX() <= _vObject[i].frameX)
				{
					_vObject[i].frameX = 0;
				}
			}

		}
		else
		{
			CAMERAMANAGER->zOrderRender(findImg(_vObject[i].type, _vObject[i].imgNumber), _vObject[i].rc.left, _vObject[i].rc.top, _vObject[i].rc.bottom, 1, _vObject[i].scale);
		}
		//CAMERAMANAGER->render(_object[i]->img, _object[i]->rc.left, _object[i]->rc.top, 0.4f);
		//CAMERAMANAGER->rectangle(_object[i]->rc, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}
	CAMERAMANAGER->zOrderALLRender();

	// 선택중인 렉트
	{
		CAMERAMANAGER->rectangle(_dragTile, D2D1::ColorF::LimeGreen, 1.0f, 5);
	}




	if (_isActive) //팔레트가 있을 때 
	{

		ImageManager::GetInstance()->FindImage("sampleUI")->Render(Vector2(_sampleTileUI.left, _sampleTileUI.top));

		// 팔레트
		if (_button->getType() == BUTTON_TERRAIN)
		{
			for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				D2DRenderer::GetInstance()->DrawRectangle(_sampleTile[i].rc, D2D1::ColorF::Black, 1.0f);
				Vector2 vec((_sampleTile[i].rc.left + _sampleTile[i].rc.right) * 0.5f, (_sampleTile[i].rc.top + _sampleTile[i].rc.bottom) * 0.5f);
				ImageManager::GetInstance()->FindImage("mapTiles")->FrameRender(vec, _sampleTile[i].terrainFrameX, _sampleTile[i].terrainFrameY);
			}
		}
		else if (_button->getType() == BUTTON_OBJECT)
		{
			if (_currentSampleObject == OBJ_HOUSE)
			{
				ImageManager::GetInstance()->FindImage("objectHouse")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_ARCHITECTURE)
			{
				ImageManager::GetInstance()->FindImage("objectArchitecture")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_DOOR)
			{
				ImageManager::GetInstance()->FindImage("objectDoor")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_PLANT)
			{
				ImageManager::GetInstance()->FindImage("objectPlant")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_NPC)
			{
				ImageManager::GetInstance()->FindImage("objectNPC")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_SPA)
			{
				ImageManager::GetInstance()->FindImage("objectSpa")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_DUN1)
			{
				ImageManager::GetInstance()->FindImage("objectDungeon1")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
			else if (_currentSampleObject == OBJ_DUN2)
			{
				ImageManager::GetInstance()->FindImage("objectDungeon2")->Render(Vector2(WINSIZEX - 505.0f, WINSIZEY * 0.5f - 70));
			}
		}


		_button->render();

		if (_button->getType() == BUTTON_TERRAIN)
			D2DRenderer::GetInstance()->DrawRectangle(_currentRect, D2D1::ColorF::LimeGreen, 1.0f, 5);
		// ------------------ 마지막 렌더 ------------------------------------ 

	}


	// 드래그 할때 생기는 렉트
	if (_drag.isDraw)
	{
		CAMERAMANAGER->rectangle(_drag.rc, D2D1::ColorF::SteelBlue, 1, 1);
		CAMERAMANAGER->fillRectangle(_drag.rc, D2D1::ColorF::SteelBlue, 0.5f);
	}

	// 미니맵
	D2DRenderer::GetInstance()->FillRectangle(_miniMap, D2D1::ColorF::Silver, 0.5f);
	D2DRenderer::GetInstance()->DrawRectangle(_miniMapMove, D2D1::ColorF::Black, 1, 2);

	if (_isSelectObject)
	{
		findImg(_currentObject.type, _currentObject.imgNumber)->SetAlpha(0.5f);
		if (_currentObject.isFrameRender)
		{
			_currentObject.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, findImg(_currentObject.type, _currentObject.imgNumber)->GetFrameSize().x *_currentObject.scale,
				findImg(_currentObject.type, _currentObject.imgNumber)->GetFrameSize().y * _currentObject.scale);
			findImg(_currentObject.type, _currentObject.imgNumber)->FrameRender(Vector2((_currentObject.rc.left + _currentObject.rc.right) * 0.5f, (_currentObject.rc.top + _currentObject.rc.bottom) * 0.5f), 1, 0, _currentObject.scale);
		}
		else
		{
			_currentObject.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, findImg(_currentObject.type, _currentObject.imgNumber)->GetWidth() * _currentObject.scale,
				findImg(_currentObject.type, _currentObject.imgNumber)->GetHeight() * _currentObject.scale);
			findImg(_currentObject.type, _currentObject.imgNumber)->Render(Vector2(_currentObject.rc.left, _currentObject.rc.top), _currentObject.scale);
		}



		D2DRenderer::GetInstance()->FillRectangle(_currentObject.rc, D2D1::ColorF::LimeGreen, 0.4f);

	}

	// 팔레트 껐다켰다하는 렉트
	ImageManager::GetInstance()->FindImage("sampleUIOnOff")->Render(Vector2(_sampleTileOnOff.left, _sampleTileOnOff.top));
}

void tile::update()
{
	mapMove();
	setMap();
	drag();
	saveLoad();
	autoTile();
}

void tile::release()
{
}

void tile::drag()
{
	// ---------------- 시작점 --------------------- //
	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
	{
		int size = _sampleTileUI.right - _sampleTileUI.left;
		_drag.isDraw = true;
		_drag.startPos = _ptMouse;
		_drag.startPos.x += CAMERAMANAGER->getLeft();
		_drag.startPos.y += CAMERAMANAGER->getTop();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT))
	{
		_drag.isDraw = true;
		_drag.endPos = _ptMouse;
		_drag.endPos.x += CAMERAMANAGER->getLeft();
		_drag.endPos.y += CAMERAMANAGER->getTop();

		if (_drag.startPos.x < _drag.endPos.x && _drag.startPos.y < _drag.endPos.y)
		{
			_drag.rc.left = _drag.startPos.x;
			_drag.rc.top = _drag.startPos.y;
			_drag.rc.right = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.bottom = _ptMouse.y + CAMERAMANAGER->getTop();
		}
		else if (_drag.startPos.x > _drag.endPos.x && _drag.startPos.y < _drag.endPos.y)
		{
			_drag.rc.left = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.top = _drag.startPos.y;
			_drag.rc.right = _drag.startPos.x;
			_drag.rc.bottom = _ptMouse.y + CAMERAMANAGER->getTop();
		}
		else if (_drag.startPos.x < _drag.endPos.x && _drag.startPos.y > _drag.endPos.y)
		{
			_drag.rc.left = _drag.startPos.x;
			_drag.rc.top = _ptMouse.y + CAMERAMANAGER->getTop();
			_drag.rc.right = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.bottom = _drag.startPos.y;
		}
		else
		{
			_drag.rc.left = _ptMouse.x + CAMERAMANAGER->getLeft();
			_drag.rc.top = _ptMouse.y + CAMERAMANAGER->getTop();
			_drag.rc.right = _drag.startPos.x;
			_drag.rc.bottom = _drag.startPos.y;
		}

		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			if (isCollision(_drag.rc, _vTile[i].rc))
			{
				_vTile[i].isDrag = true;
			}
			else
			{
				_vTile[i].isDrag = false;
			}
		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))
	{
		_drag.isDraw = false;


		if (_button->getType() == BUTTON_ERASE_OBJECT)
		{
			for (int i = 0; i < _vObject.size(); i++)
			{
				if (isCollision(_drag.rc, _vObject[i].rc))
				{
					eraseObject(i);
				}
			}
		}


		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			if (isCollision(_drag.rc, _vTile[i].rc))
			{
				if (_button->getType() == BUTTON_TERRAIN)
				{
					_vTile[i].terrainFrameX = _currentTile.x;
					_vTile[i].terrainFrameY = _currentTile.y;
					_vTile[i].isColTile = false;
					_vTile[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}

				else if (_button->getType() == BUTTON_ERASE_TERRAIN)
				{
					_vTile[i].isColTile = false;
					_vTile[i].terrain = TR_NONE;
				}
				else if (_button->getType() == BUTTON_COLLISION)
				{
					_vTile[i].isColTile = true;
				}


			}
			_vTile[i].isDrag = false;
		}

	}

}

void tile::setup()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		_sampleTile[i].terrainFrameX = i % SAMPLETILEX;
		_sampleTile[i].terrainFrameY = i / SAMPLETILEX;

		_sampleTile[i].rc = RectMake(WINSIZEX / 2 + 275 + _sampleTile[i].terrainFrameX * TILESIZE * 1.1f, WINSIZEY / 2 - 80 + _sampleTile[i].terrainFrameY * TILESIZE * 1.1f, TILESIZE, TILESIZE);
	}

	for (int i = 0; i < 4; i++)
	{
		_sampleObject[i].rc = RectMake(WINSIZEX - 505.0f + (i % 2) * 225, WINSIZEY * 0.5f - 70 + (i / 2) * 225, 225, 225);
	}


	for (int i = 0; i < _tileSize[1]; i++)
	{
		for (int j = 0; j < _tileSize[0]; j++)
		{
			tagTile temp;
			temp.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
			temp.isDrag = false;
			temp.idX = j;
			temp.idY = i;
			temp.isColTile = false;
			_vTile.push_back(temp);
		}
	}


	for (int i = 0; i < _tileSize[1] * _tileSize[0]; ++i)
	{
		_vTile[i].terrainFrameX = 8;
		_vTile[i].terrainFrameY = 4;
		_vTile[i].terrain = terrainSelect(_vTile[i].terrainFrameX, _vTile[i].terrainFrameY);
	}
}

void tile::setMap()
{
	POINT pt = _ptMouse;
	pt.x += CAMERAMANAGER->getLeft();
	pt.y += CAMERAMANAGER->getTop();
	sampleOnOff();

	// 선택할 때 범위
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_isActive)
		{
			if (_button->getType() == BUTTON_TERRAIN)
			{
				for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
				{
					if (PtInRect(&_sampleTile[i].rc, _ptMouse))
					{
						_currentTile.x = _sampleTile[i].terrainFrameX;
						_currentTile.y = _sampleTile[i].terrainFrameY;
						_currentRect = RectMake(_sampleTile[i].rc.left, _sampleTile[i].rc.top, TILESIZE, TILESIZE);
						break;
					}
				}
			}
			else if (_button->getType() == BUTTON_OBJECT)
			{
				for (int i = 0; i < 2; i++) // 왼쪽 오른쪽 버튼 눌렀을 때
				{
					if (PtInRect(&_leftRightButton[i], _ptMouse))
					{
						if (i == 0)
						{
							int num = (int)_currentSampleObject;
							num--;
							if (num < 0) num = 0;
							_currentSampleObject = (OBJECT)num;
						}
						else
						{
							int num = (int)_currentSampleObject;
							num++;
							if (num > (int)OBJ_NONE - 1) num = (int)OBJ_NONE - 1;
							_currentSampleObject = (OBJECT)num;
						}
						break;
					}
				}
				selectObject();
			}


			_button->update();
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (_button->getType() == BUTTON_COLLISION)
		{
			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 33; j++)
				{
					int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
					int cullY = CAMERAMANAGER->getTop() / TILESIZE;
					int index = (i + cullY) * _tileSize[0] + (j + cullX);
					if (index >= _tileSize[0] * _tileSize[1])
						continue;
					if (PtInRect(&_vTile[index].rc, pt))
					{
						_vTile[index].isColTile = false;
						break;
					}
				}
			}
		}

	}



	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{

		if (_button->getType() == BUTTON_ERASE_OBJECT)
		{
			for (int i = 0; i < _vObject.size(); i++)
			{
				if (PtInRect(&_vObject[i].rc, pt))
				{
					eraseObject(i);
					break;
				}
			}
		}

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 33; j++)
			{
				int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
				int cullY = CAMERAMANAGER->getTop() / TILESIZE;

				int index = (i + cullY) * _tileSize[0] + (j + cullX);
				if (index >= _tileSize[0] * _tileSize[1])
					continue;

				if (PtInRect(&_vTile[index].rc, pt))
				{
					if (_isActive)
					{
						if (_ptMouse.x >= WINSIZEX - 618) break;
					}

					if (_button->getType() == BUTTON_TERRAIN)
					{
						_vTile[index].terrainFrameX = _currentTile.x;
						_vTile[index].terrainFrameY = _currentTile.y;
						_vTile[index].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					}
					else if (_button->getType() == BUTTON_OBJECT)
					{
						if (_isSelectObject)
						{
							int w = (_currentObject.rc.right - _currentObject.rc.left) / 2;
							int h = (_currentObject.rc.bottom - _currentObject.rc.top) / 2;
							tagObject tempObject = _currentObject;
							tempObject.rc.left = pt.x - w;
							tempObject.rc.top = pt.y - h;
							tempObject.frameX = 0;

							if (tempObject.isFrameRender)
							{
								tempObject.rc.right = tempObject.rc.left + findImg(tempObject.type, tempObject.imgNumber)->GetFrameSize().x * tempObject.scale;
								tempObject.rc.bottom = tempObject.rc.top + findImg(tempObject.type, tempObject.imgNumber)->GetFrameSize().y * tempObject.scale;
							}
							else
							{
								tempObject.rc.right = tempObject.rc.left + findImg(tempObject.type, tempObject.imgNumber)->GetWidth() * tempObject.scale;
								tempObject.rc.bottom = tempObject.rc.top + findImg(tempObject.type, tempObject.imgNumber)->GetHeight() * tempObject.scale;
							}
							_vObject.push_back(tempObject);
							_isSelectObject = false;
						}
					}
					else if (_button->getType() == BUTTON_ERASE_TERRAIN)
					{
						_vTile[index].terrain = TR_NONE;
						_vTile[index].isColTile = false;
					}

					break;
				}

			}
		}

	}
	// 지금 렉트 검사
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 33; j++)
		{
			int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
			int cullY = CAMERAMANAGER->getTop() / TILESIZE;

			int index = (i + cullY) * _tileSize[0] + (j + cullX);
			if (index >= _tileSize[0] * _tileSize[1])
				continue;
			if (PtInRect(&_vTile[index].rc, pt))
			{
				_dragTile = RectMake(_vTile[index].rc.left, _vTile[index].rc.top, TILESIZE, TILESIZE);
				_nowIndex = index;
				break;
			}
		}
	}
}

void tile::saveLoad()
{
	saveMap();
	loadMap();
}

void tile::imageLoad()
{
	//ImageManager::GetInstance()

	ImageManager::GetInstance()->AddImage("objectPlant", L"Object/objectPlant.png");

	ImageManager::GetInstance()->AddImage("objectNPC", L"Object/objectNPC.png");
	ImageManager::GetInstance()->AddImage("object_door1", L"Object/object_door1.png");
	ImageManager::GetInstance()->AddImage("object_door2", L"Object/object_door2.png");
	ImageManager::GetInstance()->AddImage("object_door3", L"Object/object_door3.png");
	ImageManager::GetInstance()->AddImage("object_door4", L"Object/object_door4.png");
	ImageManager::GetInstance()->AddImage("objectSpa", L"Object/objectSpa.png");
	ImageManager::GetInstance()->AddImage("plant_flower", L"Object/plant_flower.png");
	ImageManager::GetInstance()->AddImage("spa", L"Object/spa.png");

	ImageManager::GetInstance()->AddFrameImage("plant_tree1", L"Object/plant_tree1.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_tree2", L"Object/plant_tree2.png", 35, 1);
	ImageManager::GetInstance()->AddFrameImage("plant_fountain1", L"Object/plant_fountain1.png", 9, 1);
	ImageManager::GetInstance()->AddFrameImage("Object_build_Bottom1", L"Object/Object_build_Bottom1.png", 53, 1);

	ImageManager::GetInstance()->AddFrameImage("npc_1", L"Object/npc_1.png", 17, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_2", L"Object/npc_2.png", 54, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_3", L"Object/npc_3.png", 24, 1);
	ImageManager::GetInstance()->AddFrameImage("npc_4", L"Object/npc_4.png", 49, 1);

	ImageManager::GetInstance()->AddImage("objectDungeon1", L"Object/objectDungeon1.png");
	ImageManager::GetInstance()->AddImage("objectDungeon2", L"Object/objectDungeon2.png");
	ImageManager::GetInstance()->AddImage("object_skull1", L"Object/skull1.png");
	ImageManager::GetInstance()->AddImage("object_skull2", L"Object/skull2.png");
	ImageManager::GetInstance()->AddImage("object_skull3", L"Object/skull3.png");
	ImageManager::GetInstance()->AddImage("object_pot", L"Object/pot.png");
	ImageManager::GetInstance()->AddImage("object_pot_slime", L"Object/pot_slime.png");
	ImageManager::GetInstance()->AddImage("object_pillar", L"Object/pillar.png");
	ImageManager::GetInstance()->AddImage("object_smallRock", L"Object/smallRock.png");
	ImageManager::GetInstance()->AddImage("object_smallRock_slime", L"Object/smallRock_slime.png");


}

void tile::loadMap()
{
	if (_button->getType() == BUTTON_LOAD_TOWN || _button->getType() == BUTTON_LOAD_BOSS
		|| _button->getType() == BUTTON_LOAD_SHOP || _button->getType() == BUTTON_LOAD_DUNGEON || _button->getType() == BUTTON_LOAD_ENTERENCE)
	{
		HANDLE file;
		DWORD read;
		int size[2];
		const char* fileName;
		fileName = "";
		if (_button->getType() == BUTTON_LOAD_TOWN)
		{
			_currentLoadType = 1;
			_mapImg = ImageManager::GetInstance()->AddImage("townMap", L"Image/Map/townMap.png");
			fileName = "townMap.map";
		}
		else if (_button->getType() == BUTTON_LOAD_BOSS)
		{
			_currentLoadType = 2;
			_mapImg = ImageManager::GetInstance()->AddImage("bossRoom1", L"Image/map/bossRoom1.png");
			fileName = "boss.map";
		}
		else if (_button->getType() == BUTTON_LOAD_SHOP)
		{
			_currentLoadType = 3;
			_mapImg = ImageManager::GetInstance()->AddImage("shop_background", L"Image/Shop/shop_background.png");
			fileName = "shop.map";
		}
		else if (_button->getType() == BUTTON_LOAD_DUNGEON)
		{
			_currentLoadType = 4;
			_mapImg = NULL;
			fileName = "dungeon3.map";
		}
		else if (_button->getType() == BUTTON_LOAD_ENTERENCE)
		{
			_currentLoadType = 5;
			_mapImg = NULL;
			fileName = "dungeonEnterence.map";
		}
		if (_vTile.size() > 0)
			_vTile.clear();
		if (_vObject.size() > 0)
			_vObject.clear();

		file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _tileSize, sizeof(int) * 2, &read, NULL);

		tagTile* temTile = new tagTile[_tileSize[0] * _tileSize[1]];
		ReadFile(file, temTile, sizeof(tagTile) * _tileSize[0] * _tileSize[1], &read, NULL);

		for (int i = 0; i < _tileSize[0] * _tileSize[1]; i++)
		{
			_vTile.push_back(temTile[i]);
		}

		ReadFile(file, size, sizeof(int) * 2, &read, NULL);

		// ------------ 오브젝트		
		tagObject* temp = new tagObject[size[1]];
		ReadFile(file, temp, sizeof(tagObject) * size[1], &read, NULL);
		for (int i = 0; i < size[1]; i++)
		{
			_vObject.push_back(temp[i]);
		}

		CloseHandle(file);


		_miniMap = RectMakePivot(Vector2(10, 10), Vector2(_tileSize[0] * TILESIZE * 0.05f, _tileSize[1] * TILESIZE * 0.05f), Pivot::LeftTop);
		_miniMapMove = RectMakePivot(Vector2(10, 10), Vector2(WINSIZEX * 0.05f, WINSIZEY * 0.05f), Pivot::LeftTop);
		CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, _tileSize[0] * TILESIZE - WINSIZEX, _tileSize[1] * TILESIZE - WINSIZEY);
		_button->setType(BUTTON_TERRAIN);

	}
}

void tile::saveMap()
{
	if (_currentLoadType == 0) return;
	if (_button->getType() == BUTTON_SAVE_TOWN || _button->getType() == BUTTON_SAVE_BOSS
		|| _button->getType() == BUTTON_SAVE_SHOP || _button->getType() == BUTTON_SAVE_DUNGEON || _button->getType() == BUTTON_SAVE_ENTERENCE)
	{
		_saveTime++;
	}

	if (_saveTime > 50)
	{
		HANDLE file;
		DWORD write;
		const char* fileName;
		fileName = "";
		if (_button->getType() == BUTTON_SAVE_TOWN)
		{
			if (_currentLoadType != 1)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 60;
			_tileSize[1] = 49;

			fileName = "townMap.map";
		}
		else if (_button->getType() == BUTTON_SAVE_BOSS)
		{
			if (_currentLoadType != 2)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 60;
			_tileSize[1] = 41;

			fileName = "boss.map";
		}
		else if (_button->getType() == BUTTON_SAVE_SHOP)
		{
			if (_currentLoadType != 3)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 32;
			_tileSize[1] = 28;

			fileName = "shop.map";
		}
		else if (_button->getType() == BUTTON_SAVE_DUNGEON)
		{
			if (_currentLoadType != 4)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 32;
			_tileSize[1] = 18;

			fileName = "dungeon3.map";
		}
		else if (_button->getType() == BUTTON_SAVE_ENTERENCE)
		{
			if (_currentLoadType != 5)
			{
				_saveTime = 0;
				_button->setType(BUTTON_TERRAIN);
				return;
			}
			_tileSize[0] = 32;
			_tileSize[1] = 18;

			fileName = "dungeonEnterence.map";
		}
		// ----------------- 타일 ----------------- //
		tagTile* tempTile = new tagTile[_tileSize[0] * _tileSize[1]];
		for (int i = 0; i < _vTile.size(); i++)
		{
			tempTile[i] = _vTile[i];
		}
		// ----------------- 타일 ----------------- //
		// ----------------- 오브젝트 ----------------- //
		int size[2] = { 1,_vObject.size() };
		tagObject* temp = new tagObject[_vObject.size()];
		for (int i = 0; i < _vObject.size(); i++)
		{
			temp[i] = _vObject[i];
		}
		// ----------------- 오브젝트 ----------------- //
		file = CreateFile(fileName, GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


		WriteFile(file, _tileSize, sizeof(int) * 2, &write, NULL);
		WriteFile(file, tempTile, sizeof(tagTile) * _tileSize[0] * _tileSize[1], &write, NULL);
		WriteFile(file, size, sizeof(int) * 2, &write, NULL);
		WriteFile(file, temp, sizeof(tagObject) * _vObject.size(), &write, NULL);


		CloseHandle(file);


		_saveTime = 0;
		_button->setType(BUTTON_TERRAIN);
	}

}

void tile::selectObject()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_sampleObject[i].rc, _ptMouse))
		{
			_currentObject.scale = 1;
			_currentObject.type = _currentSampleObject;
			_isSelectObject = true;
			_currentObject.imgNumber = i;
			if (_currentSampleObject == OBJ_HOUSE)
			{
				_currentObject.isFrameRender = false;
				if (i == 0)
				{
					_currentObject.scale = 1.7f;
					_currentObject.isFrameRender = true;
				}

				else if (i == 2)
				{
					_currentObject.scale = 1.2f;
				}
				break;
			}

			else if (_currentSampleObject == OBJ_ARCHITECTURE)
			{
				_currentObject.isFrameRender = false;
				if (i == 2)
				{
					_currentObject.scale = 5.0f;
				}

				break;
			}
			else if (_currentSampleObject == OBJ_DOOR)
			{
				_currentObject.isFrameRender = false;
				break;
			}
			else if (_currentSampleObject == OBJ_PLANT)
			{
				_currentObject.isFrameRender = true;
				if (i == 0)
				{
					_currentObject.scale = 1.5f;
				}
				if (i == 1)
				{
					_currentObject.scale = 2.5f;
				}
				if (i == 2)
				{
					_currentObject.scale = 1.5f;
				}
				if (i == 3)
				{
					_currentObject.scale = 2.3f;
					_currentObject.isFrameRender = false;
				}

				break;
			}
			else if (_currentSampleObject == OBJ_NPC)
			{
				_currentObject.isFrameRender = true;
				break;
			}
			else if (_currentSampleObject == OBJ_SPA)
			{
				_currentObject.isFrameRender = false;
				break;
			}
			else if (_currentSampleObject == OBJ_DUN1)
			{
				_currentObject.isFrameRender = false;
				break;
			}
			else if (_currentSampleObject == OBJ_DUN2)
			{
				_currentObject.isFrameRender = false;
				if (i == 1)
				{
					_currentObject.scale = 2.0f;
				}
				break;
			}
		}

	}
}

void tile::eraseObject(int arrNum)
{
	_vObject.erase(_vObject.begin() + arrNum);
}

void tile::autoTile()
{
	if (_button->getType() == BUTTON_AUTO)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 33; j++)
			{
				int cullX = CAMERAMANAGER->getLeft() / TILESIZE;
				int cullY = CAMERAMANAGER->getTop() / TILESIZE;
				int index = (i + cullY) * _tileSize[0] + (j + cullX);
				if (index >= _tileSize[0] * _tileSize[1])
					continue;
				_autoCalc = 0;
				autoTileType(index, TR_GRASS);
				autoTileType(index, TR_CEMENT);
		
			}
		}
		_button->setType(BUTTON_TERRAIN);
	}

}

void tile::autoTileType(int idx,TERRAIN type)
{
	if (_vTile[idx].terrain == type)
	{
		if (_vTile[idx - _tileSize[0]].terrain == type) // 위쪽이 잔디
		{
			_autoCalc += 1;
		}
		if (_vTile[idx + 1].terrain == type)
		{
			_autoCalc += 2;
		}
		if (_vTile[idx + _tileSize[0]].terrain == type)
		{
			_autoCalc += 4;
		}
		if (_vTile[idx - 1].terrain == type)
		{
			_autoCalc += 8;
		}

		if (_autoCalc == 0)
		{
			_vTile[idx].terrainFrameX = 8;
		}
		else if (_autoCalc == 1)
		{
			_vTile[idx].terrainFrameX = 3;
		}
		else if (_autoCalc == 2)
		{
			_vTile[idx].terrainFrameX = 1;
		}
		else if (_autoCalc == 4)
		{
			_vTile[idx].terrainFrameX = 7;
		}
		else if (_autoCalc == 8)
		{
			_vTile[idx].terrainFrameX = 5;
		}
		else if (_autoCalc == 3)
		{
			_vTile[idx].terrainFrameX = 2;
		}
		else if (_autoCalc == 6)
		{
			_vTile[idx].terrainFrameX = 0;
		}
		else if (_autoCalc == 12)
		{
			_vTile[idx].terrainFrameX = 6;
		}
		else if (_autoCalc == 9)
		{
			_vTile[idx].terrainFrameX = 4;
		}
		else if (_autoCalc == 7)
		{
			_vTile[idx].terrainFrameX = 1;
		}
		else if (_autoCalc == 14)
		{
			_vTile[idx].terrainFrameX = 7;
		}
		else if (_autoCalc == 13)
		{
			_vTile[idx].terrainFrameX = 5;
		}
		else if (_autoCalc == 11)
		{
			_vTile[idx].terrainFrameX = 3;
		}

		else if (_autoCalc == 15)
		{
			_vTile[idx].terrainFrameX = 8;
		}
		_autoCalc = 0;
	}


}

void tile::mapMove()
{
	if (KEYMANAGER->isStayKeyDown('W'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 10);
	if (KEYMANAGER->isStayKeyDown('S'))	CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 10);
	if (KEYMANAGER->isStayKeyDown('A'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10);
	if (KEYMANAGER->isStayKeyDown('D'))	CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10);

	float x = CAMERAMANAGER->getLeft() * 0.05f;
	float y = CAMERAMANAGER->getTop() * 0.05f;
	_miniMapMove = RectMakePivot(Vector2(10 + x, 10 + y), Vector2(WINSIZEX * 0.05f, WINSIZEY * 0.05f), Pivot::LeftTop);
}

void tile::sampleOnOff()
{
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_isActive = !_isActive;
	}



	if (_isActive)
	{
		_sampleTileOnOff.right = _sampleTileUI.left;
		_sampleTileOnOff.left = _sampleTileOnOff.right - 20;
	}
	else
	{
		_sampleTileOnOff.right = WINSIZEX;
		_sampleTileOnOff.left = WINSIZEX - 20;
	}
}


TERRAIN tile::terrainSelect(int frameX, int frameY)
{
	for (int i = 0; i < 9; i++)
	{
		// 첫번째 줄
		if (frameX == 8 && frameY == 0) return TR_FLOOR;
		else if (frameX == i && frameY == 0) return TR_WALL;

		// 두번째 줄
		if (frameX == i && frameY == 1) return TR_CEMENT;

		// 세번째 줄
		if (frameX == i && frameY == 2) return TR_GRASS;

		// 네번째 줄
		if (frameX == i && frameY == 3) return TR_GRASS;

		// 다섯번째 줄
		if (frameX == 8 && frameY == 4) return TR_NONE;
		else if (frameX == i && frameY == 4) return TR_GRASS;
	}

	return TR_NONE;
}

Image * tile::findImg(OBJECT type, int imgNum)
{
	Image* img = ImageManager::GetInstance()->FindImage("plant_tree1");
	if (type == OBJ_HOUSE)
	{
		if (imgNum == 0)			         img = ImageManager::GetInstance()->FindImage("Object_build_Bottom1");
		else if (imgNum == 1)		         img = ImageManager::GetInstance()->FindImage("build_Bottom2");
		else if (imgNum == 2)		         img = ImageManager::GetInstance()->FindImage("build_Shop");
		else if (imgNum == 3)		         img = ImageManager::GetInstance()->FindImage("build_Enchant");

	}
	else if (type == OBJ_ARCHITECTURE)
	{
		if (imgNum == 0)			         img = ImageManager::GetInstance()->FindImage("build_Well");
		else if (imgNum == 1)		         img = ImageManager::GetInstance()->FindImage("buildBoard");
		else if (imgNum == 2)		         img = ImageManager::GetInstance()->FindImage("build_fountain");
		else if (imgNum == 3)		         img = ImageManager::GetInstance()->FindImage("bench");
	}
	else if (type == OBJ_DOOR)
	{
		if (imgNum == 0)					 img = ImageManager::GetInstance()->FindImage("object_door1");
		else if (imgNum == 1)				 img = ImageManager::GetInstance()->FindImage("object_door2");
		else if (imgNum == 2)				 img = ImageManager::GetInstance()->FindImage("object_door3");
		else if (imgNum == 3)				 img = ImageManager::GetInstance()->FindImage("object_door4");
	}
	else if (type == OBJ_PLANT)
	{

		if (imgNum == 0)			          img = ImageManager::GetInstance()->FindImage("plant_tree1");
		else if (imgNum == 1)		          img = ImageManager::GetInstance()->FindImage("plant_fountain1");
		else if (imgNum == 2)		          img = ImageManager::GetInstance()->FindImage("plant_tree2");
		else if (imgNum == 3)		          img = ImageManager::GetInstance()->FindImage("plant_flower");
	}
	else if (type == OBJ_NPC)
	{
		if (imgNum == 0)		              img = ImageManager::GetInstance()->FindImage("npc_1");
		else if (imgNum == 1)	              img = ImageManager::GetInstance()->FindImage("npc_2");
		else if (imgNum == 2)	              img = ImageManager::GetInstance()->FindImage("npc_3");
		else if (imgNum == 3)	              img = ImageManager::GetInstance()->FindImage("npc_4");
	}
	else if (type == OBJ_SPA)
	{
		if (imgNum == 0 || imgNum == 1 || imgNum == 2 || imgNum == 3)			img = ImageManager::GetInstance()->FindImage("spa");

	}
	else if (type == OBJ_DUN1)
	{
		if (imgNum == 0)		              img = ImageManager::GetInstance()->FindImage("object_skull1");
		else if (imgNum == 1)	              img = ImageManager::GetInstance()->FindImage("object_skull2");
		else if (imgNum == 2)	              img = ImageManager::GetInstance()->FindImage("object_skull3");
		else if (imgNum == 3)	              img = ImageManager::GetInstance()->FindImage("object_pot");
	}
	else if (type == OBJ_DUN2)
	{
		if (imgNum == 0)		              img = ImageManager::GetInstance()->FindImage("object_pot_slime");
		else if (imgNum == 1)	              img = ImageManager::GetInstance()->FindImage("object_pillar");
		else if (imgNum == 2)	              img = ImageManager::GetInstance()->FindImage("object_smallRock");
		else if (imgNum == 3)	              img = ImageManager::GetInstance()->FindImage("object_smallRock_slime");
	}

	return img;
}
