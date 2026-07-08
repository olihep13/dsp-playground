#pragma once

typedef struct {
    double freq;
    double amp;
}Tone;

typedef struct {
    Tone CarrierTone;
    std::vector<double> messageSignal;
    double modulationIndex;
}AMSignal;

constexpr double PI = 3.141592653589793;