#include "UnrealFastNoisePlugin/Public/UFNBlendModule.h"

UUFNBlendModule::UUFNBlendModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule1(nullptr)
	, InputModule2(nullptr)
	, SelectModule(nullptr)
	, BlendCurve(nullptr)
	, Falloff(0.f)
{
}

float UUFNBlendModule::GetNoise3D(float InX, float InY, float InZ)
{

	if (!(InputModule1 && InputModule2 && SelectModule))
	{
		return 0.0f;
	}

	float Control = (SelectModule->GetNoise3D(InX, InY, InZ) + 1.0f) / 2.0f;

	if (BlendCurve)
	{
		Control = BlendCurve->GetFloatValue(Control);
	}

	return FMath::Lerp(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), Control);
}

float UUFNBlendModule::GetNoise2D(float InX, float InY)
{
	if (!(InputModule1 && InputModule2 && SelectModule))
	{
		return 0.0f;
	}

	float Control = (SelectModule->GetNoise2D(InX, InY) + 1.0f) / 2.0f;

	if (BlendCurve)
	{
		Control = BlendCurve->GetFloatValue(Control);
	}

	return FMath::Lerp(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), Control);
}
