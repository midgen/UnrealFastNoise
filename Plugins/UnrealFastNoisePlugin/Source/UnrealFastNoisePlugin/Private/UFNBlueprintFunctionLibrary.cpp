#include "UnrealFastNoisePlugin.h"
#include "FastNoise/FastNoise.h"
#include "UFNSelectModule.h"
#include "UFNBlendModule.h"
#include "UFNScaleBiasModule.h"
#include "UFNBlueprintFunctionLibrary.h"

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateNoiseGenerator(UObject* aOuter, ENoiseType aNoiseType, EFractalType aFractalType, int32 aSeed, int32 aOctaves, float aFrequency)
{
	UFastNoise* noiseGen = NewObject<UFastNoise>(aOuter, UFastNoise::StaticClass());

	noiseGen->SetNoiseType(aNoiseType);
	noiseGen->SetSeed(aSeed);
	noiseGen->SetFractalOctaves(aOctaves);
	noiseGen->SetFrequency(aFrequency);
	noiseGen->SetFractalType(aFractalType);

	return noiseGen;
}



UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateSelectModule(UObject* aOuter, UUFNNoiseGenerator* aInputModule1, UUFNNoiseGenerator* aInputModule2, UUFNNoiseGenerator* aSelectModule, float aFalloff)
{
	if (!(aInputModule1 && aInputModule2 && aSelectModule && aOuter)){
		return nullptr;
	}

	UUFNSelectModule* selectModule = NewObject<UUFNSelectModule>(aOuter, UUFNSelectModule::StaticClass());

	selectModule->inputModule1 = aInputModule1;
	selectModule->inputModule2 = aInputModule2;
	selectModule->selectModule = aSelectModule;
	selectModule->falloff = aFalloff;

	return selectModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateBlendModule(UObject* aOuter, UUFNNoiseGenerator* aInputModule1, UUFNNoiseGenerator* aInputModule2, UUFNNoiseGenerator* aSelectModule)
{
	if (!(aInputModule1 && aInputModule2 && aSelectModule && aOuter)) {
		return nullptr;
	}

	UUFNBlendModule* blendModule = NewObject<UUFNBlendModule>(aOuter, UUFNBlendModule::StaticClass());

	blendModule->inputModule1 = aInputModule1;
	blendModule->inputModule2 = aInputModule2;
	blendModule->selectModule = aSelectModule;

	return blendModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateScaleBiasModule(UObject* aOuter, UUFNNoiseGenerator* aInputModule, float aScale, float aBias)
{
	if (!(aInputModule && aOuter)) {
		return nullptr;
	}

	UUFNScaleBiasModule* scaleBiasModule = NewObject<UUFNScaleBiasModule>(aOuter, UUFNScaleBiasModule::StaticClass());

	scaleBiasModule->inputModule = aInputModule;
	scaleBiasModule->scale = aScale;
	scaleBiasModule->bias = aBias;

	return scaleBiasModule;
}

UUFNBlueprintFunctionLibrary::UUFNBlueprintFunctionLibrary(const class FObjectInitializer& obj)
	: Super(obj)
{

}