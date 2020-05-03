#include "UnrealFastNoisePlugin/Public/UFNScaleBiasModule.h"

UUFNScaleBiasModule::UUFNScaleBiasModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule(nullptr)
	, Scale(1.0f)
	, Bias(0.f)
{
}

float UUFNScaleBiasModule::GetNoise3D(float InX, float InY, float InZ)
{
	if (!(InputModule))
	{
		return 0.0f;
	}

	return (InputModule->GetNoise3D(InX, InY, InZ) * Scale) + Bias;
}

float UUFNScaleBiasModule::GetNoise2D(float InX, float InY)
{
	if (!(InputModule))
	{
		return 0.0f;
	}

	return (InputModule->GetNoise2D(InX, InY) * Scale) + Bias;
}
