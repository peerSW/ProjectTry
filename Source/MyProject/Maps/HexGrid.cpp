// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGrid.h"
#include <math.h>

// Sets default values
AHexGrid::AHexGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->x = FVector(0.0f, 1.0f, 0.0f);
	this->z = FVector(sqrt(3)*0.5f, 0.5f, 0.0f);
	this->y = -x - z;
	this->width = 157;
	this->num = 10;
	this->RightDirection = FVector2D(1, 0);
	this->RightUpDirection = FVector2D(0, 1);
	this->RightDownDirection = FVector2D(1, -1);
	this->LeftDownDirection = FVector2D(0, -1);
	this->LeftDirection = FVector2D(-1, 0);
	this->LeftUpDirection = FVector2D(-1, 1);
	core = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	core->SetCanEverAffectNavigation(false);
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hex"));
	RootComponent = core;
	cubeMesh->SetupAttachment(core);
	cubeMesh->SetGenerateOverlapEvents(false);
	cubeMesh->SetCanEverAffectNavigation(false);
	cubeMesh->SetRelativeLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	//cubeMesh->SetRelativeLocation(FVector(0, 0, 0));
}

// Called every frame
void AHexGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//return a 2D coordinate from world 3d coordinate
FVector2D AHexGrid::getCoordinateFromWorldLoc(FVector WolrdLocation)
{
	FVector relativeLoc = WolrdLocation - this->core->GetRelativeLocation();
	relativeLoc.Z = 0;
	float coord_z = relativeLoc.X / (this->z.X*width);
	float coord_x = (relativeLoc.Y - coord_z * this->z.Y*width) / (this->x.Y*width);
	float coord_y = -coord_x - coord_z;

	float rx = float(round(coord_x));
	float rz = float(round(coord_z));
	float ry = float(round(coord_y));

	float x_diff = abs(rx - coord_x);
	float y_diff = abs(ry - coord_y);
	float z_diff = abs(rz - coord_z);

	if ((x_diff > y_diff)&(x_diff > z_diff)){
		rx = -ry - rz;
	}
	else {
		if (y_diff>z_diff)
		{
			ry = -rx - rz;
		}
		else {
			rz = -rx - ry;
		}
	}
	return FVector2D(rx, rz);
}

//return a 2D coordinate from world 3d coordinate
FVector AHexGrid::getRelativeLocationFromcoord(FVector2D coord)
{
	FVector result = this->x*coord.X + this->z*coord.Y;
	return(result)*this->width;
}

//return a 2D coordinate from world 3d coordinate
FVector AHexGrid::getWorldLocationFromcoord(FVector2D coord)
{
	FVector result = this->x*coord.X + this->z*coord.Y;
	return(result)*this->width+this->core->GetRelativeLocation();
}

void AHexGrid::moveTo(FVector worldLocation)
{
	FVector2D coord = getCoordinateFromWorldLoc(worldLocation);
	FVector destination = getRelativeLocationFromcoord(coord);
	this->cubeMesh->SetRelativeLocation(destination);
}

FVector AHexGrid::getMeshLocation()
{
	return cubeMesh->GetRelativeLocation() + core->GetRelativeLocation();
}


float AHexGrid::Distance(FVector2D start, FVector2D end)
{
	return(abs(start.X - end.Y) + abs(start.X + start.Y - end.X - end.Y) + abs(start.Y - end.Y))/(2* this->width);
}



