#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNScaleBiasModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNScaleBiasModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNScaleBiasModule(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	UPROPERTY()
	UUFNNoiseGenerator* InputModule;

	float Scale;
	float Bias;
};