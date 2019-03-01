# DayZ-External-Tool

Tool for create external hacks for dayz sa 1.0
u need to make or buy bypass for cheating in the game!!!!
Example (very easy to use!)

	//GetPHandle
        EnfusionProcess::AutoGameSelection(Analysis::Deep);
 
        //get all players around u
	for (uint64_t Entity : EnfusionEngine::GetAllEntityes()) // all players
	{
		Vector3 worldPosition = EnfusionEngine::GetCoordinate(Entity);
		Vector3 screenPosition = EnfusionEngine::WorldToScreen(worldPosition);
 
		printf("PlayerName: %s                \n", EnfusionEngine::GetPlayerName(Entity).c_str());
		printf("Type: %s                      \n", EnfusionEngine::GetTypeName(Entity).c_str());
		printf("Model: %s                     \n", EnfusionEngine::GetModelName(Entity).c_str());
		printf("Item in Hands: %s             \n", EnfusionEngine::GetItemInHands(Entity).c_str());
		printf("ViewDirection: %s               \n", EnfusionEngine::GetDirection().c_str());
		printf("Distance: %.0fm               \n", EnfusionEngine::GetDistanceToMe(worldPosition));
		printf("Position: %.1f : %.1f : %.1f  \n", worldPosition.x, worldPosition.y, worldPosition.z);
		printf("SceenPosition: %.1f : %.1f    \n", screenPosition.x, screenPosition.y);		
 
                        //Aimbot (teleport ur bullet in enemy head) 
                 float centerX = Render.Width / 2.0f;
			float centerY = Render.Height / 2.0f;
 
			if (GetAsyncKeyState(VK_LMENU)) // if key pressed
			{
                                float radius = 30.0f;
				if (screenPosition.x - centerX < radius && centerX - screenPosition.x < radius &&
					centerY - screenPosition.y < radius && screenPosition.y - centerY < radius)
				{
					EnfusionEngine::KillBySilentAim(Entity); // kill selected entity
				}
			}
	}
	
	//remove grass
	EnfusionEngine::SetTerrainGrid(0.0f); //remove it
	EnfusionEngine::SetTerrainGrid(10.0f); //change back
 
        //Add "freecam" functions
        find MovCam in sdk

