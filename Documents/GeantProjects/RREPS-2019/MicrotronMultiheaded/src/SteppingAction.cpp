//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "ExG4DetectorConstruction01.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4EventManager.hh"
#include "B4Analysis.hh"
//---------------------------
#include "G4ProcessType.hh"
#include "G4VPhysicalVolume.hh"
using namespace CLHEP;
SteppingAction::SteppingAction(EventAction* eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction)
{
}

SteppingAction::~SteppingAction()
{
}
//Метод который вызывается когда происходит какое либо событие
void SteppingAction::UserSteppingAction(const G4Step* step){
	auto analysisManager = G4AnalysisManager::Instance();
    //Создаем указатель на трек для удобства
    G4Track * track = step->GetTrack();
    //Узнаем физический объем в котором находится частица
    G4VPhysicalVolume* vel=track->GetVolume();
    //Название физического объема в котором мы будем регистрировать
    //частицы, он у нас будет играть роль чуствительного объема
    G4String name="Target";
    //Условие или частица находится в интересуещем нас объеме
    if(name==vel->GetName()){
        G4String particleName = track->GetDefinition()->GetParticleName();
        if (particleName == "opticalphoton") {//opticalphoton
            //Если находится то учитываем ее энергию
            fEventAction->addParticle(step);
            //Нефизично, но нам нужно подсчитать энергию частиц попавших
            //в детектор, поэтому эту частицу уничтожаем что бы она
            //не зарегистрировалась несколько раз
            //G4ThreeVector angle = track->GetMomentumDirection();
            G4ThreeVector xyz = track->GetPosition()/mm;

            double energy = step->GetTrack()->GetDynamicParticle()->GetTotalEnergy();//получаем энергию частицы
            //std::ofstream file_energy_dep("total_particles_energy.txt", std::ios::app);
            //std::ofstream file_energy_dep1("file.txt", std::ios::app);
            analysisManager->FillH2(0, xyz[0], xyz[1]);
            analysisManager->FillH1(0, energy);
        }step->GetTrack()->SetTrackStatus(fStopAndKill);
    }
}


