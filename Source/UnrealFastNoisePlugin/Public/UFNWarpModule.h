#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNWarpModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNWarpModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNWarpModule(const FObjectInitializer& ObjectInitializer);


	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	UPROPERTY()
	UUFNNoiseGenerator* InputModule;

	UPROPERTY()
	UUFNNoiseGenerator* WarpModule;

	float Iteration1XOffset;
	float Iteration1YOffset;
	float Iteration1ZOffset;

	float Iteration2XOffset1;
	float Iteration2YOffset1;
	float Iteration2ZOffset1;
	float Iteration2XOffset2;
	float Iteration2YOffset2;
	float Iteration2ZOffset2;

	EWarpIterations WarpIterations;

	float UnitSize;

	float Multiplier;
};