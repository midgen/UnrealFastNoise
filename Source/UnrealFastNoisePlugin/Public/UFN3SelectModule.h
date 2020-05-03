#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFN3SelectModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFN3SelectModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFN3SelectModule(const FObjectInitializer& InInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	UPROPERTY()
	UUFNNoiseGenerator* InputModule1;
	UPROPERTY()
	UUFNNoiseGenerator* InputModule2;
	UPROPERTY()
	UUFNNoiseGenerator* InputModule3;
	UPROPERTY()
	UUFNNoiseGenerator* SelectModule;

	float UpperThreshold;
	float LowerThreshold;

	float Falloff;
	ESelectInterpType InterpType;
	int32 NumSteps;
};