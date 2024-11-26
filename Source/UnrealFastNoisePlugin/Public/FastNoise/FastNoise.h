// FastNoise.h
//
// MIT License
//
// Copyright(c) 2016 Jordan Peck
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The developer's email is jorzixdan.me2@gzixmail.com (for great email, take
// off every 'zix'.)
//
// UnrealEngine-ified by Chris Ashworth 2016
//

#pragma once

#include "UnrealFastNoisePlugin/Public/UFNNoiseGenerator.h"
#include <Runtime/CoreUObject/Public/UObject/Object.h>

#include "FastNoise.generated.h"

UENUM(BlueprintType)
enum class EUFN_NoiseType : uint8
{
	Value,
	ValueFractal,
	Gradient,
	GradientFractal,
	Simplex,
	SimplexFractal,
	Cellular,
	WhiteNoise
};
UENUM(BlueprintType)
enum class ESimpleNoiseType : uint8
{
	SimpleValue UMETA(DisplayName = "Value"),
	SimpleGradient UMETA(DisplayName = "Gradient"),
	SimpleSimplex UMETA(DisplayName = "Simplex"),
	SimpleWhiteNoise UMETA(DisplayName = "WhiteNoise")
};
UENUM(BlueprintType)
enum class EFractalNoiseType : uint8
{
	FractalValue UMETA(DisplayName = "Value"),
	FractalGradient UMETA(DisplayName = "Gradient"),
	FractalSimplex UMETA(DisplayName = "Simplex")
};
UENUM(BlueprintType)
enum class EInterp : uint8
{
	InterpLinear UMETA(DisplayName = "Linear"),
	InterpHermite UMETA(DisplayName = "Hermite"),
	InterpQuintic UMETA(DisplayName = "Quintic")
};
UENUM(BlueprintType)
enum class EFractalType : uint8
{
	FBM,
	Billow,
	RigidMulti
};
UENUM(BlueprintType)
enum class ECellularDistanceFunction : uint8
{
	Euclidean,
	Manhattan,
	Natural
};
UENUM(BlueprintType)
enum class ECellularReturnType : uint8
{
	CellValue,
	NoiseLookup,
	Distance,
	Distance2,
	Distance2Add,
	Distance2Sub,
	Distance2Mul,
	Distance2Div
};
UENUM(BlueprintType)
enum class EPositionWarpType : uint8
{
	None,
	Regular,
	Fractal
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

UCLASS()
class UNREALFASTNOISEPLUGIN_API UFastNoise : public UUFNNoiseGenerator
{
	GENERATED_BODY()
public:
	UFastNoise(const FObjectInitializer& InIntializer);
	~UFastNoise() { delete m_cellularNoiseLookup; }

	// Returns seed used for all noise types
	void SetSeed(int seed);

	// Sets seed used for all noise types
	// Default: 1337
	int GetSeed(void) const { return m_seed; }

	// Sets frequency for all noise types
	// Default: 0.01
	void SetFrequency(float frequency) { m_frequency = frequency; }

	// Changes the interpolation method used to smooth between noise values
	// Possible interpolation methods (lowest to highest quality) :
	// - Linear
	// - Hermite
	// - Quintic
	// Used in Value, Gradient Noise and Position Warping
	// Default: Quintic
	void SetInterp(EInterp interp) { m_interp = interp; }

	// Sets noise return type of GetNoise(...)
	// Default: Simplex
	void SetNoiseType(EUFN_NoiseType noiseType) { m_noiseType = noiseType; }

	// Sets octave count for all fractal noise types
	// Default: 3
	void SetFractalOctaves(unsigned int octaves)
	{
		m_octaves = octaves;
		CalculateFractalBounding();
	}

	// Sets octave lacunarity for all fractal noise types
	// Default: 2.0
	void SetFractalLacunarity(float lacunarity) { m_lacunarity = lacunarity; }

	// Sets octave gain for all fractal noise types
	// Default: 0.5
	void SetFractalGain(float gain)
	{
		m_gain = gain;
		CalculateFractalBounding();
	}

	// Sets method for combining octaves in all fractal noise types
	// Default: FBM
	void SetFractalType(EFractalType fractalType) { m_fractalType = fractalType; }

	// Sets return type from cellular noise calculations
	// Note: NoiseLookup requires another FastNoise object be set with SetCellularNoiseLookup() to function
	// Default: CellValue
	void SetCellularDistanceFunction(ECellularDistanceFunction cellularDistanceFunction) { m_cellularDistanceFunction = cellularDistanceFunction; }

	// Sets distance function used in cellular noise calculations
	// Default: Euclidean
	void SetCellularReturnType(ECellularReturnType cellularReturnType) { m_cellularReturnType = cellularReturnType; }

	// Noise used to calculate a cell value if cellular return type is NoiseLookup
	// The lookup value is acquired through GetNoise() so ensure you SetNoiseType() on the noise lookup, value, gradient or simplex is recommended
	void SetCellularNoiseLookup(UFastNoise* noise) { m_cellularNoiseLookup = noise; }

	// Sets the maximum warp distance from original location when using PositionWarp{Fractal}(...)
	// Default: 1.0
	void SetPositionWarpAmp(float positionWarpAmp) { m_positionWarpAmp = positionWarpAmp / 0.45f; }
	void SetPositionWarpType(EPositionWarpType positionWarpType) { m_positionWarpType = positionWarpType; }

	//2D
	float GetValue(float x, float y);
	float GetValueFractal(float x, float y);

	float GetGradient(float x, float y);
	float GetGradientFractal(float x, float y);

	float GetSimplex(float x, float y);
	float GetSimplexFractal(float x, float y);

	float GetCellular(float x, float y);

	float GetWhiteNoise(float x, float y);
	float GetWhiteNoiseInt(int x, int y);

	FORCEINLINE float GetNoise(float x, float y)
	{
		x *= m_frequency;
		y *= m_frequency;

		switch (m_noiseType)
		{
		case EUFN_NoiseType::Value:
			return SingleValue(0, x, y);
		case EUFN_NoiseType::ValueFractal:
			switch (m_fractalType)
			{
			case EFractalType::FBM:
				return SingleValueFractalFBM(x, y);
			case EFractalType::Billow:
				return SingleValueFractalBillow(x, y);
			case EFractalType::RigidMulti:
				return SingleValueFractalRigidMulti(x, y);
			default:
				return 0.0f;
			}
		case EUFN_NoiseType::Gradient:
			return SingleGradient(0, x, y);
		case EUFN_NoiseType::GradientFractal:
			switch (m_fractalType)
			{
			case EFractalType::FBM:
				return SingleGradientFractalFBM(x, y);
			case EFractalType::Billow:
				return SingleGradientFractalBillow(x, y);
			case EFractalType::RigidMulti:
				return SingleGradientFractalRigidMulti(x, y);
			default:
				return 0.0f;
			}
		case EUFN_NoiseType::Simplex:
			return SingleSimplex(0, x, y);
		case EUFN_NoiseType::SimplexFractal:
			switch (m_fractalType)
			{
			case EFractalType::FBM:
				return SingleSimplexFractalFBM(x, y);
			case EFractalType::Billow:
				return SingleSimplexFractalBillow(x, y);
			case EFractalType::RigidMulti:
				return SingleSimplexFractalRigidMulti(x, y);
			default:
				return 0.0f;
			}
		case EUFN_NoiseType::Cellular:
			switch (m_cellularReturnType)
			{
			case ECellularReturnType::CellValue:
			case ECellularReturnType::NoiseLookup:
			case ECellularReturnType::Distance:
				return SingleCellular(x, y);
			default:
				return SingleCellular2Edge(x, y);
			}
		case EUFN_NoiseType::WhiteNoise:
			return GetWhiteNoise(x, y);
		default:
			return 0.0f;
		}
	}
	FORCEINLINE float GetNoise2D(float InX, float InY)
	{
		switch (m_positionWarpType)
		{
		default:
		case EPositionWarpType::None:
			return GetNoise(InX, InY);
		case EPositionWarpType::Fractal:
			PositionWarpFractal(InX, InY);
			return GetNoise(InX, InY);
		case EPositionWarpType::Regular:
			PositionWarp(InX, InY);
			return GetNoise(InX, InY);
		}
	}

	FORCEINLINE FVector GetNoise2DDeriv(float x, float y)
	{
		FVector2D p = FVector2D(x, y);
		p.X = FMath::FloorToFloat(p.X);
		p.Y = FMath::FloorToFloat(p.Y);
		FVector2D f = FVector2D(x, y) - p;

		FVector2D u = f * f * f;

		float a = GetNoise2D(p.X, p.Y);
		float b = GetNoise2D(p.X + 1.f, p.Y);
		float c = GetNoise2D(p.X, p.Y + 1.f);
		float d = GetNoise2D(p.X + 1.0f, p.Y + 1.0f);

		FVector result;

		const FVector2D Intermediate = 6.0f * f * (f) * (FVector2D(b - a, c - a) + (a - b - c + d) * (FVector2D(u.Y, u.X)));

		result = FVector(a + (b - a) * u.X + (c - a) * u.Y + (a - b - c + d) * u.X * u.Y,
			Intermediate.X, Intermediate.Y);

		//result = FVector(a + (b - a)*u.X + (c - a)*u.Y + (a - b - c + d)*u.X*u.Y,
		//6.0*f*(1.0 - f)*(FVector2D(b - a, c - a) + (a - b - c + d)*(FVector2D(u.Y, u.X))));

		return result;
	}

	void PositionWarp(float& x, float& y);
	void PositionWarpFractal(float& x, float& y);

	//3D
	float GetValue(float x, float y, float z);
	float GetValueFractal(float x, float y, float z);

	float GetGradient(float x, float y, float z);
	float GetGradientFractal(float x, float y, float z);

	float GetSimplex(float x, float y, float z);
	float GetSimplexFractal(float x, float y, float z);

	float GetCellular(float x, float y, float z);

	float GetWhiteNoise(float x, float y, float z);
	float GetWhiteNoiseInt(int x, int y, int z);

	FORCEINLINE float GetNoise(float x, float y, float z)
	{
		x *= m_frequency;
		y *= m_frequency;
		z *= m_frequency;

		switch (m_noiseType)
		{
		case EUFN_NoiseType::Value:
			return SingleValue(0, x, y, z);
		case EUFN_NoiseType::ValueFractal:
			switch (m_fractalType)
			{
			case EFractalType::FBM:
				return SingleValueFractalFBM(x, y, z);
			case EFractalType::Billow:
				return SingleValueFractalBillow(x, y, z);
			case EFractalType::RigidMulti:
				return SingleValueFractalRigidMulti(x, y, z);
			default:
				return 0.0f;
			}
		case EUFN_NoiseType::Gradient:
			return SingleGradient(0, x, y, z);
		case EUFN_NoiseType::GradientFractal:
			switch (m_fractalType)
			{
			case EFractalType::FBM:
				return SingleGradientFractalFBM(x, y, z);
			case EFractalType::Billow:
				return SingleGradientFractalBillow(x, y, z);
			case EFractalType::RigidMulti:
				return SingleGradientFractalRigidMulti(x, y, z);
			default:
				return 0.0f;
			}
		case EUFN_NoiseType::Simplex:
			return SingleSimplex(0, x, y, z);
		case EUFN_NoiseType::SimplexFractal:
			switch (m_fractalType)
			{
			case EFractalType::FBM:
				return SingleSimplexFractalFBM(x, y, z);
			case EFractalType::Billow:
				return SingleSimplexFractalBillow(x, y, z);
			case EFractalType::RigidMulti:
				return SingleSimplexFractalRigidMulti(x, y, z);
			default:
				return 0.0f;
			}
		case EUFN_NoiseType::Cellular:
			switch (m_cellularReturnType)
			{
			case ECellularReturnType::CellValue:
			case ECellularReturnType::NoiseLookup:
			case ECellularReturnType::Distance:
				return SingleCellular(x, y, z);
			default:
				return SingleCellular2Edge(x, y, z);
			}
		case EUFN_NoiseType::WhiteNoise:
			return GetWhiteNoise(x, y, z);
		default:
			return 0.0f;
		}
	}
	FORCEINLINE float GetNoise3D(float InX, float InY, float InZ)
	{
		switch (m_positionWarpType)
		{
		default:
		case EPositionWarpType::None:
			return GetNoise(InX, InY, InZ);
		case EPositionWarpType::Fractal:
			PositionWarpFractal(InX, InY, InZ);
			return GetNoise(InX, InY, InZ);
		case EPositionWarpType::Regular:
			PositionWarp(InX, InY, InZ);
			return GetNoise(InX, InY, InZ);
		}
	}

	void PositionWarp(float& x, float& y, float& z);
	void PositionWarpFractal(float& x, float& y, float& z);

	//4D
	float GetSimplex(float x, float y, float z, float w);

	float GetWhiteNoise(float x, float y, float z, float w);
	float GetWhiteNoiseInt(int x, int y, int z, int w);

protected:
	unsigned char m_perm[512];
	unsigned char m_perm12[512];

	int m_seed = 1337;
	float m_frequency = 0.01f;
	EInterp m_interp = EInterp::InterpQuintic;
	EUFN_NoiseType m_noiseType = EUFN_NoiseType::Simplex;

	EPositionWarpType m_positionWarpType = EPositionWarpType::None;

	unsigned int m_octaves = 3;
	float m_lacunarity = 2.0f;
	float m_gain = 0.5f;
	EFractalType m_fractalType = EFractalType::FBM;

	float m_fractalBounding;
	void CalculateFractalBounding()
	{
		float amp = m_gain;
		float ampFractal = 1.0f;
		for (unsigned int i = 1; i < m_octaves; i++)
		{
			ampFractal += amp;
			amp *= m_gain;
		}
		m_fractalBounding = 1.0f / ampFractal;
	}

	ECellularDistanceFunction m_cellularDistanceFunction = ECellularDistanceFunction::Euclidean;
	ECellularReturnType m_cellularReturnType = ECellularReturnType::CellValue;
	UFastNoise* m_cellularNoiseLookup = nullptr;

	float m_positionWarpAmp = 1.0f / 0.45f;

	//2D
	float SingleValueFractalFBM(float x, float y);
	float SingleValueFractalBillow(float x, float y);
	float SingleValueFractalRigidMulti(float x, float y);
	float SingleValue(unsigned char offset, float x, float y);

	float SingleGradientFractalFBM(float x, float y);
	float SingleGradientFractalBillow(float x, float y);
	float SingleGradientFractalRigidMulti(float x, float y);
	float SingleGradient(unsigned char offset, float x, float y);

	float SingleSimplexFractalFBM(float x, float y);
	float SingleSimplexFractalBillow(float x, float y);
	float SingleSimplexFractalRigidMulti(float x, float y);
	float SingleSimplex(unsigned char offset, float x, float y);

	float SingleCellular(float x, float y);
	float SingleCellular2Edge(float x, float y);

	void SinglePositionWarp(unsigned char offset, float warpAmp, float frequency, float& x, float& y);

	//3D
	float SingleValueFractalFBM(float x, float y, float z);
	float SingleValueFractalBillow(float x, float y, float z);
	float SingleValueFractalRigidMulti(float x, float y, float z);
	float SingleValue(unsigned char offset, float x, float y, float z);

	float SingleGradientFractalFBM(float x, float y, float z);
	float SingleGradientFractalBillow(float x, float y, float z);
	float SingleGradientFractalRigidMulti(float x, float y, float z);
	float SingleGradient(unsigned char offset, float x, float y, float z);

	float SingleSimplexFractalFBM(float x, float y, float z);
	float SingleSimplexFractalBillow(float x, float y, float z);
	float SingleSimplexFractalRigidMulti(float x, float y, float z);
	float SingleSimplex(unsigned char offset, float x, float y, float z);

	float SingleCellular(float x, float y, float z);
	float SingleCellular2Edge(float x, float y, float z);

	void SinglePositionWarp(unsigned char offset, float warpAmp, float frequency, float& x, float& y, float& z);

	//4D
	float SingleSimplex(unsigned char offset, float x, float y, float z, float w);

private:
	inline unsigned char Index2D_12(unsigned char offset, int x, int y);
	inline unsigned char Index3D_12(unsigned char offset, int x, int y, int z);
	inline unsigned char Index4D_32(unsigned char offset, int x, int y, int z, int w);
	inline unsigned char Index2D_256(unsigned char offset, int x, int y);
	inline unsigned char Index3D_256(unsigned char offset, int x, int y, int z);
	inline unsigned char Index4D_256(unsigned char offset, int x, int y, int z, int w);

	inline float ValCoord2DFast(unsigned char offset, int x, int y);
	inline float ValCoord3DFast(unsigned char offset, int x, int y, int z);
	inline float GradCoord2D(unsigned char offset, int x, int y, float xd, float yd);
	inline float GradCoord3D(unsigned char offset, int x, int y, int z, float xd, float yd, float zd);
	inline float GradCoord4D(unsigned char offset, int x, int y, int z, int w, float xd, float yd, float zd, float wd);
};
