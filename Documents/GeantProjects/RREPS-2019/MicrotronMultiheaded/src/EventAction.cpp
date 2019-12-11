//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

using namespace CLHEP;

EventAction::EventAction(RunAction *runAction): G4UserEventAction(),
    fRunAction(runAction) {
    //Обнуляем
    energ=0;
}

EventAction::~EventAction() {}
//Выполняется перед запуском начальной частицы
void EventAction::BeginOfEventAction(const G4Event*)
{     //Обнуляем для каждого запуска накопленную энергию частиц в детекторе
    energ=0;
}

//Запускается после моделирования прохождения частицы
void EventAction::EndOfEventAction(const G4Event* event)
{   //Передаем полученное значение накопленой энергии частиц в
    //поток моделирования
    fRunAction->FillEnergy(energ);
    // в конце каждого события
    RunAction* runAction = (RunAction*) G4RunManager::GetRunManager()->GetUserRunAction();
    // отображаем прогресс моделирования
    runAction->DisplayProgress(event->GetEventID()+1);
}

//Накапливаем энергию частиц
void EventAction::addParticle(const G4Step* step)
{   //Здесь мы берем энергию (кинетическую, без массы покоя) в ГэВ-ах
    energ=step->GetTrack()->GetKineticEnergy()/eV;
}

