#include "stdafx.h"
#include "shopNPC.h"

HRESULT shopNPC::init(npcType type, vector<POINT> vUnMove)
{
	// 이미지
	{
		_img = ImageManager::GetInstance()->AddFrameImage("npc1", L"Image/Shop/Guy.png", 8, 4);
		ImageManager::GetInstance()->AddImage("thinkBox", L"Image/Shop/thinkBox.png");
		_emotionImg = ImageManager::GetInstance()->AddFrameImage("thinking", L"Image/Shop/think.png", 3, 1);
		ImageManager::GetInstance()->AddFrameImage("TooCheap", L"Image/Shop/tooCheap.png", 13, 1);
		ImageManager::GetInstance()->AddFrameImage("Cheap", L"Image/Shop/Cheap.png", 4, 1);
		ImageManager::GetInstance()->AddFrameImage("TooExpensive", L"Image/Shop/tooExpensive.png", 9, 1);
		ImageManager::GetInstance()->AddFrameImage("Expensive", L"Image/Shop/expensive.png", 5, 1);
	}


	// 동적 할당
	{
		_aStar = new aStar;
		_item = new item;
	}

	// 변수 초기화
	{
		_centerX = 870;
		_centerY = 1180;
		_indexX = 0;
		_indexY = 3;
		_thinkBoxX = _centerX;
		_thinkBoxY = _centerY - 80;
		_emotionIndexX = 0;
		_frameTimer = 0;
		_delayTimer = 0;
		_emotionFrameTimer = 0;
		_angle = 0;
		_checkItemCount = 0;
		_rightPrice = 0;
		_selectPrice = 0;
		_settingPrice = 0;
		_rndChoiceItem = RND->getInt(4);
		_npcActionState = NPC_ENTER;
		_npcEmotionState = NPC_EMOTION_NULL;
		_npcType = type;
		_isBuy = false;
		_vUnMove = vUnMove;
	}

	// 초기화 함수
	{
		//unMoveSet();
		wayPointSet();
		chooseItem();
	}

	_aStar->init(WINSIZEX / 50, 1400 / 50, _centerX / 50, _centerY / 50 - 3, _goToPoint.x, _goToPoint.y, _vUnMove, true);

	_rc = RectMakePivot(Vector2(_centerX, _centerY), Vector2(_img->GetFrameSize().x, _img->GetFrameSize().y), Pivot::Center);


	return S_OK;
}

void shopNPC::release()
{
}

void shopNPC::updadte()
{
	directionCheck();

	_aStar->update(_centerX / 50, _centerY / 50, _goToPoint.x, _goToPoint.y);
	_item->setItemPos(_centerX, _centerY - 50);
	_item->update();

	//cout << _item->getIndex() << endl;

	_thinkBoxX = _centerX;
	_thinkBoxY = _centerY - 80;


	// NPC 행동에 따른 업데이트
	switch (_npcActionState)
	{
	case NPC_ENTER:
		frameUpdate();
		_angle = PI / 180 * 90;
		if (_centerY > 1000)
		{
			_centerY--;
		}
		else
		{
			_npcActionState = NPC_SHOPPING;
			_aStar->changeWayPoint();
		}
		break;

	case NPC_IDLE:
		frameUpdate();
		move();

		break;

	case NPC_SHOPPING:
		frameUpdate();
		move();

		break;

	case NPC_CHECKITEM:
		emotionFrameUpdate();
		if (_rndChoiceItem == 0 || _rndChoiceItem == 2)
		{
			_indexX = 0;
			_indexY = 0;
		}
		else if (_rndChoiceItem == 1 || _rndChoiceItem == 3)
		{
			_indexX = 0;
			_indexY = 3;
		}

		_delayTimer++;

		if (_delayTimer > 100)
		{
			comparePrice();
			// 구매했으면 BUY 상태로 바꿔라
			if (_isBuy)
			{
				_goToPoint = _counterPoint;
				_aStar->changeWayPoint();
				_npcActionState = NPC_BUY;
				_delayTimer = 0;
			}
			// 아니면 다시 쇼핑
			else
			{
				if (_delayTimer > 290 && _delayTimer < 292)
				{
					_isCheckEnd = true;
				}
				if (_delayTimer > 300)
				{
					if (_checkItemCount < 4)
						chooseItem();

					_npcActionState = NPC_SHOPPING;
					_npcEmotionState = NPC_EMOTION_NULL;
					_delayTimer = 0;
				}
			}
		}		
		break;
	case NPC_BUY:
		_delayTimer++;
		emotionFrameUpdate();
		_isBuy = false;
		if (_delayTimer < 200)
		{
			if (_rndChoiceItem == 0 || _rndChoiceItem == 2)
			{
				_indexX = 0;
				_indexY = 0;
			}
			else if (_rndChoiceItem == 1 || _rndChoiceItem == 3)
			{
				_indexX = 0;
				_indexY = 3;
			}
		}
		if (_delayTimer > 200)
		{
			_npcEmotionState = NPC_EMOTION_NULL;
			_isCheckEnd = true;
			frameUpdate();
			move();
		}
		break;
	case NPC_AWAY:
		frameUpdate();
		move();
		break;
	}


	_rc = RectMakePivot(Vector2(_centerX, _centerY), Vector2(50, 50), Pivot::Center);
}

void shopNPC::render()
{
	_aStar->render();

	CAMERAMANAGER->zOrderFrameRender(_img, _centerX, _centerY, _rc.bottom, _indexX, _indexY, 1.2f, 1.f);
	//CAMERAMANAGER->rectangle(_rc, D2D1::ColorF::Green, 1.f, 2.f);

	if (_npcEmotionState != NPC_EMOTION_NULL)
	{
		CAMERAMANAGER->zOrderRender(ImageManager::GetInstance()->FindImage("thinkBox"), _thinkBoxX, _thinkBoxY, _rc.bottom + _thinkBoxY, 1.f, 1.4f);
		CAMERAMANAGER->zOrderFrameRender(_emotionImg, _thinkBoxX + 18, _thinkBoxY + 17, _rc.bottom + _thinkBoxY + 17, _emotionIndexX, 0 , 1.4f,1.f);
	}

	if(_npcActionState == NPC_BUY && _item->getImg() != NULL)
		_item->cameraRender();
	
	if (KEYMANAGER->isToggleKey('V'))
	{
		CAMERAMANAGER->rectangle(_rc, D2D1::ColorF::Blue, 1.f, 2.f);
	}
}

void shopNPC::frameUpdate()
{
	_frameTimer++;
	if (_frameTimer > 10)
	{

		_indexX++;

		if (_indexX > _img->GetMaxFrameX() - 1)
		{
			_indexX = 0;
		}
		_frameTimer = 0;
	}
}

void shopNPC::emotionFrameUpdate()
{
	_emotionFrameTimer++;

	switch (_npcEmotionState)
	{
	case NPC_CHOOSE:
		if (_emotionFrameTimer > 15)
		{
			_emotionIndexX++;

			if (_emotionIndexX > _emotionImg->GetMaxFrameX() - 1)
			{
				_emotionIndexX = 0;
			}
			_emotionFrameTimer = 0;
		}
		break;
	case NPC_TOO_EXPENSIVE:
	case NPC_EXPENSIVE:
	case NPC_CHEAP:
	case NPC_TOO_CHEAP:
		if (_emotionFrameTimer > 5)
		{
			if (_emotionIndexX < _emotionImg->GetMaxFrameX() - 1)
			{
				_emotionIndexX++;
			}

			_emotionFrameTimer = 0;
		}
		break;
	}
}

void shopNPC::move()
{
	if (_aStar->getVShortest().size() > 0)
	{
		_angle = getAngle(_centerX, _centerY, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.x, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.y);

		// 이동 시켜줌
		_centerX += cosf(_angle);
		_centerY -= sinf(_angle);

		if (getDistance(_centerX, _centerY, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.x, _aStar->getVShortest()[_aStar->getMoveIndex()]->center.y) < 1)
		{
			if (_aStar->getMoveIndex() > 0)
				_aStar->setMoveIndex(_aStar->getMoveIndex() - 1);
		}

		if (getDistance(_centerX, _centerY, _aStar->getVShortest()[0]->center.x, _aStar->getVShortest()[0]->center.y) < 1)
		{
			if (_npcActionState == NPC_SHOPPING)
			{
				_npcActionState = NPC_CHECKITEM;
				_npcEmotionState = NPC_CHOOSE;
				_emotionImg = _emotionImg = ImageManager::GetInstance()->FindImage("thinking");
				_emotionIndexX = 0;
			}
			else if (_npcActionState == NPC_BUY)
			{
				_isCount = true;
				_npcActionState = NPC_AWAY;
				_goToPoint = _eixtPoint;
				_aStar->changeWayPoint();
			}
			else if (_npcActionState == NPC_AWAY)
			{
				_isAway = true;
			}
		}
	}
}

void shopNPC::comparePrice()
{
	// 아이템의 정보 중 적정가를 가져와서. 비교후 처리

	// 아이템 적정가와 플레이어 셋팅가격 차이 구하기
	int tempPrice;
	tempPrice = _settingPrice - _rightPrice;

	// tempPrice의 크기에 따른 처리

	// 엄청 저렴
	if (tempPrice < -100)
	{
		_npcEmotionState = NPC_TOO_CHEAP;
		_emotionImg = ImageManager::GetInstance()->FindImage("TooCheap");
		_selectPrice = _settingPrice;
		_isBuy = true;
	}
	// 저렴
	else if (tempPrice >= -100 && tempPrice < -50)
	{
		_npcEmotionState = NPC_CHEAP;
		_emotionImg = ImageManager::GetInstance()->FindImage("Cheap");
		_selectPrice = _settingPrice;
		_isBuy = true;
	}
	// 비쌈
	else if (tempPrice >= -50 && tempPrice < 100)
	{
		_npcEmotionState = NPC_EXPENSIVE;
		_emotionImg = ImageManager::GetInstance()->FindImage("Expensive");
		_selectPrice = 0;
	}
	// 너무 비쌈
	else if (tempPrice > 100)
	{
		_npcEmotionState = NPC_TOO_EXPENSIVE;
		_emotionImg = ImageManager::GetInstance()->FindImage("TooExpensive");
		_selectPrice = 0;
	}
}


void shopNPC::wayPointSet()
{
	// 왼쪽 첫번째 아이템
	_itemWayPoint[0].x = 12;
	_itemWayPoint[0].y = 16;

	// 왼쪽 두번째 아이템
	_itemWayPoint[1].x = 12;
	_itemWayPoint[1].y = 20;

	// 오른쪽 첫번째아이템
	_itemWayPoint[2].x = 14;
	_itemWayPoint[2].y = 16;

	// 오른쪽 두번째 아이템
	_itemWayPoint[3].x = 14;
	_itemWayPoint[3].y = 20;

	// 계산대
	_counterPoint.x = 19;
	_counterPoint.y = 18;

	// 출입문
	_eixtPoint.x = 17;
	_eixtPoint.y = 23;

	_aroundPoint[0].x = 20;
	_aroundPoint[0].y = 21;

	_aroundPoint[1].x = 18;
	_aroundPoint[1].y = 21;
	
	_aroundPoint[2].x = 19;
	_aroundPoint[2].y = 22;
}

void shopNPC::directionCheck()
{
	int DegAngle = _angle * 180 / PI; // 라디안 디그리(각도)로 변환

	// 오른쪽 방향
	if ((DegAngle <= 45 && DegAngle >= 0) || (DegAngle <= 360 && DegAngle > 315))
	{
		_indexY = 2;
	}

	// 위쪽 방향
	else if ((DegAngle <= 135 && DegAngle > 45))
	{
		_indexY = 3;
	}

	// 왼쪽 방향
	else if ((DegAngle <= 225 && DegAngle > 135))
	{
		_indexY = 1;
	}

	// 아래쪽 방향 
	else if ((DegAngle <= 315 && DegAngle > 225))
	{
		_indexY = 0;
	}
}

void shopNPC::chooseItem()
{	
	// 중복 방지 (안 본 아이템이 나올때 까지 루프)
	while (true)
	{
		_rndChoiceItem = RND->getInt(4);

		if (!_checkItem[_rndChoiceItem] && !_isAnotherPerson[_rndChoiceItem])
			break;
	}

	// 확인한 아이템 숫자 늘려주기
	_checkItemCount++;

	switch (_rndChoiceItem)
	{
	case 0:
		_goToPoint = _itemWayPoint[0];
		_checkItem[0] = true;
		break;

	case 1:
		_goToPoint = _itemWayPoint[1];
		_checkItem[1] = true;
		break;

	case 2:
		_goToPoint = _itemWayPoint[2];
		_checkItem[2] = true;
		break;

	case 3:
		_goToPoint = _itemWayPoint[3];
		_checkItem[3] = true;
		break;
	}

	_aStar->changeWayPoint();
}

void shopNPC::choosePt()
{
	_rndChoicePt = RND->getInt(3);

	switch (_rndChoicePt)
	{
	case 0:
		_goToPoint = _aroundPoint[0];
		break;
		
	case 1:
		_goToPoint = _aroundPoint[1];
		break;

	case 2:
		_goToPoint = _aroundPoint[2];
		break;
	}
}
