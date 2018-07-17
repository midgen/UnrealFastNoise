#include "UFNShoreFilterModule.h"
#include "UnrealFastNoisePlugin.h"
#include "UFNNoiseGenerator.h"


UUFNShoreFilterModule::UUFNShoreFilterModule(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

float UUFNShoreFilterModule::GetNoise3D(float aX, float aY, float aZ)
{
	// This is only useful for 2D noise
	return -1.0f;
	

}

float UUFNShoreFilterModule::GetNoise2D(float aX, float aY)
{
	if (!(myInputModule)) {
		return 0.0f;
	}

	float startValue = myInputModule->GetNoise2D(aX, aY);

	if (startValue >= myShoreHeight + myThreshhold || startValue <= myShoreHeight - myThreshhold)
	{
		return startValue;
	}

	float alpha = (startValue + myThreshhold) / (myThreshhold * 2);

	return FMath::InterpSinInOut(startValue, 0.0f, 1.0f - alpha );

}

