// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"


UCLASS()
class MYPROJECT_API AHexGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector x;
	FVector y;
	FVector z;
	/** Natural length of the spring arm when there are no collisions */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float width;
	FVector2D RightDirection;
	FVector2D RightUpDirection;
	FVector2D LeftUpDirection;
	FVector2D LeftDirection;
	FVector2D LeftDownDirection;
	FVector2D RightDownDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* core;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* cubeMesh;
	int num;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		FVector2D getCoordinateFromWorldLoc(FVector WolrdLocation);
	UFUNCTION(BlueprintCallable)
		FVector getRelativeLocationFromcoord(FVector2D maplocation);
	UFUNCTION(BlueprintCallable)
		FVector getWorldLocationFromcoord(FVector2D maplocation);
	UFUNCTION(BlueprintCallable)
		void moveTo(FVector worldLocation);
	UFUNCTION(BlueprintCallable)
		FVector getMeshLocation();

	float Distance(FVector2D start, FVector2D end);

};
