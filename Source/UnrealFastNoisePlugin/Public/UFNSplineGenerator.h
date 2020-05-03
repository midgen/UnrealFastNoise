#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"

#include "UFNSplineGenerator.generated.h"

UCLASS(BlueprintType)
class UNREALFASTNOISEPLUGIN_API UUFNSplineGenerator : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UUFNSplineGenerator(const FObjectInitializer& ObjectInitializer);

	float GetNoise3D(float InX, float InY, float InZ) override;
	float GetNoise2D(float InX, float InY) override;

	UFUNCTION(BlueprintCallable, Category = "FastNoise")
	void AddSpline(USplineComponent* Spline);

	UPROPERTY()
	TArray<class USplineComponent*> Splines;

	/*
	The generator will return values of 1.0 for all points greater than MaximumDistance
	from the splines
	*/
	float MaximumDistance;

	/*
	  The generator will return values of 0.0 for all points less than MinimumDistance
	  from the splines
	*/
	float MinimumDistance;

	/*
	  Values between Minimum and Maximum Distance will be run through this curve function,
	  if provided.
	*/
	UCurveFloat* FalloffCurve;
};
