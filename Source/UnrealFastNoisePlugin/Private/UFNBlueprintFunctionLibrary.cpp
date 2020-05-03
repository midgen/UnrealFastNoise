#include "UnrealFastNoisePlugin/Public/UFNBlueprintFunctionLibrary.h"

#include "UnrealFastNoisePlugin/Public/FastNoise/FastNoise.h"
#include "UnrealFastNoisePlugin/Public/UFN3SelectModule.h"
#include "UnrealFastNoisePlugin/Public/UFNAddModule.h"
#include "UnrealFastNoisePlugin/Public/UFNBlendModule.h"
#include "UnrealFastNoisePlugin/Public/UFNConstantModule.h"
#include "UnrealFastNoisePlugin/Public/UFNRadialModule.h"
#include "UnrealFastNoisePlugin/Public/UFNScaleBiasModule.h"
#include "UnrealFastNoisePlugin/Public/UFNSelectModule.h"
#include "UnrealFastNoisePlugin/Public/UFNShoreFilterModule.h"
#include "UnrealFastNoisePlugin/Public/UFNSplineGenerator.h"
#include "UnrealFastNoisePlugin/Public/UFNWarpModule.h"

#include <Runtime/Engine/Classes/Components/SplineComponent.h>

UUFNBlueprintFunctionLibrary::UUFNBlueprintFunctionLibrary(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateNoiseGenerator(UObject* outer, ENoiseType noiseType, ECellularDistanceFunction cellularDistanceFunction, ECellularReturnType cellularReturnType, EFractalType fractalType, EInterp interpolation, int32 seed, int32 octaves, float frequency, float lacunarity, float fractalGain)
{
	UFastNoise* NoiseGen = NewObject<UFastNoise>(outer);

	NoiseGen->SetNoiseType(noiseType);
	NoiseGen->SetSeed(seed);
	NoiseGen->SetFractalOctaves(octaves);
	NoiseGen->SetFrequency(frequency);
	NoiseGen->SetFractalType(fractalType);
	NoiseGen->SetFractalLacunarity(lacunarity);
	NoiseGen->SetFractalGain(fractalGain);
	NoiseGen->SetCellularDistanceFunction(cellularDistanceFunction);
	NoiseGen->SetCellularReturnType(cellularReturnType);
	NoiseGen->SetInterp(interpolation);

	return NoiseGen;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateSelectModule(UObject* outer, UUFNNoiseGenerator* inputModule1, UUFNNoiseGenerator* inputModule2, UUFNNoiseGenerator* selectModule, ESelectInterpType interpolationType, float falloff, float threshold, int32 numSteps)
{
	if (!(inputModule1 && inputModule2 && selectModule && outer))
	{
		return nullptr;
	}

	UUFNSelectModule* NewSelectModule = NewObject<UUFNSelectModule>(outer);

	NewSelectModule->InputModule1 = inputModule1;
	NewSelectModule->InputModule2 = inputModule2;
	NewSelectModule->SelectModule = selectModule;
	NewSelectModule->Falloff = falloff;
	NewSelectModule->Threshold = threshold;
	NewSelectModule->InterpType = interpolationType;
	NewSelectModule->NumSteps = numSteps;

	return NewSelectModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateBlendModule(UObject* outer, UUFNNoiseGenerator* inputModule1, UUFNNoiseGenerator* inputModule2, UUFNNoiseGenerator* selectModule, UCurveFloat* blendCurve)
{
	if (!(inputModule1 && inputModule2 && selectModule && outer))
	{
		return nullptr;
	}

	UUFNBlendModule* BlendModule = NewObject<UUFNBlendModule>(outer);

	BlendModule->InputModule1 = inputModule1;
	BlendModule->InputModule2 = inputModule2;
	BlendModule->SelectModule = selectModule;
	BlendModule->BlendCurve = blendCurve;

	return BlendModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateScaleBiasModule(UObject* outer, UUFNNoiseGenerator* inputModule, float scale, float bias)
{
	if (!(inputModule && outer))
	{
		return nullptr;
	}

	UUFNScaleBiasModule* ScaleBiasModule = NewObject<UUFNScaleBiasModule>(outer);

	ScaleBiasModule->InputModule = inputModule;
	ScaleBiasModule->Scale = scale;
	ScaleBiasModule->Bias = bias;

	return ScaleBiasModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateWarpModule(UObject* outer, UUFNNoiseGenerator* inputModule, UUFNNoiseGenerator* warpModule, float multiplier, EWarpIterations warpIterations)
{
	if (!(inputModule && outer))
	{
		return nullptr;
	}

	UUFNWarpModule* ThiswarpModule = NewObject<UUFNWarpModule>(outer);

	ThiswarpModule->InputModule = inputModule;
	ThiswarpModule->WarpModule = warpModule;
	ThiswarpModule->Iteration1XOffset = 1.6f;
	ThiswarpModule->Iteration1YOffset = 2.5f;
	ThiswarpModule->Iteration2XOffset1 = 5.7f;
	ThiswarpModule->Iteration2YOffset1 = 3.4f;
	ThiswarpModule->Iteration2XOffset2 = 2.1f;
	ThiswarpModule->Iteration2YOffset2 = 3.5f;
	ThiswarpModule->Multiplier = multiplier;
	ThiswarpModule->WarpIterations = warpIterations;

	return ThiswarpModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateAddModule(UObject* outer, UUFNNoiseGenerator* inputModule1, UUFNNoiseGenerator* inputModule2, UUFNNoiseGenerator* maskModule, float threshold)
{
	if (!(outer && inputModule1 && inputModule2))
	{
		return nullptr;
	}

	UUFNAddModule* NoiseGen = NewObject<UUFNAddModule>(outer);

	NoiseGen->InputModule1 = inputModule1;
	NoiseGen->InputModule2 = inputModule2;
	NoiseGen->MaskModule = maskModule;
	NoiseGen->Threshold = threshold;

	return NoiseGen;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateConstantModule(UObject* outer, float constantValue)
{
	UUFNConstantModule* NoiseGen = NewObject<UUFNConstantModule>(outer);

	NoiseGen->ConstantValue = constantValue;

	return NoiseGen;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateSimpleNoiseGenerator(UObject* outer, ESimpleNoiseType noiseType, int32 seed, float frequency, EInterp interpolation)
{
	UFastNoise* NoiseGen = NewObject<UFastNoise>(outer);

	switch (noiseType)
	{
	case ESimpleNoiseType::SimpleGradient:
		NoiseGen->SetNoiseType(ENoiseType::Gradient);
		break;
	case ESimpleNoiseType::SimpleSimplex:
		NoiseGen->SetNoiseType(ENoiseType::Simplex);
		break;
	case ESimpleNoiseType::SimpleValue:
		NoiseGen->SetNoiseType(ENoiseType::Value);
		break;
	case ESimpleNoiseType::SimpleWhiteNoise:
		NoiseGen->SetNoiseType(ENoiseType::WhiteNoise);
		break;
	}

	NoiseGen->SetSeed(seed);
	NoiseGen->SetFrequency(frequency);
	NoiseGen->SetInterp(interpolation);

	return NoiseGen;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateFractalNoiseGenerator(UObject* outer, EFractalNoiseType noiseType, int32 seed, float frequency, float fractalGain, EInterp interpolation, EFractalType fractalType, int32 octaves, float lacunarity)
{
	UFastNoise* NoiseGen = NewObject<UFastNoise>(outer);

	switch (noiseType)
	{
	case EFractalNoiseType::FractalGradient:
		NoiseGen->SetNoiseType(ENoiseType::GradientFractal);
		break;
	case EFractalNoiseType::FractalSimplex:
		NoiseGen->SetNoiseType(ENoiseType::SimplexFractal);
		break;
	case EFractalNoiseType::FractalValue:
		NoiseGen->SetNoiseType(ENoiseType::ValueFractal);
		break;
	}

	NoiseGen->SetSeed(seed);
	NoiseGen->SetFractalOctaves(octaves);
	NoiseGen->SetFrequency(frequency);
	NoiseGen->SetFractalType(fractalType);
	NoiseGen->SetFractalGain(fractalGain);
	NoiseGen->SetFractalLacunarity(lacunarity);
	NoiseGen->SetInterp(interpolation);

	return NoiseGen;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateCellularNoiseGenerator(UObject* outer, int32 seed, float frequency, ECellularDistanceFunction cellularDistanceFunction, ECellularReturnType cellularReturnType)
{
	UFastNoise* NoiseGen = NewObject<UFastNoise>(outer);

	NoiseGen->SetNoiseType(ENoiseType::Cellular);
	NoiseGen->SetSeed(seed);
	NoiseGen->SetFrequency(frequency);
	NoiseGen->SetCellularDistanceFunction(cellularDistanceFunction);
	NoiseGen->SetCellularReturnType(cellularReturnType);

	return NoiseGen;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::Create3SelectModule(UObject* outer, UUFNNoiseGenerator* inputModule1, UUFNNoiseGenerator* inputModule2, UUFNNoiseGenerator* inputModule3, UUFNNoiseGenerator* selectModule, float lowerThreshold /*= 0.0f*/, float upperThreshold /*= 0.0f*/, ESelectInterpType interpolationType /*= ESelectInterpType::None*/, float falloff /*= 0.0f*/, int32 steps /*= 4*/)
{
	if (!(inputModule1 && inputModule2 && inputModule3 && selectModule && outer))
	{
		return nullptr;
	}

	UUFN3SelectModule* NewSelectModule = NewObject<UUFN3SelectModule>(outer);

	NewSelectModule->InputModule1 = inputModule1;
	NewSelectModule->InputModule2 = inputModule2;
	NewSelectModule->InputModule3 = inputModule3;
	NewSelectModule->SelectModule = selectModule;
	NewSelectModule->Falloff = falloff;
	NewSelectModule->LowerThreshold = lowerThreshold;
	NewSelectModule->UpperThreshold = upperThreshold;
	NewSelectModule->InterpType = interpolationType;
	NewSelectModule->NumSteps = steps;

	return NewSelectModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateSplineGenerator(UObject* outer, float MaxDistance, float MinDistance, TArray<USplineComponent*> Splines, UCurveFloat* falloffCurve)
{
	UUFNSplineGenerator* NewSplineGenerator = NewObject<UUFNSplineGenerator>(outer);
	NewSplineGenerator->MaximumDistance = MaxDistance;
	NewSplineGenerator->MinimumDistance = MinDistance;
	NewSplineGenerator->Splines = Splines;
	NewSplineGenerator->FalloffCurve = falloffCurve;

	return NewSplineGenerator;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateRadialModule(UObject* outer, UUFNNoiseGenerator* inputModule1, UUFNNoiseGenerator* inputModule2, ESelectInterpType interpolationType, FVector origin, float radius, float falloff, int32 numSteps)
{
	if (!(inputModule1 && inputModule2 && outer))
	{
		return nullptr;
	}

	UUFNRadialModule* NewRadialModule = NewObject<UUFNRadialModule>(outer);

	NewRadialModule->InputModule1 = inputModule1;
	NewRadialModule->InputModule2 = inputModule2;
	NewRadialModule->Falloff2 = falloff * falloff;
	NewRadialModule->Radius2 = radius * radius;
	NewRadialModule->Origin = origin;
	NewRadialModule->InterpType = interpolationType;
	NewRadialModule->NumSteps = numSteps;

	return NewRadialModule;
}

UUFNNoiseGenerator* UUFNBlueprintFunctionLibrary::CreateShoreFilterModule(UObject* outer, UUFNNoiseGenerator* inputModule1, const float shoreHeight, const float threshold)
{
	if (!(inputModule1 && outer))
	{
		return nullptr;
	}

	UUFNShoreFilterModule* NewShoreFilterModule = NewObject<UUFNShoreFilterModule>(outer);

	NewShoreFilterModule->InputModule = inputModule1;
	NewShoreFilterModule->ShoreHeight = shoreHeight;
	NewShoreFilterModule->Threshhold = threshold;

	return NewShoreFilterModule;
}

