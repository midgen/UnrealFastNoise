#include "UnrealFastNoisePlugin/Public/UFNSelectModule.h"

UUFNSelectModule::UUFNSelectModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule1(nullptr)
	, InputModule2(nullptr)
	, SelectModule(nullptr)
	, Threshold(0.f)
	, Falloff(0.f)
	, InterpType(ESelectInterpType::None)
	, NumSteps(0)
{
}

float UUFNSelectModule::GetNoise3D(float InX, float InY, float InZ)
{
	if (!(InputModule1 && InputModule2 && SelectModule))
	{
		return 0.0f;
	}

	float Control = (SelectModule->GetNoise3D(InX, InY, InZ));

	if (InterpType != ESelectInterpType::None)
	{
		// outside lower falloff bound
		if (Control <= (Threshold - Falloff))
		{
			return InputModule2->GetNoise3D(InX, InY, InZ);
		}
		// outside upper falloff bound
		else if (Control >= (Threshold + Falloff))
		{
			return InputModule1->GetNoise3D(InX, InY, InZ);
		}
		// otherwise must be inside the threshold bounds, so smooth it
		else
		{

			switch (InterpType)
			{
			case ESelectInterpType::CircularIn:
				return FMath::InterpCircularIn(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::CircularInOut:
				return FMath::InterpCircularInOut(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::CircularOut:
				return FMath::InterpCircularOut(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::ExponentialIn:
				return FMath::InterpExpoIn(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::ExponentialInOut:
				return FMath::InterpExpoInOut(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::ExponentialOut:
				return FMath::InterpExpoOut(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::SineIn:
				return FMath::InterpSinIn(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::SineInOut:
				return FMath::InterpSinInOut(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::SineOut:
				return FMath::InterpSinOut(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::Step:
				return FMath::InterpStep(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)), NumSteps);
			case ESelectInterpType::Linear:
				return FMath::Lerp(InputModule2->GetNoise3D(InX, InY, InZ), InputModule1->GetNoise3D(InX, InY, InZ), (Control - (Threshold - Falloff) / (2.0f * Falloff)));
			}
		}
	}

	// If there's no interpolation, easy mode
	if (Control > Threshold)
	{
		return InputModule1->GetNoise3D(InX, InY, InZ);
	}
	else
	{
		return InputModule2->GetNoise3D(InX, InY, InZ);
	}
}

float UUFNSelectModule::GetNoise2D(float InX, float InY)
{
	if (!(InputModule1 && InputModule2 && SelectModule))
	{
		return 0.0f;
	}

	float control = (SelectModule->GetNoise2D(InX, InY));

	if (InterpType != ESelectInterpType::None)
	{
		// outside lower falloff bound
		if (control <= (Threshold - Falloff))
		{
			return InputModule2->GetNoise2D(InX, InY);
		}
		// outside upper falloff bound
		else if (control >= (Threshold + Falloff))
		{
			return InputModule1->GetNoise2D(InX, InY);
		}
		// otherwise must be inside the threshold bounds, so smooth it
		else
		{
			switch (InterpType)
			{
			case ESelectInterpType::CircularIn:
				return FMath::InterpCircularIn(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::CircularInOut:
				return FMath::InterpCircularInOut(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::CircularOut:
				return FMath::InterpCircularOut(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::ExponentialIn:
				return FMath::InterpExpoIn(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::ExponentialInOut:
				return FMath::InterpExpoInOut(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::ExponentialOut:
				return FMath::InterpExpoOut(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::SineIn:
				return FMath::InterpSinIn(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::SineInOut:
				return FMath::InterpSinInOut(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::SineOut:
				return FMath::InterpSinInOut(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			case ESelectInterpType::Step:
				return FMath::InterpStep(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)), NumSteps);
			case ESelectInterpType::Linear:
				return FMath::Lerp(InputModule2->GetNoise2D(InX, InY), InputModule1->GetNoise2D(InX, InY), (control - (Threshold - Falloff) / (2.0f * Falloff)));
			}
		}
	}

	if (control > Threshold)
	{
		return InputModule1->GetNoise2D(InX, InY);
	}
	else
	{
		return InputModule2->GetNoise2D(InX, InY);
	}
}
