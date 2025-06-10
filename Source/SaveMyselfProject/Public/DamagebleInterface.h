
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamagebleInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDamagebleInterface : public UInterface
{
	GENERATED_BODY()
};

class SAVEMYSELFPROJECT_API IDamagebleInterface
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void ReceiveDamage(float Damage);
};
