
#include "UnrealFastNoisePlugin.h"
#include "UFNNoiseGenerator.h"
#include "UFNSelectModule.h"

UUFNSelectModule::UUFNSelectModule(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

float UUFNSelectModule::GetNoise3D(float aX, float aY, float aZ)
{
	if (!(inputModule1 && inputModule2 && selectModule)) {
		return 0.0f;
	}

	float control = selectModule->GetNoise3D(aX, aY, aZ);

	if (control > 0.0f + falloff) {
		return inputModule1->GetNoise3D(aX, aY, aZ);
	}
	else {
		return inputModule2->GetNoise3D(aX, aY, aZ);
	}
}

float UUFNSelectModule::GetNoise2D(float aX, float aY)
{
	if (!(inputModule1 && inputModule2 && selectModule)) {
		return 0.0f;
	}

	float control = selectModule->GetNoise2D(aX, aY);

	if (control > 0.0f + falloff) {
		return inputModule1->GetNoise2D(aX, aY);
	}
	else {
		return inputModule2->GetNoise2D(aX, aY);
	}
}

