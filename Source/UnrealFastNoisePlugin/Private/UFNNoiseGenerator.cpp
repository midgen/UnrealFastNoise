#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"


UUFNNoiseGenerator::UUFNNoiseGenerator(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

float UUFNNoiseGenerator::GetNoise2D(float InX, float InY)
{
	return -2.0f;
}

float UUFNNoiseGenerator::GetNoise3D(float InX, float InY, float InZ)
{
	return -2.0f;
}