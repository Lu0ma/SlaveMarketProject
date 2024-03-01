#include "Bench.h"
#include "Macro.h"

#define PATH_BENCH "Map/Bench.png"


Bench::Bench() : Actor(STRING_ID("Bench"), ShapeData(Vector2f(0.0f, 5.0f), Vector2f(176.0, 80.0f), PATH_BENCH))
{

}

void Bench::Init()
{

}