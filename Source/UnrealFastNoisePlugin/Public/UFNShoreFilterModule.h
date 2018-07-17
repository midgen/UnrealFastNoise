#pragma once

#include "UFNNoiseGenerator.h"
#include "CoreMinimal.h"
#include "UFNShoreFilterModule.generated.h"

UCLASS()
class UNREALFASTNOISEPLUGIN_API UUFNShoreFilterModule : public UUFNNoiseGenerator
{
	GENERATED_UCLASS_BODY()
public:

	float GetNoise3D(float aX, float aY, float aZ) override;
	float GetNoise2D(float aX, float aY) override;

	UPROPERTY()
		UUFNNoiseGenerator* myInputModule;

	float myShoreHeight;
	float myThreshhold;

};