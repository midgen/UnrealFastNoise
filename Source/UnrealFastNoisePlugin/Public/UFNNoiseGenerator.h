#pragma once

#include <Runtime/CoreUObject/Public/UObject/Object.h>

#include "UFNNoiseGenerator.generated.h"

UCLASS(BlueprintType)
class UNREALFASTNOISEPLUGIN_API UUFNNoiseGenerator : public UObject
{
	GENERATED_BODY()
public:
	UUFNNoiseGenerator(const class FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "UnrealFastNoise")
	virtual float GetNoise2D(float InX, float InY);
	UFUNCTION(BlueprintCallable, Category = "UnrealFastNoise")
	virtual float GetNoise3D(float InX, float InY, float InZ);
};