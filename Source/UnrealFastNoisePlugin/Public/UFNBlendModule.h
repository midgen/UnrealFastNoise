#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNBlendModule.generated.h"

class UCurveFloat;

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNBlendModule : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNBlendModule(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;
	UPROPERTY()
	UUFNNoiseGenerator* InputModule1;
	UPROPERTY()
	UUFNNoiseGenerator* InputModule2;
	UPROPERTY()
	UUFNNoiseGenerator* SelectModule;
	UPROPERTY()
	UCurveFloat* BlendCurve;

	float Falloff;
};