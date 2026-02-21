// Copyright (c) 2026 Bram Reuling

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DemoAsyncNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDemoOutputPin, float, DemoOutput);

/**
 * Creates a node that has a single incoming execution pin and multiple outgoing execution pins.
 * The class has the following outgoing pins:
 * - Direct: Executes directly after the incoming execution pin is triggered.
 * - Later: Executes 2 seconds after the incoming execution pin is triggered.
 * 
 * DemoBlueprintNode(...) is the actual 'Node' that you will call in blueprints. This function does the initial setup.
 * Activate(...) will trigger the outgoing execution pins.
 * 
 * More information => https://blog.bramreuling.com/posts/Creating-async-blueprint-nodes-in-Unreal-Engine/
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
	
	// Timer.
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
