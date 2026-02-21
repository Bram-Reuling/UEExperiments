// Copyright (c) 2026 Bram Reuling

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DemoAsyncNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDemoOutputPin, float, DemoOutput);

/**
 * 
 */
UCLASS()
class UEEXPERIMENTS_API UDemoAsyncNode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	float DelayTime = 0.f;
	
	UPROPERTY(BlueprintAssignable)
	FDemoOutputPin Direct;
	
	UPROPERTY(BlueprintAssignable)
	FDemoOutputPin Later;
	
private:
	const UObject* WorldObject;
	
	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;
	
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldObject"), Category = "CustomNodes/Async/Demo")
	static UDemoAsyncNode* DemoBlueprintNode(const UObject* WorldObject);
	
	virtual void Activate() override;
	
private:
	UFUNCTION()
	void InternalDirectCall() const;
	
	UFUNCTION()
	void InternalLaterCall(float timeElapsed);
};
