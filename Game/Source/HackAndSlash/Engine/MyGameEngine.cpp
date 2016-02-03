// Fill out your copyright notice in the Description page of Project Settings.

#include "HackAndSlash.h"
#include "MyGameEngine.h"

UMyGameEngine::UMyGameEngine(const FObjectInitializer& PIPE) : Super(PIPE)
{

}

void UMyGameEngine::Init(class IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);
}

void UMyGameEngine::PreExit()
{
	HackAndSlash::instance->Logout();
	Super::PreExit();
}