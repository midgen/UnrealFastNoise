#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNShoreFilterModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNShoreFilterModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNShoreFilterModule(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	UPROPERTY()
	UUFNNoiseGenerator* InputModule;

	float ShoreHeight;
	float Threshhold;
};