/**
 * \brief Solve the Australian colouring problem.
 *
 * This is a simple problem to test the constraint solver.
 */

#include <iostream>
#include "Constraint.hxx"
#include "Australia.hxx"

using std::cout;
using std::endl;
using std::ostream;

int main(int argc, char **argv) {
    Territory wa(T_WA);
    Territory nt(T_NT, C_GREEN);
    Territory q(T_Q);
    Territory nsw(T_NSW);
    Territory v(T_V);
    Territory sa(T_SA);
    Territory t(T_T);

    cout << t << endl;
    cout << nt << endl;

    return 0;
}

Territory::Territory(const territory &t) :
    Variable({C_RED, C_GREEN, C_BLUE}),
    _territory(t) {}

Territory::Territory(const territory &t, const color &c) :
    Variable({c}),
    _territory(t) {
    _assigned = V_ASSIGNED;
}

Territory::Territory(const Territory &t) :
    Variable(t),
    _territory(t._territory) {}

ostream &operator<<(ostream &o, const territory &t) {
    switch (t) {
    case T_WA:
        o << "Western Austrailia";
        break;
    case T_NT:
        o << "Northern Territory";
        break;
    case T_Q:
        o << "Queensland";
        break;
    case T_NSW:
        o << "New South Wales";
        break;
    case T_V:
        o << "Victoria";
        break;
    case T_SA:
        o << "South Austrailia";
        break;
    case T_T:
        o << "Tasmania";
        break;
    }

    return o;
}

ostream &operator<<(ostream &o, const color &t) {
    switch (t) {
    case C_RED:
        o << "Red";
        break;
    case C_GREEN:
        o << "Green";
        break;
    case C_BLUE:
        o << "Blue";
        break;
    }

    return o;
}

ostream &operator<<(ostream &o, const Territory &t) {
    o << "Territory " << t._territory << ": ";

    switch(t._assigned) {
    case Variable::V_UNASSIGNED:
        o << "Remaining:";
        for(Variable::Domain::const_iterator i = t._value.begin();
            i != t._value.end();
            i++) {
            o << " " << (color)*i;
        }
        break;
    case Variable::V_ASSIGNED:
        o << "Assigned: " << (color)*t._value.begin();
        break;
    case Variable::V_EMPTY:
        o << "EMPTY";
        break;
    }
    return o;
}
