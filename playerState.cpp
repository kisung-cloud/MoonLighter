#include "stdafx.h"
#include "playerState.h"
#include "player.h"

HRESULT playerIdleState::init()
{
	_transForm = false;

	return S_OK;
}

//Idle 鼻鷓
void playerIdleState::update(player & player)
{
	cout << _transForm << endl;
	if (!_transForm)
	{
		//務晦
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
		//嬪
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(false);
		}

		//嬴楚 
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(true);
		}

		//豭薹 
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(false);
		}

		//螃艇薹 
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	}
	
	//Ы溯檜橫 掘腦晦
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天


	//Ы溯檜橫 餌蜂 <-- 歜衛
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDie"), ImageManager::GetInstance()->FindImage("playerDie"));
		player.setCurrentState(player.getDieState());
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//Ы溯檜橫 蔓萄
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			player.setCurrentState(player.getShieldState());
		}
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//Ы溯檜橫 熱艙 <-- 歜衛
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_transForm = true;
	}

	if (_transForm)
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(true);
		}

		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionX(false);
		}

		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionX(true);
		}
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

	//��


	//匐
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSword1"), ImageManager::GetInstance()->FindImage("playerUpSword1"));
		player.setCurrentState(player.getSwordState());
		player.setDirectionY(false);
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSword1"), ImageManager::GetInstance()->FindImage("playerDownSword1"));
	}
	//天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天天

}

//walk 鼻鷓
void playerWalkState::update(player & player)
{
	//嬪
	if (!player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//虜擒 嬴楚酈 援腦賊 嬪薹Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			}
			//嬪薹Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setY(player.getY() - 0);
				return;
			}
			//嬴楚酈蒂 飲賊 嬪煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//虜擒 檜翕醞 豭薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setDirectionX(false);
			}
			//虜擒 檜翕醞 螃艇薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setDirectionX(true);
			}
			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			}
			player.setY(player.getY() - 5);
		}
	}

	//嬪薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//嬴鼠酈紫 援艇鼻鷓陛 嬴棲賊 Idle 鼻鷓煎 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(true);
		}
	}

	//嬴楚
	if (player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//虜擒 嬪薹酈 援腦賊 嬴楚 Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			}
			//嬴楚Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setY(player.getY() + 0);
				return;
			}
			//嬪薹酈蒂 飲賊 嬴楚煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//虜擒 檜翕醞 豭薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setDirectionX(false);
			}
			//虜擒 檜翕醞 螃艇薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setDirectionX(true);
			}

			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			}
			player.setY(player.getY() + 5);
		}
	}

	//嬴楚酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//嬴鼠酈紫 援艇鼻鷓陛 嬴棲賊 Idle 鼻鷓煎 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionY(true);
		}
	}

	//豭薹
	if (!player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//虜擒 螃艇薹酈 援腦賊 豭薹 Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			}
			//豭薹Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setX(player.getX() - 0);
				return;
			}
			//螃艇薹酈蒂 飲賊 豭薹戲煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//虜擒 檜翕醞 嬪薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setDirectionY(false);
			}
			//虜擒 檜翕醞 嬴楚薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setDirectionY(true);
			}
			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			}
			player.setX(player.getX() - 5);
		}
	}

	//豭薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//嬴鼠酈紫 援艇鼻鷓陛 嬴棲賊 Idle 鼻鷓煎 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
	}

	//螃艇薹
	if (player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//虜擒 豭薹酈 援腦賊 螃艇薹 Idle 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			}
			//螃艇薹Idle 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setX(player.getX() + 0);
				return;
			}
			//豭薹酈蒂 飲賊 螃艇薹戲煎 棻衛 遺霜歜
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
				player.setCurrentState(player.getWalkState());
			}
			//虜擒 檜翕醞 嬪薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setDirectionY(false);
			}
			//虜擒 檜翕醞 嬴楚薹酈 援腦賊
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setDirectionY(true);
			}
			//虜擒 檜翕醞 掘腦晦 援腦賊
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			}
			player.setX(player.getX() + 5);
		}
	}

	//螃艇薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//嬴鼠酈紫 援艇鼻鷓陛 嬴棲賊 Idle 鼻鷓煎 
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
			player.setCurrentState(player.getIdleState());
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(false);
		}
	}

	//Ы溯檜橫 掘腦晦
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"), ImageManager::GetInstance()->FindImage("playerRightRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"), ImageManager::GetInstance()->FindImage("playerLeftRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"), ImageManager::GetInstance()->FindImage("playerDownRoll"));
			player.setCurrentState(player.getRollState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"), ImageManager::GetInstance()->FindImage("playerUpRoll"));
			player.setCurrentState(player.getRollState());
		}
	}

	//Ы溯檜橫 蔓萄
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
			player.setCurrentState(player.getShieldState());
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
			player.setCurrentState(player.getShieldState());
		}
	}
}

//roll(掘腦晦) 鼻鷓
void playerRollState::update(player & player)
{
	//嬪煎 掘腦晦 
	if(player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpRoll"))
	{
		player.setY(player.getY() - 10);
	}
	//嬴楚煎 掘腦晦
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownRoll"))
	{
		player.setY(player.getY() + 10);
	}
	//豭薹戲煎 掘腦晦
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftRoll"))
	{
		player.setX(player.getX() - 10);
	}
	//螃艇薹戲煎 掘腦晦
	if (player.getPlayerMotion() == KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightRoll"))
	{
		player.setX(player.getX() + 10);
	}

	//酈 飲賊
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		//嬴鼠酈紫 援腦雖 彊堅氈戲賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			if (!player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (!player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}

			if (player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
			}
		}
	}
}

//die 鼻鷓
void playerDieState::update(player & player)
{

}

//shield 鼻鷓
void playerShieldState::update(player & player)
{
	//Ы溯檜橫 蔓萄
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		if (player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightShield"), ImageManager::GetInstance()->FindImage("playerRightShield"));
		}
		if (!player.getDirectionX())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftShield"), ImageManager::GetInstance()->FindImage("playerLeftShield"));
		}
		if (player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownShield"), ImageManager::GetInstance()->FindImage("playerDownShield"));
		}
		if (!player.getDirectionY())
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpShield"), ImageManager::GetInstance()->FindImage("playerUpShield"));
		}
	}

	//蔓萄酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			if (player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdle"), ImageManager::GetInstance()->FindImage("playerRightIdle"));
				player.setCurrentState(player.getIdleState());
			} 
			if (!player.getDirectionX())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdle"), ImageManager::GetInstance()->FindImage("playerLeftIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdle"), ImageManager::GetInstance()->FindImage("playerDownIdle"));
				player.setCurrentState(player.getIdleState());
			}
			if (!player.getDirectionY())
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdle"), ImageManager::GetInstance()->FindImage("playerUpIdle"));
				player.setCurrentState(player.getIdleState());
			}
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightWalk"), ImageManager::GetInstance()->FindImage("playerRightWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//豭薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftWalk"), ImageManager::GetInstance()->FindImage("playerLeftWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpWalk"), ImageManager::GetInstance()->FindImage("playerUpWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕ж啪
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownWalk"), ImageManager::GetInstance()->FindImage("playerDownWalk"));
			player.setCurrentState(player.getWalkState());
			player.setDirectionX(true);
		}
	}	
}

//idleSwim 鼻鷓
void playerIdleSwimState::update(player & player)
{
	//嬪
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirectionY(false);
	}

	//嬴楚
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirectionY(true);
	}

	//豭薹
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirectionX(false);
	}

	//螃艇薹
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
		player.setCurrentState(player.getSwimState());
		player.setDirectionX(true);
	}
}


//swim 鼻鷓
void playerSwimState::update(player & player)
{
	//嬪 
	if (!player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			//虜擒 嬴楚薹酈 援腦賊 嬪薹 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			}
			//嬪薹 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				player.setY(player.getY() - 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('S'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setY(player.getY() - 3);
		}
	}

	//嬪薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpIdleSwim"), ImageManager::GetInstance()->FindImage("playerUpIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//嬴楚酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(true);
		}
	}

	//嬴楚
	if (player.getDirectionY())
	{
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			//虜擒 嬪薹酈 援腦賊 嬴楚 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			}
			//嬴楚 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('W'))
			{
				player.setY(player.getY() + 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('W'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownSwim"), ImageManager::GetInstance()->FindImage("playerDownSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setY(player.getY() + 3);
		}
	}

	//嬴楚薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerDownIdleSwim"), ImageManager::GetInstance()->FindImage("playerDownIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerUpSwim"), ImageManager::GetInstance()->FindImage("playerUpSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}

	//豭薹
	if (!player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			//虜擒 螃艇薹酈 援腦賊 豭薹 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			}
			//豭薹 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				player.setX(player.getX() - 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('D'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftSwim"), ImageManager::GetInstance()->FindImage("playerLeftSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setX(player.getX() - 3);
		}
	}

	//豭薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerLeftIdleSwim"), ImageManager::GetInstance()->FindImage("playerLeftIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//螃艇薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}

	//螃艇薹
	if (player.getDirectionX())
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			//虜擒 豭薹酈 援腦賊 螃艇薹 idleSwim 賅蝗戲煎 滲л
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			}
			//螃艇薹 idleSwim 賅蝗戲煎 誇蹺晦
			else if (KEYMANAGER->isStayKeyDown('A'))
			{
				player.setX(player.getX() + 0);
				return;
			}
			//酈 飲賊 棻衛 檜翕
			else if (KEYMANAGER->isOnceKeyUp('A'))
			{
				player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
				player.setCurrentState(player.getSwimState());
			}
			player.setX(player.getX() + 3);
		}
	}

	//螃艇薹酈 飲賊
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		//嬴鼠酈紫 寰援腦賊 Idle 鼻鷓煎 瞪��
		if (KEYMANAGER->getKeyUp() == NULL)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightIdleSwim"), ImageManager::GetInstance()->FindImage("playerRightIdleSwim"));
			player.setCurrentState(player.getIdleSwimState());
		}
		//嬪薹酈蒂 援腦賊 棻衛 檜翕
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			player.setPlayerMotion(KEYANIMANAGER->findAnimation(player.getIndex(), "playerRightSwim"), ImageManager::GetInstance()->FindImage("playerRightSwim"));
			player.setCurrentState(player.getSwimState());
			player.setDirectionY(false);
		}
	}
}

//bow 鼻鷓
void playerbowState::update(player & player)
{

}

//sword 鼻鷓
void playerSwordState::update(player & player)
{

}
