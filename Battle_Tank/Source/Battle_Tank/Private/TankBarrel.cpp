// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

 void UTankBarrel::Elevate(float DegreePerSecond)
 {
      UE_LOG(LogTemp,Warning,TEXT("Barrel Elevate Called At Speed : %f"),DegreePerSecond);
 }