#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

BEGIN_DEFINE_SPEC(LevelGeneratorTests, "ProjectSoulCube.ProjectSoulCube.Private.Tests.LevelGeneratorTests",
				EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


END_DEFINE_SPEC(LevelGeneratorTests)


void LevelGeneratorTests::Define()
{
	BeforeEach([this]()
	{
		
	});
	
	AfterEach([this]()
	{
		
	});

	Describe("Player Spawn Check", [this]()
	{
		It("Verify if the player is spawned in the world", [this]()
		{
			
		});
	});
	
}

#endif
