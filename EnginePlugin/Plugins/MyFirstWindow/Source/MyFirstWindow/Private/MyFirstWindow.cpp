// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyFirstWindow.h"
#include "MyFirstWindowStyle.h"
#include "MyFirstWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Editor/EditorEngine.h"
#include "Engine/Selection.h"
#include <EnginePlugin\MyCube.h>
#include "Editor/EditorEngine.h"
#include <DeclarativeSyntaxSupport.h>
#include <ClassViewerModule.h>
#include <Kismet/GameplayStatics.h>
#include <SSCSEditor.h>
#include <PropertyEditorModule.h>

static const FName MyFirstWindowTabName("MyFirstWindow");

#define LOCTEXT_NAMESPACE "FMyFirstWindowModule"

void FMyFirstWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FMyFirstWindowStyle::Initialize();
	FMyFirstWindowStyle::ReloadTextures();

	FMyFirstWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMyFirstWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMyFirstWindowModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMyFirstWindowModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMyFirstWindowModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MyFirstWindowTabName, FOnSpawnTab::CreateRaw(this, &FMyFirstWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMyFirstWindowTabTitle", "MyFirstWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMyFirstWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMyFirstWindowStyle::Shutdown();

	FMyFirstWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MyFirstWindowTabName);
}

TSharedRef<SDockTab> FMyFirstWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FMyFirstWindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("MyFirstWindow.cpp"))
		);
	TSharedPtr<SMultiLineEditableTextBox> EditableTextBox;

	FClassViewerInitializationOptions InitOptions;
	InitOptions.Mode = EClassViewerMode::ClassPicker;
	InitOptions.DisplayMode = EClassViewerDisplayMode::ListView;
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");
	
	//TSharedPtr<SBox> ComponentsBox = SNew(SBox)
	//	.Visibility(EVisibility::Collapsed);

	//TSharedPtr<class SSCSEditor> SCSEditor = SNew(SSCSEditor)
	//	.EditorMode(EComponentEditorMode::ActorInstance)
	//	.AllowEditing_Lambda([=] {return GEditor->PlayWorld == nullptr; })
	//	.ActorContext_Lambda([=] {return GEditor->GetSelectedActors()->GetTop<AActor>(); });

	//	//.OnSelectionUpdated(this, &SActorDetails::OnSCSEditorTreeViewSelectionChanged)
	//	//.OnItemDoubleClicked(this, &SActorDetails::OnSCSEditorTreeViewItemDoubleClicked)
	//ComponentsBox->SetVisibility(EVisibility::Visible);
	//ComponentsBox->SetContent(SCSEditor.ToSharedRef());

	
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			/*SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			],*/
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				[
					/*SNew(SMultiLineEditableTextBox)
					.Text(myText)*/
					ClassViewerModule.CreateClassViewer(InitOptions, FOnClassPicked::CreateRaw(this, &FMyFirstWindowModule::ClassPicker))
				]
	/*+ SHorizontalBox::Slot()
		[
			ComponentsBox.ToSharedRef()
		]*/
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.FillWidth(0.2f)
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Text(FText::FromString("Click Me"))
					.OnClicked(FOnClicked::CreateRaw(this, &FMyFirstWindowModule::OnClicked))
				]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.FillWidth(0.2f)
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Text(FText::FromString("Try Me"))
				.OnClicked(FOnClicked::CreateLambda([=] {
				if (ChosenClass)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s"), *ChosenClass->GetName());
					auto act = Cast<AActor>(ChosenClass);
					if (act)
					{
						//GEditor->SelectActor()
						GEditor->SelectActor(act, true, true);
						auto selections = GEditor->GetSelectedActors();
						for (FSelectionIterator It(*selections); It; ++It)
						{
							auto actor = Cast<AActor>(*It);
							if (actor != nullptr)
							{
								UE_LOG(LogTemp, Warning, TEXT("%s,(%s)"), *actor->GetClass()->GetName(), *actor->GetActorLabel());
								//actor->SetActorScale3D(actor->GetActorScale3D() * 1.1f);
							}
						}
					}
				}
					return FReply::Handled();
					}))
				]
				
		];
}
FReply FMyFirstWindowModule::OnClicked()
{
	TArray<AActor*> AllActors;
	auto gworld = GEditor->GetEditorWorldContext(true).World();
	UGameplayStatics::GetAllActorsOfClass(gworld, AActor::StaticClass(), AllActors);
	for (auto acto : AllActors)
	{
		if (acto)
		{
			UE_LOG(LogTemp, Warning, TEXT("{%s}, %s,(%s)"), *acto->GetWorld()->GetName(), *acto->GetClass()->GetName(), *acto->GetActorLabel());
			if (ChosenClass)
			{
				UE_LOG(LogTemp, Warning, TEXT("ChosenClass: {%s} Acto:(%s)"), *ChosenClass->GetName(), *acto->GetName());
			}
		}
		if (acto->GetClass()->IsChildOf(ChosenClass))
		{
			GEditor->SelectNone(true, true);
			GEditor->SelectActor(acto, true, true);
			GEditor->SelectAllActorsWithClass(false);
			break;
		}
	}
	
	auto selections = GEditor->GetSelectedActors();
	for (FSelectionIterator It(*selections); It; ++It)
	{
		auto actor = Cast<AMyCube>(*It);
		if (actor != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("{%s}, %s,(%s)"), *actor->GetWorld()->GetName(), *actor->GetClass()->GetName(), *actor->GetActorLabel());
			UE_LOG(LogTemp, Warning, TEXT("Enum: {%s}"), *actor->GetEnumAsString());
			actor->SetActorScale3D(actor->GetActorScale3D() * 1.1f);
		}
	}
	//for (size_t i = 0; i < selections->Num(); i++)
	//{
	//	auto actor = selections.TClassIterator[i];
	//	UE_LOG(LogTemp, Warning, TEXT("%s,(%s)"), *actor->GetName());
	//}
	/*
	for (auto sel : allSelected) {
	auto actor = Cast<AActor>(sel);
	UE_LOG(LogTemp, Warning, TEXT("%s,(%s)"),*actor.GetClass()->GetName(), *actor.GetActorLabel());
	}*/
	UE_LOG(LogTemp, Warning, TEXT("I GOT A JOB!!!"));
	return FReply::Handled();
}

void FMyFirstWindowModule::ClassPicker(UClass* AssetClass) {
	ChosenClass = AssetClass;
	UE_LOG(LogTemp, Warning, TEXT("Raw Deletage {%s}"), *AssetClass->GetName());
}

void FMyFirstWindowModule::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	
}


void FMyFirstWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(MyFirstWindowTabName);
}

void FMyFirstWindowModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMyFirstWindowCommands::Get().OpenPluginWindow);
}

void FMyFirstWindowModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMyFirstWindowCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyFirstWindowModule, MyFirstWindow)