# UnrealFastNoise
Modular, Blueprint-friendly noise generation for UE4

Provides a modular system for mixing noise generators in Blueprint. 

Note that the returned noisegenerator UOBJECT must be held in a variable to about being GC'ed.

Modules :

* NoiseGenerator - The main noise generator.
* SelectModule - Select from two different modules using a 3rd as a mask. Supports interpolation.
* 3SelectModule - Select from 3 different modules using a 4th as a mask.
* BlendModule - Blends between two different modules using a 3rd.
* ScaleBiasModule - Multiplies/Adds values from input module.
* WarpModule - Applies domain warping to the input module.
* AddModule - Adds two input module values together.
* ConstantModule - Returns a constant value.
* Simple/Fractal/Cellular Modules - More focused versions of NoiseGenerator (same code, just simpler nodes)
* RadialModule - Blends between 2 input modules based on distance from a given point.
