# DayZ-External-Tool
Tool for creating external hacks for dayz sa 0.63 / 1.0


Example (very easy to use!)

u need bypass for cheating in the game

int main()
{
	EnfusionProcess::AutoGameSelection(Analysis::Deep); 

	while (true) 
	{
		printf("Server: %s \n", EnfusionEngine::GetNetworkClientServerName().c_str());
		printf("Players Online: %d \n", EnfusionEngine::GetCountOfPlayers());

		
		for (uint64_t Entity : EnfusionEngine::GetAllEntityes())
		{
			Vector3 worldPosition = EnfusionEngine::GetCoordinate(Entity);
			Vector3 screenPosition = EnfusionEngine::WorldToScreen(worldPosition);

			if (EnfusionEngine::GetType(Entity) == Types::dayzplayer)
			{
				printf("[Soldier]                     \n");
				printf("PlayerName: %s                \n", EnfusionEngine::GetPlayerName(Entity).c_str());
				printf("Type: %s                      \n", EnfusionEngine::GetTypeName(Entity).c_str());
				printf("Model: %s                     \n", EnfusionEngine::GetModelName(Entity).c_str());
				printf("Item in Hands: %s             \n", EnfusionEngine::GetItemInHands(Entity).c_str());
				printf("Distance: %.0fm               \n", EnfusionEngine::GetDistanceToMe(worldPosition));
				printf("Position: %.1f : %.1f : %.1f  \n", worldPosition.x, worldPosition.y, worldPosition.z);
				printf("SceenPosition: %.1f : %.1f    \n", screenPosition.x, screenPosition.y);
			}

			if (EnfusionEngine::GetType(Entity) == Types::Car)
			{
				//etc..
			}

			if (EnfusionEngine::GetType(Entity) == Types::Thing)
			{
				//etc..
			}
		}

		//Camera control

		if (GetAsyncKeyState(VK_UP) < 0) { 
			EnfusionEngine::MovCameraForward();
		}

		if (GetAsyncKeyState(VK_DOWN) < 0) { 
			EnfusionEngine::MovCameraBackward();
		}

		if (GetAsyncKeyState(VK_LEFT) < 0) { 
			EnfusionEngine::MovCameraLeft();
		}

		if (GetAsyncKeyState(VK_RIGHT) < 0) { 
			EnfusionEngine::MovCameraRight();
		}

		if (GetAsyncKeyState(VK_PRIOR) < 0) { 
			EnfusionEngine::MovCameraUp();
		}

		if (GetAsyncKeyState(VK_NEXT) < 0) { 
			EnfusionEngine::MovCameraDown();
		}
	}

	return 0;
}
