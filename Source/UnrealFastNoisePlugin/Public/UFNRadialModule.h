#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNRadialModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNRadialModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNRadialModule(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	UPROPERTY()
	UUFNNoiseGenerator* InputModule1;

	UPROPERTY()
	UUFNNoiseGenerator* InputModule2;

	FVector Origin;
	float Radius2;
	float Falloff2;

	ESelectInterpType InterpType;
	int32 NumSteps;
};