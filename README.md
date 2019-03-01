# DayZ-External-Tool

Tool for create external hacks for dayz sa 1.0
u need to make or buy bypass for cheating in the game!!!!
Example (very easy to use!)

	EnfusionProcess::AutoGameSelection(Analysis::Deep); //GetPHandle
	
	for (uint64_t Entity : EnfusionEngine::GetAllEntityes()) // all players
		{
			Vector3 worldPosition = EnfusionEngine::GetCoordinate(Entity);
			Vector3 screenPosition = EnfusionEngine::WorldToScreen(worldPosition);

			printf("PlayerName: %s                \n", EnfusionEngine::GetPlayerName(Entity).c_str());
			printf("Type: %s                      \n", EnfusionEngine::GetTypeName(Entity).c_str());
			printf("Model: %s                     \n", EnfusionEngine::GetModelName(Entity).c_str());
			printf("Item in Hands: %s             \n", EnfusionEngine::GetItemInHands(Entity).c_str());
			printf("Distance: %.0fm               \n", EnfusionEngine::GetDistanceToMe(worldPosition));
			printf("Position: %.1f : %.1f : %.1f  \n", worldPosition.x, worldPosition.y, worldPosition.z);
			printf("SceenPosition: %.1f : %.1f    \n", screenPosition.x, screenPosition.y);		
		}


