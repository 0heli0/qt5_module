#include "qperson.h"

QPerson::QPerson(QString name, QObject *parent) : QObject(parent)
{
    m_name = name;
}

unsigned QPerson::age()
{
    return m_age;
}

void QPerson::setAge(unsigned age)
{
    m_age = age;
    emit(ageChanged(age));
}

void QPerson::increaseAge()
{
    m_age++;
    emit(ageChanged(m_age));
}
