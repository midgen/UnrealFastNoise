#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ENoiseType : uint8
{
	Value, ValueFractal, Perlin, PerlinFractal, Simplex, SimplexFractal, WhiteNoise, Cellular, Cubic, CubicFractal
};
UENUM(BlueprintType)
enum class EFractalType : uint8
{
	FBM, Billow, RigidMulti
};
UENUM(BlueprintType)
enum class ECellularDistanceFunction : uint8
{
	Euclidean, Manhattan, Natural
};
UENUM(BlueprintType)
enum class ECellularReturnType : uint8
{
	CellValue, Distance, Distance2, Distance2Add, Distance2Sub, Distance2Mul, Distance2Div, NoiseLookup, Distance2Cave
};
UENUM(BlueprintType)
enum class EPerturbType : uint8
{
	None, Gradient, GradientFractal, Normalise, Gradient_Normalise, GradientFractal_Normalise
};
UENUM(BlueprintType)
enum class ESelectInterpType : uint8
{
	None,
	CircularIn,
	CircularOut,
	CircularInOut,
	ExponentialIn,
	ExponentialOut,
	ExponentialInOut,
	SineIn,
	SineOut,
	SineInOut,
	Step,
	Linear
};