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
			TestEqual("Initial Health is equal to MaxHealth", PlayerCharacter->GetHealth(), PlayerCharacter->GetMaxHealth());
		});
        
		It("Verify Initial Player Shield Attribute", [this]()
		{
			TestEqual("Initial Shield is equal to MaxShield", PlayerCharacter->GetShield(), PlayerCharacter->GetMaxShield());
		});

		It("Verify Initial Player Stamina Attribute", [this]()
		{
			TestEqual("Initial Stamina is equal to MaxStamina", PlayerCharacter->GetStamina(), PlayerCharacter->GetMaxStamina());
		});
	});
}

#endif