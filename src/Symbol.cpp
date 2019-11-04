#include "Symbol.h"

char Symbol::toChar() const {
    return ch;
}

int Symbol::get() const {
    return ch;
}

bool Symbol::operator<(const Symbol &ot) const {
    return ch < ot.ch;
}