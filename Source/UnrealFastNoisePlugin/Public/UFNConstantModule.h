#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNConstantModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNConstantModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNConstantModule(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	float ConstantValue;
};