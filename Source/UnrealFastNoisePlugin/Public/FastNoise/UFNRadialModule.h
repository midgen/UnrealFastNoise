#pragma once

#include "UFNNoiseGenerator.h"
#include "CoreMinimal.h"
#include "UFNRadialModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNRadialModule : public UUFNNoiseGenerator
{
	GENERATED_UCLASS_BODY()
public:

	float GetNoise3D(float aX, float aY, float aZ) override;
	float GetNoise2D(float aX, float aY) override;

	UPROPERTY()
	UUFNNoiseGenerator* inputModule1;

	UPROPERTY()
	UUFNNoiseGenerator* inputModule2;

	FVector origin;
	float radius;
	float falloff;

	ESelectInterpType interpType;
	int32 numSteps;
};