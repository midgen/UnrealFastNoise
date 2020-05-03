#include "UnrealFastNoisePlugin/Public/UFN3SelectModule.h"

UUFN3SelectModule::UUFN3SelectModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule1(nullptr)
	, InputModule2(nullptr)
	, InputModule3(nullptr)
	, UpperThreshold(0.f)
	, LowerThreshold(0.f)
	, Falloff(0.f)
	, InterpType(ESelectInterpType::Linear)
	, NumSteps(0)
{
}

float UUFN3SelectModule::GetNoise3D(float InX, float InY, float InZ)
{
	if (!(InputModule1 && InputModule2 && InputModule3 && SelectModule))
	{
		return 0.0f;
	}

	float Control = (SelectModule->GetNoise3D(InX, InY, InZ));

	// If there's no interpolation, easy mode
	if (Control >= UpperThreshold)
	{
		return InputModule1->GetNoise3D(InX, InY, InZ);
	}
	else if (Control < UpperThreshold && Control >= LowerThreshold)
	{
		return InputModule2->GetNoise3D(InX, InY, InZ);
	}
	else
	{
		return InputModule3->GetNoise3D(InX, InY, InZ);
	}
}

float UUFN3SelectModule::GetNoise2D(float InX, float InY)
{
	if (!(InputModule1 && InputModule2 && InputModule3 && SelectModule))
	{
		return 0.0f;
	}

	float Control = (SelectModule->GetNoise2D(InX, InY));

	// If there's no interpolation, easy mode
	if (Control >= UpperThreshold)
	{
		return InputModule1->GetNoise2D(InX, InY);
	}
	else if (Control < UpperThreshold && Control >= LowerThreshold)
	{
		return InputModule2->GetNoise2D(InX, InY);
	}
	else
	{
		return InputModule3->GetNoise2D(InX, InY);
	}
}
