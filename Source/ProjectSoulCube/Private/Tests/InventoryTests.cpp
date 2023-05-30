#include "Components/InventorySystemComponent.h"
#include "LevelItems/AScCollectableItem.h"
#include "Misc/AutomationTest.h"
#include "Misc/InteractionStructs.h"
#include "Player/PlayerCharacter.h"
#include "Tests/AutomationCommon.h"
#include "Tests/SoulCubeTestsCommon.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(InventoryTests, "ProjectSoulCube.ProjectSoulCube.Private.Tests.InventoryTests",
								 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

// Define required test scope variables
TSubclassOf<APlayerCharacter> PlayerCharacterClass;
UClass* TestItemClass;
APlayerCharacter* PlayerCharacter;
AAScCollectableItem* CollectableTestItem;
UInventorySystemComponent* InventorySystemComponent;
UWorld* TestWorld;

FInventoryItemInfo ItemInfo;

END_DEFINE_SPEC(InventoryTests)

void InventoryTests::Define()
{
	BeforeEach([this]()
	{
		AutomationOpenMap(TEXT("/Game/Maps/GameMap"));
		TestWorld = GetTestWorld();

		PlayerCharacterClass = StaticLoadClass(APlayerCharacter::StaticClass(), nullptr, TEXT("/Game/Blueprints/Player/BP_SC_Player.BP_SC_Player_C"));
		if(PlayerCharacterClass)
		{
			if(TestWorld)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				PlayerCharacter = TestWorld->SpawnActor<APlayerCharacter>(PlayerCharacterClass, FVector(0.0f, 0.0f, 650.0f), FRotator::ZeroRotator, SpawnParams);
			}
			if(PlayerCharacter)
			{
				if(PlayerCharacter->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
				{
					InventorySystemComponent = IInventoryInterface::Execute_GetInventorySystemComponent(PlayerCharacter);
				}	
			}
		}
		
		TestItemClass = StaticLoadClass(AAScCollectableItem::StaticClass(), nullptr, TEXT("/Game/Blueprints/LevelGenerator/Collectables/BP_Item_HealthBuff.BP_Item_HealthBuff_C"));
		if(TestItemClass)
		{
			if(TestWorld)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				CollectableTestItem = TestWorld->SpawnActor<AAScCollectableItem>(TestItemClass,FVector(50.0f, 50.0f, 650.0f), FRotator::ZeroRotator, SpawnParams);
			}
		}
	});
	
	AfterEach([this]()
	{
		PlayerCharacter->Destroy();
		CollectableTestItem->Destroy();
	});

	Describe("Inventory Spawn Check", [this]()
	{
		It("Verify if the Inventory is attached to the player is spawned in the world", [this]()
		{
			TestNotNull("Inventory should be valid", InventorySystemComponent);
		});
		
		It("Verify if a collectable item is spawned is spawned in the world", [this]()
		{
			TestNotNull("Collectable Item should be valid", CollectableTestItem);
		});
	});

	Describe("Inventory Check", [this]()
	{
		It("Verify Initial Inventory Data", [this]()
		{
			TestEqual("Initial Inventory should be zero",  InventorySystemComponent->GetInventorySize(), 0);
			if(PlayerCharacter)
			{
				if(IPlayerStatsInterface* StatsInterface = Cast<IPlayerStatsInterface>(PlayerCharacter))
				{
					TestEqual("Initial Max Inventory is set from Player attribute", StatsInterface->GetMaxInventorySize(), InventorySystemComponent->GetMaxInventorySize() * 1.0f);
				}
			}
		});
	});
}

#endif