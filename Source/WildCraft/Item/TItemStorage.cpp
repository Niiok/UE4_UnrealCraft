// Fill out your copyright notice in the Description page of Project Settings.


#include "TItemStorage.h"
#include "Item/WC_ItemInstance.h"

template<typename T>
const TMap<UWC_ItemInstance*, T>& TItemStorage<T>::GetItems()
{
	return Items;
}

template<typename T>
TItemStorage<T>::TItemStorage()
{
}

template<typename T>
TItemStorage<T>::~TItemStorage()
{
}
