#ifndef EventAction_h
#define EventAction_h 1
//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/
#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Step.hh"
#include "globals.hh"
class RunAction;
///Класс отвечающий за запуск 1 первичной частицы
class EventAction: public G4UserEventAction
{
public:
    ///Конструктор
    EventAction(RunAction* runAction);
    ~EventAction();
    ///Функция выполняемая перед запуском частицы
    virtual void BeginOfEventAction(const G4Event* event);
    ///Функция выполняемая после запуска частицы
    virtual void EndOfEventAction(const G4Event* event);
    ///В эту переменную будем накапливать энергию частиц
    /// пришедших в детектор
    G4double energ;
    ///Функция регистрации частицы в детекторе
    void addParticle(const G4Step* step);
private:
    ///Указатель на поток выполнения
    RunAction* fRunAction;
};

#endif

