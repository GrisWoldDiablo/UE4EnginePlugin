 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CM.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class ENGINEPLUGIN_API UCM : public UObject
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere) float myFloat;
    UPROPERTY(EditAnywhere) bool myBool;
    UPROPERTY(EditAnywhere, meta = (ClampMin = 11, ClampMax = 30, UIMin = 10, UIMax = 25)) int myInt;
    UPROPERTY(EditAnywhere, meta = (MultiLine = true)) FString myString;
    UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 10.0f)) float myFloatSlider;
    UPROPERTY(EditAnywhere) FVector myVector;
    UPROPERTY(EditAnywhere) FRotator myRotator;
    UPROPERTY(EditAnywhere) FTransform myTransform;
    UPROPERTY(EditAnywhere) FColor myColor;
    UPROPERTY(EditAnywhere) FText myText;
};
