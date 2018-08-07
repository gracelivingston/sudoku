/**
 * \file Constraint.hxx
 *
 * \brief Header file defining Constraints and Variables.
 */

#ifndef CONSTRAINT_HXX
#define CONSTRAINT_HXX

#include <set>
#include <vector>
#include <utility>
#include <initializer_list>

using std::set;
using std::vector;
using std::initializer_list;

/**
 * A variable for a constraint problem.
 *
 * Types:
 *
 * - T: the type of the variable
 */
class Variable {
public:
    /** The Domain of this Variable. */
    typedef set<int> Domain;

    /** Construct an empty Variable, indicating an error. */
    Variable();

    /** Construct a new Variable with the given Domain. */
    Variable(const Domain &domain);

    /** Construct a new Variable from an initializer_list. */
    Variable(const initializer_list<int> &domain);

    /** Construct a new Variable with an assigned value. */
    Variable(const int &v);

    /** Copy a Variable. */
    Variable(const Variable &v);

    /** What kind of value this variable has. */
    enum assigned {
        /** This Variable isn’t fully constrained. */
        V_UNASSIGNED,

        /** This Variable is exactly constrained. */
        V_ASSIGNED,

        /** This Variable is over constrained. */
        V_EMPTY
    };

    /** Assign a value to this Variable, returning a copy. */
    Variable assign(const int &v) const;

    /** Remove possible values from this Variable, returning
     * a copy. */
    Variable reduce(const Domain::iterator &v1,
                    const Domain::iterator &v2) const;

    const Domain &value() const;

    const assigned status() const;
protected:
    assigned _assigned;

    /** Either the actual value or the remaining values, depending on
     * _assigned. If _assigned is V_EMPTY, this doesn’t matter. */
    Domain _value;
};

/**
 * A set of references to Variables.
 *
 * Since Variables are affected by potentially any Constraint, we
 * store references to them and pass these sets around.
 */
typedef set<Variable> Variables;

/**
 * A constraint between two variables.
 *
 * Specifies a constraint to be enforced between two variable.
 */
class Constraint {
public:
    /**
     * Construct a Constraint over a set of Variables.
     */
    Constraint(Variables &vs);

    /**
     * Copy a Constraint.
     */
    Constraint(const Constraint &c);

    /**
     * Validate the Constraint.
     *
     * This will check the Variables covered by this Constraint.
     * If the Constraint is satisfied, this returns true, otherwise it
     * returns false.
     *
     * Constraints only check, they don’t modify.
     */
    virtual bool operator()() const = 0;
protected:
    Variables _variables;
};

/**
 * Constraint requiring all variables to have a different value.
 */
class Alldiff : public Constraint {
    virtual bool operator()() const;
};

typedef vector<Constraint> Constraints;

/**
 * A Constraint Satisfaction Problem.
 *
 * This represents a whole CSP. It contains all of the Variables and
 * the Constraints, and then Algorithms can be used to subsequently
 * reduce the Variables until a solution is found.
 */
class CSP {
public:
    CSP(Variables vars, Constraints cstrs);
    CSP(const CSP &csp);
};

/**
 * A CSP algorithm.
 *
 * Performs an assignment on a CSP.
 * a reduced copy.
 */
class Algorithm {
public:
    virtual CSP operator()(const CSP &csp) = 0;
};

#endif
