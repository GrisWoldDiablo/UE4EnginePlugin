// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyFirstWindowCommands.h"

#define LOCTEXT_NAMESPACE "FMyFirstWindowModule"

void FMyFirstWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "MyFirstWindow", "Bring up MyFirstWindow window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
