// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

double pow(double x, double y);
float powf(float x, float y);
long double powl(long double x, long double y);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    return (atoi(&fraction[0]) * (8/atoi(&fraction[2])));
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double freq = 0;
    // A4 = 440
    // B4 = 440 * 2^(x/12) where x is how much of a difference in a semitone the note is from A4

    // To go up an octive, multiply/divide the number by 2
    if (note[1] == '1' || note[2] == '1')
    {
        freq = 440 / (4*(2));
    }
    else if (note[1] == '2' || note[2] == '2')
    {
        freq = 440 / (2*(2));
    }
    else if (note[1] == '3' || note[2] == '3')
    {
        freq = 440 / (1*(2));
    }
    else if (note[1] == '4' || note[2] == '4')
    {
        freq = 440;
    }
    else if (note[1] == '5' || note[2] == '5')
    {
        freq = 440 * (1*(2));
    }
    else if (note[1] == '6' || note[2] == '6')
    {
        freq = 440 * (2*(2));
    }
    else if (note[1] == '7' || note[2] == '7')
    {
        freq = 440 * (3*(2));
    }
    else if (note[1] == '8' || note[2] == '8')
    {
        freq = 440 * (4*(2));
    }

    // Apply actual notes
    if (note[0] == 'A' && (note[1] != '#' && note[1] != 'b'))
    {
        freq = freq * 1;
    }
    else if ((note[0] == 'A' && note[1] == '#') || (note[0] == 'B' && note[1] == 'b'))
    {
        freq = freq * 1.0594630944;
    }
    else if (note[0] == 'B' && (note[1] != '#' && note[1] != 'b'))
    {
        freq = freq * 1.1224620483;
    }
    else if (note[0] == 'C' && (note[1] != '#' && note[1] != 'b'))
    {
        freq = freq * 1.189207115 / 2;
    }
    else if ((note[0] == 'C' && note[1] == '#') || (note[0] == 'D' && note[1] == 'b'))
    {
        freq = freq * 1.2599210499 / 2;
    }
    else if (note[0] == 'D' && (note[1] != '#' && note[1] != 'b'))
    {
        freq = freq * 1.3348398542 / 2;
    }
    else if ((note[0] == 'D' && note[1] == '#') || (note[0] == 'E' && note[1] == 'b'))
    {
        freq = freq * 1.4142135624 / 2;
    }
    else if (note[0] == 'E' && (note[1] != '#' && note[1] != 'b'))
    {
        freq = freq * 1.4983070769 / 2;
    }
    else if (note[0] == 'F' && (note[1] != '#' && note[1] != 'b'))
    {
        freq = freq * 1.587401052 / 2;
    }
    else if ((note[0] == 'F' && note[1] == '#') || (note[0] == 'G' && note[1] == 'b'))
    {
        freq = freq * 1.6817928305 / 2;
    }
    else if (note[0] == 'G' && (note[1] != '#' && note[1] != 'b'))
    {
        freq = freq * 1.7817974363 / 2;
    }
    else if ((note[0] == 'G' && note[1] == '#'))
    {
        freq = freq * 1.8877486254 / 2;
    } else if ((note[0] == 'A' && note[1] == 'b')) {
        freq = freq * 1.8877486254 / 2;
    }

    return round(freq);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return (s[0] == '\0');
}
