#include "UnrealFastNoisePlugin/Public/UFNWarpModule.h"

UUFNWarpModule::UUFNWarpModule(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InputModule(nullptr)
	, WarpModule(nullptr)
	, Iteration1XOffset(0.f)
	, Iteration1YOffset(0.f)
	, Iteration1ZOffset(0.f) 
	, Iteration2XOffset1(0.f)
	, Iteration2YOffset1(0.f)
	, Iteration2ZOffset1(0.f)
	, Iteration2XOffset2(0.f)
	, Iteration2YOffset2(0.f)
	, Iteration2ZOffset2(0.f)
	, WarpIterations(EWarpIterations::One)
	, UnitSize(0.f)
	, Multiplier(0.f)
{
}

float UUFNWarpModule::GetNoise3D(float InX, float InY, float InZ)
{
	if (!(InputModule))
	{
		return 0.0f;
	}

	FVector p = FVector(InX, InY, InZ);

	FVector q = FVector(WarpModule->GetNoise3D(p.X, p.Y, p.Z), WarpModule->GetNoise3D(p.X + Iteration1XOffset, p.Y + Iteration1YOffset, p.Z + Iteration1ZOffset), WarpModule->GetNoise3D(p.X + Iteration1XOffset + 0.5f, p.Y + Iteration1YOffset + 0.5f, p.Z + Iteration1ZOffset + 2.4f));

	if (WarpIterations == EWarpIterations::One)
	{
		return (InputModule->GetNoise3D(p.X + (Multiplier * q.X), p.Y + (Multiplier * q.Y), p.Z + (Multiplier * q.Z)));
	}

	FVector r = FVector(WarpModule->GetNoise3D((p.X + (Multiplier * q).X) + Iteration2XOffset1, (p.Y + (Multiplier * q).Y) + Iteration2YOffset1, (p.Z + (Multiplier * q).Z) + Iteration2ZOffset1),
		WarpModule->GetNoise3D((p.X + (Multiplier * q).X) + Iteration2XOffset2, (p.Y + (Multiplier * q).Y) + Iteration2YOffset2, (p.Z + (Multiplier * q).Z) + Iteration2ZOffset2),
		WarpModule->GetNoise3D((p.X + (Multiplier * q).X + 3.4f) + Iteration2XOffset2, (p.Y + (Multiplier * q).Y) + Iteration2YOffset2 + 4.6f, (p.Z + (Multiplier * q).Z) + Iteration2ZOffset2) + 2.3f);

	return (InputModule->GetNoise3D(p.X + (Multiplier * r.X), p.Y + (Multiplier * r.Y), p.Z + (Multiplier * r.Z)));
}

float UUFNWarpModule::GetNoise2D(float InX, float InY)
{
	if ((!(InputModule)) || !WarpModule)
	{
		return 0.0f;
	}

	FVector2D p = FVector2D(InX, InY);

	FVector2D q = FVector2D(WarpModule->GetNoise2D(p.X, p.Y), WarpModule->GetNoise2D(p.X + Iteration1XOffset, p.Y + Iteration1YOffset));

	if (WarpIterations == EWarpIterations::One)
	{
		return (InputModule->GetNoise2D(p.X + (Multiplier * q.X), p.Y + (Multiplier * q.Y)));
	}

	FVector2D r = FVector2D(WarpModule->GetNoise2D((p.X + (Multiplier * q).X) + Iteration2XOffset1, (p.Y + (Multiplier * q).Y) + Iteration2YOffset1),
		WarpModule->GetNoise2D((p.X + (Multiplier * q).X) + Iteration2XOffset2, (p.Y + (Multiplier * q).Y) + Iteration2YOffset2));

	return (InputModule->GetNoise2D(p.X + (Multiplier * r.X), p.Y + (Multiplier * r.Y)));
}
