// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Appfox_Test_Task : ModuleRules
{
	public Appfox_Test_Task(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
