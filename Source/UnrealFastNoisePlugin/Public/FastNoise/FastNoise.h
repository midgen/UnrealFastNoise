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
#include "CoreMinimal.h"
#include "Object.h"
#include "UFNNoiseGenerator.h"
#include "FastNoiseSIMD.h"
#include "FastNoiseEnumerators.h"
#include "FastNoise.generated.h"



UCLASS()
class UNREALFASTNOISEPLUGIN_API UFastNoise : public UUFNNoiseGenerator
{
	GENERATED_UCLASS_BODY()
public:
	UFastNoise() { 
		myFastNoise = FastNoiseSIMD::NewFastNoiseSIMD(1337); 
		myFastNoise->SetSeed(1337); 
	};
	~UFastNoise() { delete myFastNoise; }

	// Returns seed used for all noise types
	void SetSeed(int seed) { myFastNoise->SetSeed(seed); }

	// Sets seed used for all noise types
	// Default: 1337
	int GetSeed(void) const { return myFastNoise->GetSeed(); }

	// Sets frequency for all noise types
	// Default: 0.01
	void SetFrequency(float frequency) { myFastNoise->SetFrequency(frequency); }

	// Sets noise return type of GetNoise(...)
	// Default: Simplex
	void SetNoiseType(ENoiseType noiseType) { myFastNoise->SetNoiseType(noiseType); }

	// Sets octave count for all fractal noise types
	// Default: 3
	void SetFractalOctaves(unsigned int octaves) { myFastNoise->SetFractalOctaves(octaves); }

	// Sets octave lacunarity for all fractal noise types
	// Default: 2.0
	void SetFractalLacunarity(float lacunarity) { myFastNoise->SetFractalLacunarity(lacunarity); }

	// Sets octave gain for all fractal noise types
	// Default: 0.5
	void SetFractalGain(float gain) { myFastNoise->SetFractalGain(gain); }

	// Sets method for combining octaves in all fractal noise types
	// Default: FBM
	void SetFractalType(EFractalType fractalType) { myFastNoise->SetFractalType(fractalType); }

	// Sets return type from cellular noise calculations
	// Note: NoiseLookup requires another FastNoise object be set with SetCellularNoiseLookup() to function
	// Default: CellValue
	void SetCellularDistanceFunction(ECellularDistanceFunction cellularDistanceFunction) { myFastNoise->SetCellularDistanceFunction(cellularDistanceFunction); }

	// Sets distance function used in cellular noise calculations
	// Default: Euclidean
	void SetCellularReturnType(ECellularReturnType cellularReturnType) { myFastNoise->SetCellularReturnType(cellularReturnType); }



	FORCEINLINE float GetNoise(float x, float y);
	FORCEINLINE float GetNoise2D(float x, float y);


	FORCEINLINE float GetNoise(float x, float y, float z);
	FORCEINLINE float GetNoise3D(float x, float y, float z);


private:

	FastNoiseSIMD* myFastNoise;




};