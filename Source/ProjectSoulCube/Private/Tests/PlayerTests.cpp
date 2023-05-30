#include "Misc/AutomationTest.h"
#include "Player/PlayerCharacter.h"
#include "Tests/AutomationCommon.h"
#include "Tests/SoulCubeTestsCommon.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(PlayerTests, "ProjectSoulCube.ProjectSoulCube.Private.Tests.PlayerTests",
				EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

// Define required test scope variables
APlayerCharacter* PlayerCharacter;
UWorld* TestWorld;

END_DEFINE_SPEC(PlayerTests)

void PlayerTests::Define()
{
	BeforeEach([this]()
	{
		AutomationOpenMap(TEXT("/Game/Maps/GameMap"));
		TestWorld = GetTestWorld();

		if(!IsValid(PlayerCharacter))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			PlayerCharacter = TestWorld->SpawnActor<APlayerCharacter>(FVector(0.0f, 0.0f, 650.0f), FRotator::ZeroRotator, SpawnParams);
		}
	});
	
	AfterEach([this]()
	{
		PlayerCharacter->Destroy();
	});

	Describe("Player Spawn Check", [this]()
	{
		It("Verify if the player is spawned in the world", [this]()
		{
			TestNotNull("Spawned player should be valid", PlayerCharacter);
		});
	});
	
	Describe("Player Attributes Check", [this]()
	{
		It("Verify Initial Player Health Attribute", [this]()
		{
			if(PlayerCharacter)
			{
				if(IPlayerStatsInterface* StatsInterface = Cast<IPlayerStatsInterface>(PlayerCharacter))
				{
					TestEqual("Initial Health is equal to MaxHealth", StatsInterface->GetHealth(), StatsInterface->GetMaxHealth());
				}
			}
		});
        
		It("Verify Initial Player Shield Attribute", [this]()
		{
			if(PlayerCharacter)
			{
				if(IPlayerStatsInterface* StatsInterface = Cast<IPlayerStatsInterface>(PlayerCharacter))
				{
					
					TestEqual("Initial Shield is equal to MaxShield", StatsInterface->GetShield(), StatsInterface->GetMaxShield());
				}
			}
		});

		It("Verify Initial Player Stamina Attribute", [this]()
		{
			if(PlayerCharacter)
			{
				if(IPlayerStatsInterface* StatsInterface = Cast<IPlayerStatsInterface>(PlayerCharacter))
				{
					TestEqual("Initial Stamina is equal to MaxStamina", StatsInterface->GetStamina(), StatsInterface->GetMaxStamina());
				}
			}
		});
	});
}

#endif