#pragma once

UENUM()
enum EOperation
{
	Sum			UMETA(DisplayName = "Sum"),
	Subtract		UMETA(DisplayName = "Subtract"),
	Multiply		UMETA(DisplayName = "Multiply"),
	Divide		UMETA(DisplayName = "Divide"),
};