#include "UnrealFastNoisePlugin/Public/UFNRadialModule.h"

#include "UnrealFastNoisePlugin/Public/UnrealFastNoisePlugin.h"

UUFNRadialModule::UUFNRadialModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule1(nullptr)
	, InputModule2(nullptr)
	, Origin(FVector::ZeroVector)
	, Radius2(0.f)
	, Falloff2(0.f)
	, InterpType(ESelectInterpType::None)
	, NumSteps(0)
{
}

float UUFNRadialModule::GetNoise3D(float InX, float InY, float InZ)
{
	if (!(InputModule1 && InputModule2))
	{
		return 0.0f;
	}

	float dist2 = (Origin - FVector(InX, InY, InZ)).SizeSquared();

	if (InterpType != ESelectInterpType::None)
	{
		// outside falloff
		if (dist2 > Radius2 + Falloff2)
		{
			return InputModule2->GetNoise3D(InX, InY, InZ);
		}
		// inside radius
		else if (dist2 < Radius2)
		{
			return InputModule1->GetNoise3D(InX, InY, InZ);
		}
		// otherwise in the falloff range, so smooth
		else
		{

			switch (InterpType)
			{
			case ESelectInterpType::CircularIn:
				return FMath::InterpCircularIn(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::CircularInOut:
				return FMath::InterpCircularInOut(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::CircularOut:
				return FMath::InterpCircularOut(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::ExponentialIn:
				return FMath::InterpExpoIn(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::ExponentialInOut:
				return FMath::InterpExpoInOut(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::ExponentialOut:
				return FMath::InterpExpoOut(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::SineIn:
				return FMath::InterpSinIn(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::SineInOut:
				return FMath::InterpSinInOut(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::SineOut:
				return FMath::InterpSinInOut(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::Step:
				return FMath::InterpStep(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2, NumSteps);
			case ESelectInterpType::Linear:
				return FMath::Lerp(InputModule1->GetNoise3D(InX, InY, InZ), InputModule2->GetNoise3D(InX, InY, InZ), (dist2 - Radius2) / Falloff2);
			}
		}
	}

	// If there's no interpolation, easy mode
	if (dist2 > Radius2)
	{
		return InputModule1->GetNoise3D(InX, InY, InZ);
	}
	else
	{
		return InputModule2->GetNoise3D(InX, InY, InZ);
	}
}

float UUFNRadialModule::GetNoise2D(float InX, float InY)
{
	if (!(InputModule1 && InputModule2))
	{
		return 0.0f;
	}

	float dist2 = (FVector2D(InX, InY) - FVector2D(Origin.X, Origin.Y)).SizeSquared();

	if (InterpType != ESelectInterpType::None)
	{
		// outside falloff
		if (dist2 > Radius2 + Falloff2)
		{
			return InputModule2->GetNoise2D(InX, InY);
		}
		// inside radius
		else if (dist2 < Radius2)
		{
			return InputModule1->GetNoise2D(InX, InY);
		}
		// otherwise in the falloff range, so smooth
		else
		{

			switch (InterpType)
			{
			case ESelectInterpType::CircularIn:
				return FMath::InterpCircularIn(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::CircularInOut:
				return FMath::InterpCircularInOut(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::CircularOut:
				return FMath::InterpCircularOut(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::ExponentialIn:
				return FMath::InterpExpoIn(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::ExponentialInOut:
				return FMath::InterpExpoInOut(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::ExponentialOut:
				return FMath::InterpExpoOut(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::SineIn:
				return FMath::InterpSinIn(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::SineInOut:
				return FMath::InterpSinInOut(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::SineOut:
				return FMath::InterpSinInOut(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			case ESelectInterpType::Step:
				return FMath::InterpStep(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2, NumSteps);
			case ESelectInterpType::Linear:
				return FMath::Lerp(InputModule1->GetNoise2D(InX, InY), InputModule2->GetNoise2D(InX, InY), (dist2 - Radius2) / Falloff2);
			}
		}
	}

	// If there's no interpolation, easy mode
	if (dist2 > Radius2)
	{
		return InputModule1->GetNoise2D(InX, InY);
	}
	else
	{
		return InputModule2->GetNoise2D(InX, InY);
	}
}
