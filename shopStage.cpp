#include "stdafx.h"
#include "shopStage.h"

HRESULT shopStage::init()
{
	_backGround = ImageManager::GetInstance()->AddImage("shop_background", L"Image/Shop/shop_background.png");
	ImageManager::GetInstance()->AddImage("shop_mid", L"Image/Shop/shop_mid.png");
	ImageManager::GetInstance()->AddImage("shop_first", L"Image/Shop/shop_first.png");
	ImageManager::GetInstance()->AddFrameImage("shop_door", L"Image/Shop/shop_door.png",5,1);

	CAMERAMANAGER->settingCamera(0, 0, WINSIZEX, WINSIZEY, 0, 0, 1600 - WINSIZEX, 1400 - WINSIZEY);

	_player = new player;
	_player->init();

	_shopNPC = new shopNPC;
	_shopNPC->init();
	
	_im = new itemManager;
	_im->init();

	//_im->setItem()
	disPlaySet();

	_doorFrameTimer = 0;
	_doorIndex = 0;

	return S_OK;
}

void shopStage::render()
{
	CAMERAMANAGER->render(_backGround, _backGround->GetWidth() / 2, 200, 1.15f, 1.0f);
	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================
	_player->render();
	_im->render();

	if(_enterNPC)
		_shopNPC->render();

	// ================================ 이 사이에 NPC, 플레이어 넣을것 ===================================
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_mid"), WINSIZEX / 2 - 55, 613, 1.15f, 1.0f);    
	CAMERAMANAGER->render(ImageManager::GetInstance()->FindImage("shop_first"), WINSIZEX / 2 - 65, 1162, 1.15f, 1.0f);
	CAMERAMANAGER->frameRender(ImageManager::GetInstance()->FindImage("shop_door"), WINSIZEX / 2 + 10, 1109, _doorIndex, 0 ,1.2f,1.f);
}

void shopStage::update()
{
	_player->update();
	_im->update();

	if(_enterNPC)
		_shopNPC->updadte();
	
	CAMERAMANAGER->setX(_player->getX());
	CAMERAMANAGER->setY(_player->getY());

	doorUpdate();
}

void shopStage::release()
{

}

void shopStage::disPlaySet()
{
	_display[0].init(Vector2(0, 0), NULL, 0, 0, false);
	_display[1].init(Vector2(0, 0), NULL, 0, 0, false);
	_display[2].init(Vector2(0, 0), NULL, 0, 0, false);
	_display[3].init(Vector2(0, 0), NULL, 0, 0, false);
}

void shopStage::disPlayUpdate()
{

}

void shopStage::doorUpdate()
{
	switch (_doorState)
	{
	case DOOR_CLOSE:
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_doorState = DOOR_OPENING;
		}
		break;
	case DOOR_OPENING:
		_doorFrameTimer++;
		if (_doorFrameTimer > 5)
		{
			_doorIndex++;

			if (_doorIndex == 4)
				_doorState = DOOR_DELAY;

			_doorFrameTimer = 0;
		}
		break;
	case DOOR_CLOSING:
		_doorFrameTimer++;

		if (_doorFrameTimer > 5)
		{
			_doorIndex--;

			if (_doorIndex == 0)
				_doorState = DOOR_CLOSE;

			_doorFrameTimer = 0;
		}
		break;
	case DOOR_DELAY:
		_enterNPC = true;
		_doorFrameTimer++;

		if (_doorFrameTimer > 130)
		{
			_doorState = DOOR_CLOSING;
			_doorFrameTimer = 0;
		}
		break;
	}
}
