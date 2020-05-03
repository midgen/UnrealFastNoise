#include "UnrealFastNoisePlugin/Public/UFNAddModule.h"

UUFNAddModule::UUFNAddModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule1(nullptr)
	, InputModule2(nullptr)
	, MaskModule(nullptr)
	, Threshold(0.f)
{
}

float UUFNAddModule::GetNoise3D(float InX, float InY, float InZ)
{

	if (!(InputModule1 || InputModule2))
	{
		return 0.0f;
	}

	float Modifier = 1.0f;
	if (MaskModule)
	{
		float Mask = MaskModule->GetNoise3D(InX, InY, InZ);
		if (Mask >= Threshold)
		{
			Modifier = Mask;
		}
		else
		{
			return InputModule1->GetNoise3D(InX, InY, InZ);
		}
	}

	return Modifier * (InputModule1->GetNoise3D(InX, InY, InZ) + InputModule2->GetNoise3D(InX, InY, InZ));
}

float UUFNAddModule::GetNoise2D(float InX, float InY)
{
	return GetNoise3D(InX, InY, 0.0f);
}
