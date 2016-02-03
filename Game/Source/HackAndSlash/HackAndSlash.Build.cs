// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HackAndSlash : ModuleRules
{
	public HackAndSlash(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", 
            "Networking", "Slate", "SlateCore", "OnlineSubsystem",
            "OnlineSubsystemNull", "HTTP", "OnlineSubsystemUtils", "Sockets",
            "AIModule", "GameplayTasks",});
        
        PrivateDependencyModuleNames.AddRange(
            new string[] {
				"HackAndSlashLoadingScreen"});
        
        PrivateDependencyModuleNames.AddRange(
            new string[] {
				"Slate",
				"SlateCore",});
	}
}
