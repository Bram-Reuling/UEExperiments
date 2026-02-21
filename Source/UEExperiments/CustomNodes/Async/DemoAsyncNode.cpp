// Copyright (c) 2026 Bram Reuling

#include "DemoAsyncNode.h"

//======================================================================================================================
UDemoAsyncNode* UDemoAsyncNode::DemoBlueprintNode(const UObject* WorldObject)
{
	UDemoAsyncNode* Node = NewObject<UDemoAsyncNode>();
	if (Node)
	{
		Node->WorldObject = WorldObject;
		Node->DelayTime = 2.f;
	}
	
	return Node;
}

//======================================================================================================================
void UDemoAsyncNode::Activate()
{
	InternalDirectCall();
	
	if (!WorldObject)
		return;
	
	TimerDelegate.BindUObject(this, &UDemoAsyncNode::InternalLaterCall, DelayTime);
	WorldObject->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DelayTime, false);
}

//======================================================================================================================
void UDemoAsyncNode::InternalDirectCall() const
{
	Direct.Broadcast(0.f);
}

//======================================================================================================================
void UDemoAsyncNode::InternalLaterCall(float timeElapsed)
{
	Later.Broadcast(timeElapsed);
	
	WorldObject->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
	TimerDelegate.Unbind();
}
