// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantMap.h"

MutantMap::MutantMap()
{
	AMutantBase* Mutant1;
	AMutantBase* Mutant2;
	AMutantBase* Mutant3;

	MMutants.Add(Tall, Mutant1);
	MMutants.Add(Normal, Mutant2);
	MMutants.Add(Short, Mutant3);
}

MutantMap::~MutantMap()
{
}
