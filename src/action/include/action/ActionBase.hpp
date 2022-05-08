#ifndef ACTIONBASE_HPP
#define ACTIONBASE_HPP

#include "action/IAction.hpp"

class ActionBase : public IAction
{
public:
    ActionBase();
    ActionBase(const QString& name);

    // IAction interface
    const QString& getName() const override;

    void setName(const QString& name);

private:
    QString mName;
};

#endif // ACTIONBASE_HPP
