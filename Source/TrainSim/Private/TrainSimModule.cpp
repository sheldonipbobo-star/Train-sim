// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrainSimModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FTrainSimModule, TrainSim);

void FTrainSimModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("TrainSim Module Started"));
}

void FTrainSimModule::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("TrainSim Module Shutdown"));
}
