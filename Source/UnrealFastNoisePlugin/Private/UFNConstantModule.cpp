#include "UnrealFastNoisePlugin/Public/UFNConstantModule.h"

UUFNConstantModule::UUFNConstantModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ConstantValue(0.f)
{
}

float UUFNConstantModule::GetNoise3D(float InX, float InY, float InZ)
{
	return ConstantValue;
}

float UUFNConstantModule::GetNoise2D(float InX, float InY)
{
	return ConstantValue;
}
