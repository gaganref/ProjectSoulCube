#include "Components/InventorySystemComponent.h"
#include "LevelItems/AScCollectableItem.h"
#include "Misc/AutomationTest.h"
#include "Misc/InteractionStructs.h"
#include "Player/PlayerCharacter.h"
#include "Tests/AutomationCommon.h"
#include "Tests/SoulCubeTestsCommon.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(InventoryTests, "ProjectSoulCube.ProjectSoulCube.Private.Tests.InventoryTests",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

// Define required test scope variables
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

		if(!IsValid(PlayerCharacter))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			PlayerCharacter = TestWorld->SpawnActor<APlayerCharacter>(FVector(0.0f, 0.0f, 650.0f), FRotator::ZeroRotator, SpawnParams);

			CollectableTestItem = TestWorld->SpawnActor<AAScCollectableItem>(FVector(50.0f, 50.0f, 650.0f), FRotator::ZeroRotator, SpawnParams);
			ItemInfo.ItemWeight = 2;
			CollectableTestItem->SetItemInfoData(&ItemInfo);
			
			if(PlayerCharacter)
			{
				if(PlayerCharacter->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
				{
					InventorySystemComponent = IInventoryInterface::Execute_GetInventorySystemComponent(PlayerCharacter);
				}
			}
		}
	});
	
	AfterEach([this]()
	{
		PlayerCharacter->Destroy();
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
			TestEqual("Initial Max Inventory is set from Player attribute", PlayerCharacter->GetMaxInventorySize(), InventorySystemComponent->GetMaxInventorySize() * 1.0f);
		});
	});
	
	// Describe("Inventory Simple Functionality Check", [this]()
	// {
	// 	It("Inventory Add Item Check", [this]()
	// 	{
	// 		InventorySystemComponent->AddItem(CollectableTestItem);
	// 		const int32 CurrentSize = InventorySystemComponent->GetInventorySize();
	// 		
	// 		int32 ItemSize = 0;
	// 		if(CollectableTestItem)
	// 		{
	// 			if(CollectableTestItem->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	// 			{
	// 				ItemSize = IInteractableInterface::Execute_GetItemWeight(CollectableTestItem);
	// 			}
	// 		}
	// 		
	// 		TestEqual("Inventory Size should increase", InventorySystemComponent->GetInventorySize(), CurrentSize + ItemSize);
	// 	});
	//
	// 	It("Inventory Remove Item Check", [this]()
	// 	{
	// 		InventorySystemComponent->AddItem(CollectableTestItem);
	// 		const int32 CurrentSize = InventorySystemComponent->GetInventorySize();
	//
	// 		int32 ItemSize = 0;
	// 		if(CollectableTestItem)
	// 		{
	// 			if(CollectableTestItem->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	// 			{
	// 				ItemSize = IInteractableInterface::Execute_GetItemWeight(CollectableTestItem);
	// 			}
	// 		}
	// 		
	// 		InventorySystemComponent->RemoveItem(CollectableTestItem);
	// 		
	// 		TestEqual("Inventory Size should decrease", InventorySystemComponent->GetInventorySize(), CurrentSize - ItemSize);
	// 	});
	// });
}

#endif