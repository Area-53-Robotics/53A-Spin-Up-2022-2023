//Header for indexer.cpp

#pragma once
#include "vex.h"

void startIndexer();

void updateIndexer();

void increaseDelay();

void decreaseDelay();

void printDelay();

void shoot();

void repeatShot(int numberOfShots = 3, float delay = 3);

void releaseIndexer();