#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNSelectModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNSelectModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNSelectModule(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	UPROPERTY()
	UUFNNoiseGenerator* InputModule1;
	UPROPERTY()
	UUFNNoiseGenerator* InputModule2;
	UPROPERTY()
	UUFNNoiseGenerator* SelectModule;

	float Threshold;
	float Falloff;
	ESelectInterpType InterpType;
	int32 NumSteps;
};