#pragma once
// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
#include "FastNoise/FastNoise.h"
#include "UFNBlueprintFunctionLibrary.generated.h"

UCLASS()
class UUFNBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, Category = "UnrealFastNoise")
	static UUFNNoiseGenerator* CreateNoiseGenerator(UObject* aOuter, ENoiseType aNoiseType, EFractalType aFractalType, int32 aSeed, int32 aOctaves, float aFrequency);

	UFUNCTION(BlueprintPure, Category = "UnrealFastNoise")
	static UUFNNoiseGenerator* CreateSelectModule(UObject* aOuter, UUFNNoiseGenerator* aInputModule1, UUFNNoiseGenerator* aInputModule2, UUFNNoiseGenerator* aSelectModule, float aFalloff);

	UFUNCTION(BlueprintPure, Category = "UnrealFastNoise")
	static UUFNNoiseGenerator* CreateBlendModule(UObject* aOuter, UUFNNoiseGenerator* aInputModule1, UUFNNoiseGenerator* aInputModule2, UUFNNoiseGenerator* aSelectModule);

	UFUNCTION(BlueprintPure, Category = "UnrealFastNoise")
	static UUFNNoiseGenerator* CreateScaleBiasModule(UObject* aOuter, UUFNNoiseGenerator* aInputModule, float aScale, float aBias);
};