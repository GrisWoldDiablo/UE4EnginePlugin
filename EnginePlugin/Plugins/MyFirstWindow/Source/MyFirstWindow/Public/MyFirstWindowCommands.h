// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MyFirstWindowStyle.h"

class FMyFirstWindowCommands : public TCommands<FMyFirstWindowCommands>
{
public:

	FMyFirstWindowCommands()
		: TCommands<FMyFirstWindowCommands>(TEXT("MyFirstWindow"), NSLOCTEXT("Contexts", "MyFirstWindow", "MyFirstWindow Plugin"), NAME_None, FMyFirstWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};