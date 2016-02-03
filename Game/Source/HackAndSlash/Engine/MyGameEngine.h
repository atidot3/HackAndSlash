// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameEngine.h"
#include "MyGameEngine.generated.h"


UCLASS()
class UMyGameEngine : public UGameEngine
{
	GENERATED_UCLASS_BODY()
public:
	// When engine starts
	void Init(class IEngineLoop* InEngineLoop);
	// Close engine
	void PreExit();
};
