#include "UFNRadialModule.h"
#include "UnrealFastNoisePlugin.h"
#include "UFNNoiseGenerator.h"


UUFNRadialModule::UUFNRadialModule(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

float UUFNRadialModule::GetNoise3D(float aX, float aY, float aZ)
{
	if (!(inputModule1 && inputModule2)) {
		return 0.0f;
	}

	float dist = (origin - FVector(aX, aY, aZ)).Size();

	if (interpType != ESelectInterpType::None)
	{
		// outside falloff
		if (dist >  radius + falloff) {
			return inputModule2->GetNoise3D(aX, aY, aZ);
		}
		// inside radius
		else if (dist < radius) {
			return inputModule1->GetNoise3D(aX, aY, aZ);
		}
		// otherwise in the falloff range, so smooth
		else {

			switch (interpType)
			{
			case ESelectInterpType::CircularIn:
				return FMath::InterpCircularIn(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::CircularInOut:
				return FMath::InterpCircularInOut(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::CircularOut:
				return FMath::InterpCircularOut(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::ExponentialIn:
				return FMath::InterpExpoIn(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::ExponentialInOut:
				return FMath::InterpExpoInOut(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::ExponentialOut:
				return FMath::InterpExpoOut(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::SineIn:
				return FMath::InterpSinIn(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::SineInOut:
				return FMath::InterpSinInOut(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::SineOut:
				return FMath::InterpSinInOut(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			case ESelectInterpType::Step:
				return FMath::InterpStep(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff, numSteps);
			case ESelectInterpType::Linear:
				return FMath::Lerp(inputModule1->GetNoise3D(aX, aY, aZ), inputModule2->GetNoise3D(aX, aY, aZ), (dist - radius) / falloff);
			}
		}
	}

	// If there's no interpolation, easy mode
	if (dist > radius) {
		return inputModule1->GetNoise3D(aX, aY, aZ);
	}
	else {
		return inputModule2->GetNoise3D(aX, aY, aZ);
	}


}

float UUFNRadialModule::GetNoise2D(float aX, float aY)
{
	if (!(inputModule1 && inputModule2)) {
		return 0.0f;
	}

	float dist = (FVector2D(aX, aY) - FVector2D(origin.X, origin.Y)).Size();

	if (interpType != ESelectInterpType::None)
	{
		// outside falloff
		if (dist > radius + falloff) {
			return inputModule2->GetNoise2D(aX, aY);
		}
		// inside radius
		else if (dist < radius) {
			return inputModule1->GetNoise2D(aX, aY);
		}
		// otherwise in the falloff range, so smooth
		else {

			switch (interpType)
			{
			case ESelectInterpType::CircularIn:
				return FMath::InterpCircularIn(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::CircularInOut:
				return FMath::InterpCircularInOut(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::CircularOut:
				return FMath::InterpCircularOut(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::ExponentialIn:
				return FMath::InterpExpoIn(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::ExponentialInOut:
				return FMath::InterpExpoInOut(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::ExponentialOut:
				return FMath::InterpExpoOut(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::SineIn:
				return FMath::InterpSinIn(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::SineInOut:
				return FMath::InterpSinInOut(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::SineOut:
				return FMath::InterpSinInOut(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			case ESelectInterpType::Step:
				return FMath::InterpStep(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff, numSteps);
			case ESelectInterpType::Linear:
				return FMath::Lerp(inputModule1->GetNoise2D(aX, aY), inputModule2->GetNoise2D(aX, aY), (dist - radius) / falloff);
			}
		}
	}

	// If there's no interpolation, easy mode
	if (dist > radius) {
		return inputModule1->GetNoise2D(aX, aY);
	}
	else {
		return inputModule2->GetNoise2D(aX, aY);
	}

}

