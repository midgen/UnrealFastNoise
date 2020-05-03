#include "UnrealFastNoisePlugin/Public/UFNShoreFilterModule.h"

UUFNShoreFilterModule::UUFNShoreFilterModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule(nullptr)
	, ShoreHeight(0.f)
	, Threshhold(0.f)
{
}

float UUFNShoreFilterModule::GetNoise3D(float InX, float InY, float InZ)
{
	// This is only useful for 2D noise
	return -1.0f;
}

float UUFNShoreFilterModule::GetNoise2D(float InX, float InY)
{
	if (!(InputModule))
	{
		return 0.0f;
	}

	float StartValue = InputModule->GetNoise2D(InX, InY);

	if (StartValue >= ShoreHeight + Threshhold || StartValue <= ShoreHeight - Threshhold)
	{
		return StartValue;
	}

	float Alpha = (StartValue + Threshhold) / (Threshhold * 2);

	return FMath::InterpSinInOut(StartValue, 0.0f, 1.0f - Alpha);
}
