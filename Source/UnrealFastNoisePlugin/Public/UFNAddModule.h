#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNAddModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNAddModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNAddModule(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;
	UPROPERTY()
	UUFNNoiseGenerator* InputModule1;
	UPROPERTY()
	UUFNNoiseGenerator* InputModule2;
	UPROPERTY()
	UUFNNoiseGenerator* MaskModule;

	float Threshold;
};