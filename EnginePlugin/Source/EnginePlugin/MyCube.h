// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CM.h"

#include "MyCube.generated.h"

UENUM(BlueprintType)
enum class ESelectorEnum : uint8
{
	VE_Option1 UMETA(DisplayName="Option 1"),
	VE_Option2 UMETA(DisplayName="Option 2"),
	VE_Option3 UMETA(DisplayName="Option 3")
};

USTRUCT(BlueprintType)
struct FCustomClass
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A|Sub") float myFloat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "B|Sub") bool myBool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 11, ClampMax = 30, UIMin = 10, UIMax = 25)) int myInt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true)) FString myString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.0f, UIMax = 10.0f)) float myFloatSlider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector myVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A") FRotator myRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A") FTransform myTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A", AdvancedDisplay) FColor myColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "B", AdvancedDisplay) FText myText;
};

UCLASS()
class ENGINEPLUGIN_API AMyCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCube();
	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A") ESelectorEnum MaterialOptionsEnum;
	FORCEINLINE FString GetEnumAsString()
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESelectorEnum"), true);
		if (!EnumPtr) return FString("Invalid");

		return (EnumPtr->GetDisplayNameTextByValue((int64)MaterialOptionsEnum)).ToString(); // for EnumValue == VE_Dance returns "VE_Dance"
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="A|Mats") UMaterialInterface* MatOption1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A|Mats") UMaterialInterface* MatOption2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A", AdvancedDisplay) UMaterialInterface* MatOption3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A") TArray<TSubclassOf<class UCM>> CustomClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A", meta = (TitleProperty = "name")) TArray<FCustomClass> FCustomClasses;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

};
