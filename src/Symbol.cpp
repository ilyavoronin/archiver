#include "Symbol.h"

char Symbol::get_char() const {
    return ch;
}

int Symbol::get() const {
    return ch;
}

bool Symbol::operator<(const Symbol &ot) const {
    return this->ch < ot.ch;
}

bool Symbol::operator>(const Symbol &ot) const {
    return this->ch > ot.ch;
}

bool Symbol::operator<=(const Symbol &ot) const {
    return this->ch <= ot.ch;
}

bool Symbol::operator>=(const Symbol &ot) const {
    return this->ch >= ot.ch;
}

bool Symbol::operator==(const Symbol &ot) const {
    return this->ch == ot.ch;
}

bool Symbol::operator!=(const Symbol &ot) const {
    return this->ch != ot.ch;
}