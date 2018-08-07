#include <algorithm>
#include "Constraint.hxx"

using std::set_union;

Variable::Variable() : _assigned(V_EMPTY) {}

Variable::Variable(const Domain &domain) :
    _assigned(V_UNASSIGNED),
    _value(domain) {}

Variable::Variable(const initializer_list<int> &domain) :
    _assigned(V_UNASSIGNED),
    _value(domain) {}

Variable::Variable(const int &v) :
    _assigned(V_ASSIGNED) {
    _value = {v};
}

Variable Variable::assign(const int &v) const {
    if (_assigned == V_UNASSIGNED) {
        // If we’re unassigned, try and assign.
        if (_value.find(v) != _value.end()) {
            // The value is available, so assign it.
            return Variable(v);
        } else {
            // The value isn’t available so don’t.
            return Variable();
        }
    } else {
        // We’re already assigned, so just return a copy.
        return *this;
    }

    
}

const Variable::Domain &Variable::value() const {
    return _value;
}

const Variable::assigned Variable::status() const {
    return _assigned;
}

Variable::Variable(const Variable &v) :
    _assigned(v._assigned),
    _value(v._value) {}

bool Alldiff::operator()() const {
    // The assigned values
    Variable::Domain assd;

    // Go thorugh the assigned values and make sure they’re
    // all different.
    for(Variables::const_iterator v = _variables.begin();
        v != _variables.end();
        v++) {
        if (v->status() == Variable::V_ASSIGNED) {
            int w = *v->value().begin();
            if (assd.find(w) != assd.end()) {
                // The current value is already assigned, so we have
                // a constraint violation.
                return false;
            } else {
                // Otherwise add this value to the assigned values.
                assd.insert(v->value().begin(), v->value().end());
            }
        }
    }

    return true;
}
