#include "ActionBase.hpp"

ActionBase::ActionBase()
    : mName("")
{

}

ActionBase::ActionBase(const QString& name)
    : mName(name)
{

}

const QString& ActionBase::getName() const
{
    return mName;
}

void ActionBase::setName(const QString& name)
{
    mName = name;
}
