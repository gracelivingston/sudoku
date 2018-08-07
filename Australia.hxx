/**
 * \file Australia.hxx
 *
 * Definitions for the Australia colour problem.
 */

#ifndef AUSTRALIA_HXX
#define AUSTRALIA_HXX

#include <iostream>

using std::ostream;

/**
 * The Australian territories.
 */
enum territory {
    /** Western Australia */
    T_WA,

    /** Northern Territory */
    T_NT,

    /** Queensland */
    T_Q,

    /** New South Wales */
    T_NSW,

    /** Victoria */
    T_V,

    /** South Australia */
    T_SA,

    /** Tasmania */
    T_T
};

enum color {
    C_RED,
    C_GREEN,
    C_BLUE
};

class Territory : public Variable {
public:
    /** Assign a color to a Territory. */
    Territory(const territory &t, const color &c);

    /** Create a free Territory. */
    Territory(const territory &t);

    /** Copy a Territory. */
    Territory(const Territory &t);
private:
    territory _territory;

    friend ostream &operator<<(ostream &o, const Territory &t);

};

ostream &operator<<(ostream &o, const territory &t);
ostream &operator<<(ostream &o, const color &t);

#endif
