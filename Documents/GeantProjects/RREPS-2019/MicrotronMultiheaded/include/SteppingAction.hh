#ifndef SteppingAction_h
#define SteppingAction_h 1

//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;
class G4LogicalVolume;

/// Stepping action class
/// Класс для регистрации событий

class SteppingAction : public G4UserSteppingAction
{
public:
    /// Конструктор
    SteppingAction(EventAction* eventAction);
    virtual ~SteppingAction();
    /// method from the base class
    /// Метод который вызывается, когда происходит какое либо событие с
    /// частицей
    virtual void UserSteppingAction(const G4Step*);
private:
    EventAction* fEventAction;
};

#endif
